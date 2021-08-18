# MultiStepperSyringePump

This repo contains an Arduino code to operate multiple stepper motors for their application as an automatic syringe pump.

Serial Inputs:  
a---> Enter distance linear guide 'a' has to move in mm :  
b---> Enter distance linear guide 'b' has to move in mm :  
g---> Run motor 'a' by a specific distance then wait for a 'period' and then run motor 'b' by a specific distance. Note: specific distances are hard coded and can be changed by modifying the code  
s---> Stop all the motors   

Output:
- multiple stepper motors run individually and/or simultaneously depending on the serial input.

Check out the system in operation: https://www.youtube.com/watch?v=T5XUcyTErbg&ab_channel=maheshlokhande

<img src="images/20210818_131010.jpg" width="500" height="1000">
