// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
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

#ifndef TerrainData_h__
#define TerrainData_h__

#include "gameTypes/MapTypes.h"
#include "gameTypes/LandscapeType.h"
#include "Rect.h"

class TerrainData
{
    // Disallow construction, only static methods
    TerrainData();
public:
    /// Returns the terrain type for a given map terrain index
    static TerrainType MapIdx2Terrain(unsigned char mapIdx);
    /// Returns the position in the texture image
    static Rect GetPosInTexture(TerrainType t);
    /// Returns the color for the terrain
    static unsigned GetColor(LandscapeType landsCape, TerrainType t);
    /// Gets the edge type for a terrain type
    static EdgeType GetEdgeType(LandscapeType landsCape, TerrainType t);
    /// Gets the edge type that t1 draws over t2
    /// 0: None, 1: Snow, 2: Mountain, 3: Desert, 4: Meadow, 5: Water
    static unsigned char GetEdgeType(LandscapeType landsCape, TerrainType t1, TerrainType t2);
    /// Returns whether the given map terrain index is a harbour spot
    static bool IsHarborSpot(unsigned char mapIdx){ return (mapIdx & 0x40) != 0;}
    /// Returns whether the given terrain type can be used (is not deadly)
    static bool IsUseable(TerrainType t);
    /// Returns whether the given terrain type can be used by a ship (non-blocking water)
    static bool IsUsableByShip(TerrainType t);
    /// Returns whether stuff (animals, corn fields) can grow on the terrain (no dessert, mountain etc)
    static bool IsVital(TerrainType t);
    /// Returns whether the given terrain is any kind of water
    static bool IsWater(TerrainType t);
    /// Returns whether the given terrain is a mountain
    static bool IsMountain(TerrainType t);
    /// Returns whether the given terrain is a mineable mountain
    static bool IsMineable(TerrainType t);
};

#endif // TerrainData_h__