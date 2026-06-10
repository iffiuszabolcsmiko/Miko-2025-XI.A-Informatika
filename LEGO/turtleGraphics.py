from hub import port, motion_sensor
import motor_pair
import color_sensor
import runloop

motor_pair.pair(motor_pair.PAIR_1, port.A, port.C)

STEP_CM = 5
TURN_SPEED = 100
DRIVE_SPEED = 360
TURN_ANGLE = 90
DEGREES_PER_CM = 20# kalibrálandó!

# --- MOZGÁS ---
async def move_forward(cm):
    await motor_pair.move_for_degrees(
        motor_pair.PAIR_1,
        int(cm * DEGREES_PER_CM),
        0,
        velocity=DRIVE_SPEED
    )

async def draw_forward(cm):
    await motor_pair.move_for_degrees(
        motor_pair.PAIR_1,
        int(cm * DEGREES_PER_CM),
        0,
        velocity=DRIVE_SPEED
    )

# --- FORDULÁS (giroszkopos) ---
async def turn(angle):
    motion_sensor.reset_yaw(0)
    await runloop.sleep_ms(50)# hadd álljon be a reset

    target = angle * 10 # tilt_angles tizedfokon ad vissza

    if angle > 0:
        motor_pair.move(motor_pair.PAIR_1, 100, velocity=-TURN_SPEED)
        while motion_sensor.tilt_angles()[0] < target:# [2] = yaw
            await runloop.sleep_ms(5)
    else:
        motor_pair.move(motor_pair.PAIR_1, 100, velocity=TURN_SPEED)
        while motion_sensor.tilt_angles()[0] > target:
            await runloop.sleep_ms(5)

    motor_pair.stop(motor_pair.PAIR_1)

# --- INTERPRETER ---
async def execute(commands):
    step = STEP_CM

    for c in commands:
        if c == 'D':
            await draw_forward(step)
        elif c == 'M':
            await move_forward(step)
        elif c == '+':
            await turn(TURN_ANGLE)
        elif c == '-':
            await turn(-TURN_ANGLE)
        elif c == '|':
            await turn(180)
        elif c == '>':
            step += 1
        elif c == '<':
            step = max(1, step - 1)

# --- FŐ PROGRAM ---
async def main():
    await execute("D+D+D+D")
    #while True:
        #print(motion_sensor.tilt_angles())
        #await runloop.sleep_ms(500)

runloop.run(main())
