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

#include "defines.h" // IWYU pragma: keep
#include "nofMiner.h"

#include "Loader.h"
#include "GameClient.h"
#include "buildings/nobUsual.h"
#include "SoundManager.h"
#include "ogl/glArchivItem_Bitmap_Player.h"
class SerializedGameData;

nofMiner::nofMiner(const MapPoint pos, const unsigned char player, nobUsual* workplace)
    : nofWorkman(JOB_MINER, pos, player, workplace)
{
}

nofMiner::nofMiner(SerializedGameData& sgd, const unsigned obj_id) : nofWorkman(sgd, obj_id)
{
}

void nofMiner::DrawWorking(DrawPoint drawPt)
{
    const DrawPoint offsets[NAT_COUNT][4] = //work animation offset per nation and (granite, coal, iron, gold)
    {
        {{5, 3},  {5, 3},  {5, 3},  {5, 3}},  //africans
        {{4, 1},  {4, 1},  {4, 1},  {4, 1}},  //japanese
        {{9, 4},  {9, 4},  {9, 4},  {9, 4}},  //romans
        {{10, 3}, {10, 3}, {10, 3}, {10, 3}}, //vikings
        {{8, 3},  {8, 3},  {8, 3},  {8, 3}}   //babylonians
    };

    unsigned now_id = GAMECLIENT.Interpolate(160, current_ev);
    unsigned texture;
    if(workplace->GetNation() == NAT_ROMANS)
        texture = 92 + now_id % 8;
    else
        texture = 1799 + now_id % 4;
    LOADER.GetPlayerImage("rom_bobs", texture)->Draw(drawPt + offsets[workplace->GetNation()][(workplace->GetBuildingType() - BLD_GRANITEMINE) * 2]);

    if(now_id % 8 == 3)
    {
        SOUNDMANAGER.PlayNOSound(59, this, now_id);
        was_sounding = true;
    }
}

unsigned short nofMiner::GetCarryID() const
{
    switch(workplace->GetBuildingType())
    {
        case BLD_GOLDMINE: return 65;
        case BLD_IRONMINE: return 66;
        case BLD_COALMINE: return 67;
        default: return 68;
    }
}

GoodType nofMiner::ProduceWare()
{
    switch(workplace->GetBuildingType())
    {
        case BLD_GOLDMINE: return GD_GOLD;
        case BLD_IRONMINE: return GD_IRONORE;
        case BLD_COALMINE: return GD_COAL;
        default: return GD_STONES;
    }
}

bool nofMiner::AreWaresAvailable()
{
    return nofWorkman::AreWaresAvailable() &&
        GetResources(workplace->GetBuildingType() - BLD_GRANITEMINE);
}
