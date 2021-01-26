// Copyright (c) 2017 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#include "PointOutput.h"
#include "helpers/containerUtils.h"
#include "mapGenerator/Algorithms.h"
#include <boost/test/unit_test.hpp>
#include <set>

using namespace rttr::mapGenerator;

BOOST_AUTO_TEST_SUITE(AlgorithmsTests)

BOOST_AUTO_TEST_CASE(UpdateDistances_updates_enqueued_elements_correctly)
{
    MapExtent size(8, 8);
    MapPoint reference(4, 7);
    NodeMapBase<unsigned> distances;
    distances.Resize(size, unsigned(-1));
    std::queue<MapPoint> queue;
    queue.push(reference);
    distances[reference] = 0;

    UpdateDistances(distances, queue);

    BOOST_TEST_REQUIRE(queue.empty());

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_REQUIRE(distances[pt] == distances.CalcDistance(pt, reference));
    }
}

BOOST_AUTO_TEST_CASE(Smooth_keeps_homogenous_map_unchanged)
{
    NodeMapBase<int> nodes;
    MapExtent size(16, 8);

    const int radius = 4;
    const int iterations = 2;
    const int expectedValue = 1;

    nodes.Resize(size, expectedValue);

    Smooth(iterations, radius, nodes);

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_REQUIRE(nodes[pt] == expectedValue);
    }
}

BOOST_AUTO_TEST_CASE(Smooth_interpolates_values_around_peak)
{
    NodeMapBase<int> nodes;
    MapExtent size(16, 8);

    const MapPoint peak(4, 7);
    const int peakValue = 1000;
    const int radius = 4;
    const int iterations = 2;
    const int defaultValue = 1;

    nodes.Resize(size, defaultValue);
    nodes[peak] = peakValue;

    Smooth(iterations, radius, nodes);

    BOOST_TEST_REQUIRE(nodes[peak] < peakValue);

    auto neighbors = nodes.GetPointsInRadius(peak, radius);

    for(MapPoint p : neighbors)
    {
        BOOST_TEST_REQUIRE(nodes[p] > defaultValue);
    }
}

BOOST_AUTO_TEST_CASE(Scale_updates_minimum_and_maximum_values_correctly)
{
    MapExtent size(16, 8);
    NodeMapBase<unsigned> values;
    values.Resize(size, 8u);
    values[0] = 12; // max
    values[1] = 7;  // min

    Scale(values, 0u, 20u);

    BOOST_TEST_REQUIRE(values[0] == 20u);
    BOOST_TEST_REQUIRE(values[1] == 0u);
}

BOOST_AUTO_TEST_CASE(Scale_keeps_equal_values_unchanged)
{
    MapExtent size(16, 8);
    NodeMapBase<unsigned> values;
    values.Resize(size, 8u);

    Scale(values, 0u, 20u);

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_REQUIRE(values[pt] == 8u);
    }
}

BOOST_AUTO_TEST_CASE(Collect_returns_empty_for_negative_map_point)
{
    NodeMapBase<int> map;
    MapExtent size(16, 8);
    MapPoint negative(0, 0);

    map.Resize(size, 1);
    map[negative] = 0;

    auto result = Collect(map, negative, [&map](const MapPoint& p) { return map[p]; });

    BOOST_TEST_REQUIRE(result.empty());
}

BOOST_AUTO_TEST_CASE(Collect_returns_all_map_points_for_entirely_positive_map)
{
    NodeMapBase<int> map;
    MapExtent size(16, 8);
    MapPoint point(0, 0);

    map.Resize(size, 1);

    auto result = Collect(map, point, [&map](const MapPoint& p) { return map[p]; });

    const unsigned expectedResults = size.x * size.y;

    BOOST_TEST_REQUIRE(result.size() == expectedResults);

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_REQUIRE(helpers::contains(result, pt));
    }
}

BOOST_AUTO_TEST_CASE(Collect_returns_only_connected_positive_map_points)
{
    NodeMapBase<int> map;
    MapExtent size(16, 16);
    map.Resize(size, 0);

    // positive area around target point
    MapPoint point(3, 4);
    auto neighbors = map.GetNeighbours(point);
    for(auto neighbor : neighbors)
    {
        map[neighbor] = 1;
    }
    map[point] = 1;

    // disconnected, positive area
    MapPoint other(12, 12);
    auto otherNeighbors = map.GetNeighbours(other);
    for(auto neighbor : otherNeighbors)
    {
        map[neighbor] = 1;
    }
    map[other] = 1;

    auto result = Collect(map, point, [&map](const MapPoint& p) { return map[p]; });

    const unsigned expectedSize = neighbors.size() + 1u;
    const unsigned actualSize = result.size();

    BOOST_TEST_REQUIRE(actualSize == expectedSize);
    BOOST_TEST_REQUIRE(helpers::contains(result, point));

    for(auto pt : neighbors)
    {
        BOOST_TEST_REQUIRE(helpers::contains(result, pt));
    }
}

