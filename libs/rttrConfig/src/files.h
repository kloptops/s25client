// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
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
#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#pragma once

#include "helpers/MultiArray.h"
#include "s25util/warningSuppression.h"
#include <array>
#include <string>

RTTR_IGNORE_DIAGNOSTIC("-Wunused-variable")

namespace s25 {
namespace folders {
    constexpr auto config = "<RTTR_CONFIG>";                   // Einstellungsordner
    constexpr auto data = "<RTTR_GAME>/DATA";                  // S2 game data
    constexpr auto driver = "<RTTR_DRIVER>";                   // Treiberordner
    constexpr auto gameLstsGlobal = "<RTTR_RTTR>/LSTS/GAME";   // systemweite lstfiles (immer bei spielstart geladen)
    constexpr auto gameLstsUser = "<RTTR_USERDATA>/LSTS/GAME"; // persönliche lstfiles (immer bei spielstart geladen)
    constexpr auto gamedata = "<RTTR_RTTR>/gamedata";          // Path to the gamedata
    constexpr auto languages = "<RTTR_RTTR>/languages";        // die ganzen Sprachdateien
    constexpr auto loadScreens = "<RTTR_GAME>/GFX/PICS";
    constexpr auto loadScreensMissions = "<RTTR_GAME>/GFX/PICS/MISSION";
    constexpr auto logs = "<RTTR_USERDATA>/LOGS";     // Log-Ordner
    constexpr auto lstsGlobal = "<RTTR_RTTR>/LSTS";   // systemweite lstfiles (immer bei start geladen)
    constexpr auto lstsUser = "<RTTR_USERDATA>/LSTS"; // persönliche lstfiles (immer bei start geladen)
    constexpr auto mapsCampaign = "<RTTR_GAME>/DATA/MAPS";
    constexpr auto mapsContinents = "<RTTR_GAME>/DATA/MAPS2";
    constexpr auto mapsNew = "<RTTR_GAME>/DATA/MAPS4";
    constexpr auto mapsOld = "<RTTR_GAME>/DATA/MAPS3";
    constexpr auto mapsOther = "<RTTR_RTTR>/MAPS/OTHER"; // Andere Maps
    constexpr auto mapsOwn = "<RTTR_USERDATA>/WORLDS";
    constexpr auto mapsPlayed = "<RTTR_USERDATA>/MAPS"; // die heruntergeladenen Karten
    constexpr auto mapsRttr = "<RTTR_RTTR>/MAPS/NEW";   // unsere eigenen neuen Karten
    constexpr auto mapsSea = "<RTTR_RTTR>/MAPS/SEA";    // Seefahrtkarten
    constexpr auto mbob = "<RTTR_GAME>/DATA/MBOB";      // Nation graphics
    constexpr auto music = "<RTTR_RTTR>/MUSIC";
    constexpr auto replays = "<RTTR_USERDATA>/REPLAYS";         // Replayordner
    constexpr auto save = "<RTTR_USERDATA>/SAVE";               // Der Speicherordner
    constexpr auto screenshots = "<RTTR_USERDATA>/screenshots"; // Screenshots
    constexpr auto sng = "<RTTR_RTTR>/MUSIC/SNG";               // die musik
    constexpr auto texte = "<RTTR_RTTR>/texte";
    constexpr auto textures = "<RTTR_GAME>/GFX/TEXTURES"; // Terrain textures
} // namespace folders
namespace files {
    constexpr auto soundOrig = "<RTTR_GAME>/DATA/SOUNDDAT/SOUND.LST"; // die originale sound.lst
    constexpr auto soundScript = "<RTTR_RTTR>/sound.scs";             // Das konvertier-script
} // namespace files
namespace resources {
    constexpr auto boat = "<RTTR_GAME>/DATA/BOBS/BOAT.LST";
    constexpr auto boot_z = "<RTTR_GAME>/DATA/BOOT_Z.LST";
    constexpr auto carrier = "<RTTR_GAME>/DATA/BOBS/CARRIER.BOB";
    constexpr auto colors = "<RTTR_RTTR>/COLORS.ACT";   // Spezialpalette wegen Schriften usw
    constexpr auto config = "<RTTR_CONFIG>/CONFIG.INI"; // die Einstellungsdatei
    constexpr auto io = "<RTTR_GAME>/DATA/IO/IO.DAT";
    constexpr auto jobs = "<RTTR_GAME>/DATA/BOBS/JOBS.BOB";
    constexpr auto mis0bobs = "<RTTR_GAME>/DATA/MIS0BOBS.LST";
    constexpr auto mis1bobs = "<RTTR_GAME>/DATA/MIS1BOBS.LST";
    constexpr auto mis2bobs = "<RTTR_GAME>/DATA/MIS2BOBS.LST";
    constexpr auto mis3bobs = "<RTTR_GAME>/DATA/MIS3BOBS.LST";
    constexpr auto mis4bobs = "<RTTR_GAME>/DATA/MIS4BOBS.LST";
    constexpr auto mis5bobs = "<RTTR_GAME>/DATA/MIS5BOBS.LST";
    constexpr auto pal5 = "<RTTR_GAME>/GFX/PALETTE/PAL5.BBM"; // die ganzen Paletten
    constexpr auto pal6 = "<RTTR_GAME>/GFX/PALETTE/PAL6.BBM";
    constexpr auto pal7 = "<RTTR_GAME>/GFX/PALETTE/PAL7.BBM";
    constexpr auto paletti0 = "<RTTR_GAME>/GFX/PALETTE/PALETTI0.BBM";
    constexpr auto paletti1 = "<RTTR_GAME>/GFX/PALETTE/PALETTI1.BBM";
    constexpr auto paletti8 = "<RTTR_GAME>/GFX/PALETTE/PALETTI8.BBM";
    constexpr auto resource = "<RTTR_GAME>/DATA/RESOURCE.DAT";
    constexpr auto rom_bobs = "<RTTR_GAME>/DATA/CBOB/ROM_BOBS.LST";
    constexpr auto setup013 = "<RTTR_GAME>/GFX/PICS/SETUP013.LBM"; // Optionen
    constexpr auto setup015 = "<RTTR_GAME>/GFX/PICS/SETUP015.LBM"; // Freies Spiel
} // namespace resources
} // namespace s25

const std::array<const std::string, 21> LOAD_SCREENS = {{"setup666", "setup667", "setup801", "setup802", "setup803", "setup804", "setup805",
                                                         "setup806", "setup810", "setup811", "setup895", "setup896", "africa",   "austra",
                                                         "europe",   "green",    "japan",    "namerica", "nasia",    "samerica", "sasia"}};

constexpr unsigned NUM_GFXSETS = 3;
constexpr unsigned NUM_NATIONS = 5;

const std::array<const std::string, NUM_NATIONS> NATION_ICON_IDS = {{"afr_icon", "jap_icon", "rom_icon", "vik_icon", "bab_icon"}};

const helpers::MultiArray<const std::string, 2, NUM_NATIONS> NATION_GFXSET_Z = {
  {{"afr_z", "jap_z", "rom_z", "vik_z", "bab_z"}, {"wafr_z", "wjap_z", "wrom_z", "wvik_z", "wbab_z"}}};

const std::array<const std::string, NUM_GFXSETS> MAP_GFXSET_Z = {{"MAP_0_Z", "MAP_1_Z", "MAP_2_Z"}};

const std::array<const std::string, NUM_GFXSETS> TEX_GFXSET = {{"TEX5", "TEX6", "TEX7"}};

RTTR_POP_DIAGNOSTIC

#endif // FILES_H_INCLUDED
