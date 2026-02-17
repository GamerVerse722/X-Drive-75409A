#pragma once

#include "gamers-forge/bmapper.hpp"

#include "pros/misc.hpp"


namespace devices {
    extern pros::Controller master;
}

namespace configuration::drive {
    void default_constants();
    void initialize();
}

namespace configuration::controls {
    extern BMapper::ButtonHandler button_handler;

    void configure();
}

namespace configuration::autonomous {
    void configure();
}