BOOST_AUTO_TEST_CASE(DistancesTo_with_predicate_returns_expected_distance_for_each_map_point)
{
    MapExtent size(9, 8);

    std::vector<unsigned> expectedDistances{
      // clang-format off
        5, 4, 3, 3, 3, 3, 4, 5, 6,
         5, 4, 4, 4, 4, 4, 5, 6, 6,
        5, 4, 3, 3, 3, 3, 4, 5, 6,
         4, 3, 2, 2, 2, 3, 4, 5, 5,
        4, 3, 2, 1, 1, 2, 3, 4, 5,
         3, 2, 1, 0, 1, 2, 3, 4, 4,
        4, 3, 2, 1, 1, 2, 3, 4, 5,
         4, 3, 2, 2, 2, 3, 4, 5, 5,
      // clang-format on
    };

    auto distances = DistancesTo(size, [](MapPoint pt) {
        return pt == MapPoint(3, 5); // compute distance to P(4/3)
    });

    BOOST_TEST_REQUIRE(distances.GetSize() == size);

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_INFO(pt);
        BOOST_TEST(expectedDistances[pt.x + pt.y * size.x] == distances[pt]);
    }
}

BOOST_AUTO_TEST_CASE(DistancesTo_returns_expected_distance_for_each_map_point)
{
    MapExtent size(9, 8);

    std::vector<unsigned> expectedDistances{
      // clang-format off
        5, 4, 3, 3, 3, 3, 4, 5, 6,
         5, 4, 4, 4, 4, 4, 5, 6, 6,
        5, 4, 3, 3, 3, 3, 4, 5, 6,
         4, 3, 2, 2, 2, 3, 4, 5, 5,
        4, 3, 2, 1, 1, 2, 3, 4, 5,
         3, 2, 1, 0, 1, 2, 3, 4, 4,
        4, 3, 2, 1, 1, 2, 3, 4, 5,
         4, 3, 2, 2, 2, 3, 4, 5, 5,
      // clang-format on
    };

    std::set<MapPoint, MapPointLess> flaggedPoints{MapPoint(3, 5)};
    auto distances = DistancesTo(flaggedPoints, size);

    BOOST_TEST_REQUIRE(distances.GetSize() == size);

    RTTR_FOREACH_PT(MapPoint, size)
    {
        BOOST_TEST_INFO(pt);
        BOOST_TEST(expectedDistances[pt.x + pt.y * size.x] == distances[pt]);
    }
}

BOOST_AUTO_TEST_CASE(LimitFor_ignores_map_points_outside_of_area)
{
    MapExtent size(8, 16);
    NodeMapBase<int> values;
    values.Resize(size);
    for(int i = 0; i < size.x * size.y; i++)
    {
        values[i] = i;
    }
    const std::vector<MapPoint> area{MapPoint(4, 0), MapPoint(5, 0), MapPoint(6, 0), MapPoint(7, 0)};
    const double coverage = 0.5;
    const int minimum = 1;

    int limit = LimitFor(values, area, coverage, minimum);

    auto expectedNodes = static_cast<unsigned>(area.size() * coverage);
    unsigned actualNodes = 0u;
    for(const auto& pt : area)
    {
        if(values[pt] >= minimum && values[pt] <= limit)
        {
            actualNodes++;
        }
    }
    BOOST_TEST_REQUIRE(actualNodes == expectedNodes);
}

BOOST_AUTO_TEST_CASE(LimitFor_ignores_map_points_below_minimum_threshold)
{
    MapExtent size(8, 16);
    NodeMapBase<int> values;
    values.Resize(size);
    for(int i = 0; i < size.x * size.y; i++)
    {
        values[i] = i;
    }
    const double coverage = 0.11;
    const int minimum = 2;

    int limit = LimitFor(values, coverage, minimum);

    auto expectedNodes = static_cast<unsigned>(size.x * size.y * coverage);
    unsigned actualNodes = 0u;
    RTTR_FOREACH_PT(MapPoint, size)
    {
        if(values[pt] >= minimum && values[pt] <= limit)
        {
            actualNodes++;
        }
    }
    BOOST_TEST_REQUIRE(actualNodes == expectedNodes);
}

BOOST_AUTO_TEST_CASE(LimitFor_always_chooses_closest_value)
{
    MapExtent size(8, 8);
    NodeMapBase<int> values;
    values.Resize(size);
    double coverage = 0.3;
    int minimum = 3;
    unsigned totalNodes = size.x * size.y;
    auto exactNumberOfNodes = static_cast<unsigned>(coverage * totalNodes);
    for(unsigned i = 0; i < exactNumberOfNodes - 5; i++)
    {
        values[i] = 5;
    }
    for(unsigned i = exactNumberOfNodes - 5; i < totalNodes; i++)
    {
        values[i] = 6;
    }

    BOOST_TEST_REQUIRE(LimitFor(values, coverage, minimum) == 5);

    for(unsigned i = 0; i < exactNumberOfNodes + 5; i++)
    {
        values[i] = 5;
    }

    for(unsigned i = exactNumberOfNodes + 5; i < totalNodes; i++)
    {
        values[i] = 6;
    }

    BOOST_TEST_REQUIRE(LimitFor(values, coverage, minimum) == 5);
}

BOOST_AUTO_TEST_SUITE_END()
