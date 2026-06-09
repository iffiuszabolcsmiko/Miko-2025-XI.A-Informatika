from hub import port, motion_sensor
import motor_pair
import runloop

# --- MOTOR PÁROSÍTÁS ---
motor_pair.pair(motor_pair.PAIR_1, port.A, port.B)

# --- KONFIG ---
STEP_CM = 10
TURN_SPEED = 25
TURN_ANGLE = 90

# --- MOZGÁS ---
def move_forward(cm):
    motor_pair.move_for_degrees(
        motor_pair.PAIR_1,
        cm * 360,# közelítés: 360° ≈ 1 kerékfordulat
        0,
        velocity=300
    )

def draw_forward(cm):
    # itt lehetne filc le/fel
    motor_pair.move_for_degrees(
        motor_pair.PAIR_1,
        cm * 360,
        0,
        velocity=300
    )

# --- GIROSKÓPOS FORDULÁS ---
def turn(angle):
    motion_sensor.reset_yaw(0)

    if angle > 0:   #jobbra
        motor_pair.move(motor_pair.PAIR_1, 0, velocity=TURN_SPEED)
        while motion_sensor.tilt_angles()[0] < angle * 10:
            pass
    else:   #balra
        motor_pair.move(motor_pair.PAIR_1, 0, velocity=-TURN_SPEED)
        while motion_sensor.tilt_angles()[0] > angle * 10:
            pass

    motor_pair.stop(motor_pair.PAIR_1)

# --- INTERPRETER ---
def execute(commands):
    step = STEP_CM

    for c in commands:

        if c == 'D':
            draw_forward(step)
        elif c == 'M':
            move_forward(step)
        elif c == '+':
            turn(TURN_ANGLE)
        elif c == '-':
            turn(-TURN_ANGLE)
        elif c == '|':
            turn(180)
        elif c == '>':
            step += 1
        elif c == '<':
            step = max(1, step - 1)

# --- FŐ PROGRAM ---
async def main():
    execute("D+D+D+D")

runloop.run(main())
