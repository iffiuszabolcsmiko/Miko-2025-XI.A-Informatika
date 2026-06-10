from hub import port, motion_sensor
import motor_pair
import color_sensor
import runloop

motor_pair.pair(motor_pair.PAIR_1, port.A, port.C)

TURN_SPEED = 100
DRIVE_SPEED = 360
DEGREES_PER_CM = 20# kalibrálandó!

class LSystem:

    def __init__(self, axiom, angle=90, step=5):
        self.axiom = axiom
        self.commands = axiom
        self.rules = {}

        self.angle = angle
        self.step = step

    def add_rule(self, pattern, replacement):
        self.rules[pattern] = replacement

    def apply_rules(self, iterations):

        current = self.commands

        for _ in range(iterations):

            result = []

            for c in current:

                if c in self.rules:
                    result.append(self.rules[c])
                else:
                    result.append(c)

            current = "".join(result)

        self.commands = current
        return current

    async def draw(self):
        await execute(
            self.commands,
            self.angle,
            self.step
        )

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
        while motion_sensor.tilt_angles()[0] < target:
            #print(motion_sensor.tilt_angles())
            await runloop.sleep_ms(5)
    else:
        motor_pair.move(motor_pair.PAIR_1, 100, velocity=TURN_SPEED)
        while motion_sensor.tilt_angles()[0] > target:
            await runloop.sleep_ms(5)

    motor_pair.stop(motor_pair.PAIR_1)

# --- INTERPRETER ---
async def execute(commands, turn_angle, step_length):

    step = step_length

    for c in commands:

        if c in ('F', 'G', 'D'):
            await draw_forward(step)

        elif c in ('M', 'f'):
            await move_forward(step)

        elif c == '+':
            await turn(turn_angle)

        elif c == '-':
            await turn(-turn_angle)

        elif c == '|':
            await turn(180)

        elif c == '>':
            step += 1

        elif c == '<':
            step = max(1, step - 1)

# --- FŐ PROGRAM ---
async def main():
    '''
    koch = LSystem(
        axiom="F",
        angle=90,
        step=2
    )

    koch.add_rule(
        "F",
        "F+F-F-F+F"
    )

    koch.apply_rules(3)

    print(koch.commands)

    await koch.draw()
    '''

    sier = LSystem(
        axiom="F-G-G",
        angle=120,
        step=5
    )

    sier.add_rule(
        "F",
        "F-G+F+G-F"
    )

    sier.add_rule(
        "G",
        "GG"
    )

    sier.apply_rules(2)

    await sier.draw()

    '''
    while True:
        print(motion_sensor.tilt_angles())
        await runloop.sleep_ms(500)
    '''
runloop.run(main())
