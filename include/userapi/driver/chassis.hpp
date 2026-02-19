#pragma once

#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include <vector>

namespace xDrive {
    class Chassis {
        private:
            pros::MotorGroup fl;
            pros::MotorGroup fr;
            pros::MotorGroup bl;
            pros::MotorGroup br;

            pros::Imu imu;

            double heading_offset = 0;
            double target_heading = 0;

            double kP_heading = 1.5;   // Tune this
            double heading_deadband = 5;

            void setPower(double fl_p, double fr_p, double bl_p, double br_p);

        public:
            Chassis(const std::vector<std::int8_t> frontLeft,
                    const std::vector<std::int8_t> frontRight,
                    const std::vector<std::int8_t> backLeft,
                    const std::vector<std::int8_t> backRight,
                    const std::uint8_t imu_port,
                    int rpm);
            
            Chassis(std::int8_t frontLeft,
                    std::int8_t frontRight,
                    std::int8_t backLeft,
                    std::int8_t backRight,
                    std::int8_t imu_port,
                    int rpm);

            void calibrate();
            void drive(double forward, double strafe, double rotate_input);
    };
}