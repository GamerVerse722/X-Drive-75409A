#include "userapi/driver/chassis.hpp"
#include "pros/motor_group.hpp"

#include <cmath>

namespace xDrive {
    #define DEG_TO_RAD (M_PI / 180.0)

    Chassis::Chassis(
        const std::vector<std::int8_t> frontLeft,
        const std::vector<std::int8_t> frontRight,
        const std::vector<std::int8_t> backLeft,
        const std::vector<std::int8_t> backRight,
        const std::uint8_t imu_port,
        int rpm)
        : fl(frontLeft, pros::MotorGearset(rpm)),
        fr(frontRight, pros::MotorGearset(rpm)),
        bl(backLeft, pros::MotorGearset(rpm)),
        br(backRight, pros::MotorGearset(rpm)),
        imu(imu_port) {}
            
    Chassis::Chassis(
        std::int8_t frontLeft,
        std::int8_t frontRight,
        std::int8_t backLeft,
        std::int8_t backRight,
        std::int8_t imu_port,
        int rpm)
        : fl({frontLeft}, pros::MotorGearset(rpm)),
        fr({frontRight}, pros::MotorGearset(rpm)),
        bl({backLeft}, pros::MotorGearset(rpm)),
        br({backRight}, pros::MotorGearset(rpm)),
        imu(imu_port) {}

    void Chassis::calibrate() {
        imu.reset();
        while (imu.is_calibrating()) {
            pros::delay(10);
        }

        heading_offset = imu.get_rotation();
        target_heading = heading_offset;
    }

    void Chassis::setPower(double fl_p, double fr_p, double bl_p, double br_p) {

        double max_val = fmax(fabs(fl_p),
                    fmax(fabs(fr_p),
                    fmax(fabs(bl_p),
                            fabs(br_p))));

        if (max_val > 127) {
            fl_p = fl_p / max_val * 127;
            fr_p = fr_p / max_val * 127;
            bl_p = bl_p / max_val * 127;
            br_p = br_p / max_val * 127;
        }

        fl.move(fl_p);
        fr.move(fr_p);
        bl.move(bl_p);
        br.move(br_p);
    }

    void Chassis::drive(double forward, double strafe, double rotate_input) {

        double current_heading = imu.get_rotation();

        // Field-centric transform
        double heading = (current_heading - heading_offset) * DEG_TO_RAD;

        double temp = forward * cos(heading) + strafe * sin(heading);
        strafe = -forward * sin(heading) + strafe * cos(heading);
        forward = temp;

        double rotate = rotate_input;

        // ----- Heading Hold -----
        if (fabs(rotate_input) < heading_deadband) {

            double error = target_heading - current_heading;

            // Wrap to [-180, 180]
            if (error > 180) error -= 360;
            if (error < -180) error += 360;

            rotate = error * kP_heading;

        } else {
            target_heading = current_heading;
        }

        // X-drive math
        double fl_p = forward + strafe + rotate;
        double fr_p = forward - strafe - rotate;
        double bl_p = forward - strafe + rotate;
        double br_p = forward + strafe - rotate;

        setPower(fl_p, fr_p, bl_p, br_p);
    }
}