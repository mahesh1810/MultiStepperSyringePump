# MultiStepperSyringePump

This repo contains Arduino code to operate multiple stepper motors for their application as an automatic syringe pump.

Serial Inputs:
a---> Enter linear distance linear guide 'a' needs to move :
b---> Enter linear distance linear guide 'b' needs to move :
g---> Run motor 'a' by specific distance then wait for 'period' and then run motor 'b' by specific distance. Note: specific distances are hard coded and can be changed by modifying the code
s---> Stop all the motors

Output:
- multiple stepper motors run individually and/or simultaneously depending on the serial input.
