#include "userapi/configuration.hpp"

#include "automonous.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"

#include "gamers-forge/automanager.hpp"

#include "pros/misc.hpp"
#include "userapi/ui/autom/mode_selector.hpp"
#include "userapi/ui/autom/location_selector.hpp"

namespace devices {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
}

namespace configuration::drive {
    using namespace devices;

    void default_constants() {
    }

    void initialize() {
    }
}

namespace configuration::controls {
    BMapper::ButtonHandler button_handler(devices::master);

    void configure() {
        using pros::controller_digital_e_t;
    }
} 

namespace configuration::autonomous {
    void configure() {
        using namespace ui::autom;

        location_selector::initialize();
        mode_selector::initialize();

        AutoManager::register_autom(AutomMode::QUALIFICATIONS, AutomColor::RED, AutomPosition::LEFT, autom::Qualifications::left);
        AutoManager::register_autom(AutomMode::QUALIFICATIONS, AutomColor::RED, AutomPosition::RIGHT, autom::Qualifications::right);
        AutoManager::register_autom(AutomMode::QUALIFICATIONS, AutomColor::BLUE, AutomPosition::LEFT, autom::Qualifications::left);
        AutoManager::register_autom(AutomMode::QUALIFICATIONS, AutomColor::BLUE, AutomPosition::RIGHT, autom::Qualifications::right);

        AutoManager::register_autom(AutomMode::ELIMINATIONS, AutomColor::RED, AutomPosition::LEFT, autom::Eliminations::left);
        AutoManager::register_autom(AutomMode::ELIMINATIONS, AutomColor::RED, AutomPosition::RIGHT, autom::Eliminations::right);
        AutoManager::register_autom(AutomMode::ELIMINATIONS, AutomColor::BLUE, AutomPosition::LEFT, autom::Eliminations::left);
        AutoManager::register_autom(AutomMode::ELIMINATIONS, AutomColor::BLUE, AutomPosition::RIGHT, autom::Eliminations::right);

        AutoManager::register_autom(AutomMode::SKILLS, AutomColor::COLOR_NONE, AutomPosition::NO_POSITION, autom::Skills::skills2);

        AutoManager::register_autom(AutomMode::NONE, AutomColor::COLOR_NONE, AutomPosition::NO_POSITION, autom::None::none);
    }
}