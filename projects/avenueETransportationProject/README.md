# Description:

For the AvenueE Transportation Project, I worked in a team of three UC Davis students to design, build and present a vehicle safety system using an Arduino starter kit.  We went from brainstorming to a working prototype in 4 days. 

We came up with a Drowsy Drifting Detection System, which monitors a vehicle's turning and sounds a subtle alarm whenever the car veers significantly in a direction the driver hasn't signaled.  This will alert fatigued drivers before absently drifting into a nearby lane becomes an accident. 

As the lead programmer, I wrote the embedded C/C++ firmware that reads the turn signal inputs, compares them in real time and triggers the alarm. I also assisted with the circuit design and intergrating the hardware.

# How It Works:

The crux of the firmware is a series of four timers.
Every time the first goes off, the position of the joystick is checked and the position of the wheels is updated if needed.
The second and third determine when the blinkers are triggered and how often they flash.
The fourth timer continuously compares the position of the wheels to the state of the blinkers, and will sound the buzzer if the wheels are turned incorrectly.