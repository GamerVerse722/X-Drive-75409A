import itertools

# Motor base RPMs
motor_5_5w = 200
motor_11w_options = [100, 200, 600]

# Available gears
gears = [12, 24, 36, 48, 60, 72, 84]

tolerance = 0.001  # allow floating point tolerance

def output_rpm(motor_rpm, driver, driven):
    return motor_rpm * (driver / driven)

matches = []

for gear_5_driver, gear_5_driven in itertools.product(gears, gears):
    rpm_5 = output_rpm(motor_5_5w, gear_5_driver, gear_5_driven)

    for motor_11 in motor_11w_options:
        for gear_11_driver, gear_11_driven in itertools.product(gears, gears):
            rpm_11 = output_rpm(motor_11, gear_11_driver, gear_11_driven)

            if abs(rpm_5 - rpm_11) < tolerance:
                matches.append({
                    "5.5W": (gear_5_driver, gear_5_driven),
                    "11W_motor_rpm": motor_11,
                    "11W_gears": (gear_11_driver, gear_11_driven),
                    "final_rpm": rpm_5
                })

# Print results
for match in matches:
    if match["final_rpm"] == 400:
        print(match)

print(f"\nTotal matches found: {len(matches)}")
