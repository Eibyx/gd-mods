#pragma once

#include <Geode/loader/EventExport.hpp>
#include <Geode/loader/Mod.hpp>

#undef MY_MOD_ID
#define MY_MOD_ID "thesillydoggo.qolmod"

namespace qolmod::api
{
    GEODE_EVENT_EXPORT(void, enableAntiCheat, (geode::Mod* mod), (mod));
    GEODE_EVENT_EXPORT(void, disableAntiCheat, (geode::Mod* mod), (mod));

    inline void enableAntiCheat()
    {
        enableAntiCheat(geode::Mod::get());
    }

    inline void disableAntiCheat()
    {
        disableAntiCheat(geode::Mod::get());
    }
};
