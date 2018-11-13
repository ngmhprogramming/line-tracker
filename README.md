# line-tracker
Line tracking car with Arduino, which attempts to follow a black duct tape line on a white background.

# How it works
- Two colour sensors check if they are above the line or not
- They are calibrated first by taking 100 samples at 20 millisecond intervals
- This is because readings would vary base on the surroundings and the sensors are low quality
- If one side is off, it corrects the motion by turning until both are on the line, to prevent the car from "escaping"
- If both sides are similar, the car is on the line, or the sensors are placed accross the line, so it moves forward

# Hardware
- TCS230 / TCS3200 Colour Sensor
  - Left
    - S2 - Digital Pin 2
    - OUT - Digital Pin 3
  - Right
    - S2 - Digital Pin 4
    - OUT - Digital Pin 5
  - Only one input is used as it is black and white
- L9110 Motor Driver
  - IA2 (A-IA) - Analog Pin 0
  - IB2 (A-IB) - Analog Pin 1
  - IA1 (B-IA) - Analog Pin 2
  - IB1 (B-IB) - Analog Pin 3
