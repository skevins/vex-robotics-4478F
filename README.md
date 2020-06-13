# Who are we?
We are 4478F, a VRC team from Masuk High School. We have plenty more teams.

# About the code
This code is for our bot that uses x-drive. For that, the code includes position tracking (odometry), and field-centric programming.

Field-centric driving is different from bot-centric driving. For example, if you have a bot with tank drive, and you tell it to move forward, it moves forward. Then, if you tell it to turn, then move forward, it will turn, and move where it thinks is forward, which is parallel to the wheels. The driver needs to understand this, because when they say forward, the robot moves towards its own forward. With field-centric driving, when the robot is told to move forward, it will move forward relative to the driver, not itself (forward relative to the driver is referenced as the robot/driver's "north" in the code).  This is especially important when using any holonomic drive, like x-drive, since the ability to turn while moving straight can be hard to control (while robot-centric).
