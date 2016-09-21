# EmbeddedSystemProject
This Project has been developped on PSoC 4 in the IDE "PSoC Creator". The code is in C.

The project was made in collaboration with The Symme Lab in Annecy, France. This lab develops one of the best current today energy havester and wants to create a start-up. 
My project is to develop a very low-power embedded system which has to be powered up by this harvester.
The key point is so that it has to consume as less energy as possible. It was made possible in particular due to cyclic sleep of all the components.

This small system cyclically and wirelessly send data from an accelerometer.
This code allows the microcontroller PSoC 4 to take data from the accelerometer ADXL345 and send it with Xbee (Selected because it is used a lot in industry and we wanted an "industriable" demonstrator).
In this code, you can find the one for the transmitter system and the one for the receiver system (composed of an Xbee and a PSoC 4).





