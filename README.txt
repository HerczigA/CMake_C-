It is a simple repo for practising of usage cmake and developing c++ skills.
The basic concept is making a generic raspberry pi software for those adafruit devices and chinese sensors and actuators.
Moreover try to make communication with smarter devices also (STM/MSP430 etc...) via SPI, I2C, UART and Bluetooth.
For using this devices I plan to use a simple JSON to reading the parameters which are IDs, names, device type and communication type. 
Of course it is very easy and simple, but I plan to expand this JSON parsing wih more informations (e.g. databits for communcitons and
connection between devices sensor-actuator pairs ). 
Next to that I make different functions to using this devices, different type of reading and writing functions. 

As I mentioned I use cmake, but I do not want to typing always long cmake arguments for building and compiling in terminal. 
Therefore I made a simple python script which makes my life much easier. I can generating important cmake environment and building easily 
with this "super" python script. Also I can remove easily unnecessary files after compiling with this script. Important to know, it is in a 
early state so there are so many possibilities what I would like to integrate into this in the future. But for sure it works!

To use type this "./build.py -c -b  ". However there is a little info for this if you type "./build.py --help". Feel free to use.

Future plan:
- Adding a simple database for the datas what will be measured.
- Reading from these datas from database via online page on a secure and providing channel.
- Adding logger to check if there is some errors.
- Making better all the communication types.
- Make remote controlling .