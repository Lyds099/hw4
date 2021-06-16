1.how to setup and run your program  
Part1  
&emsp;&emsp;(1)Clone the repo: $ git clone https://github.com/Lyds099/hw4.git  
&emsp;&emsp;(2) $ cd part1  
&emsp;&emsp;(3)Compile the program: $ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f  
&emsp;&emsp;(4)Open the screen for main.cpp: $ sudo screen /dev/ttyACM0  
&emsp;&emsp;(5)Open the screen for Xbee host: $ sudo screen /dev/ttyUSB0  
&emsp;&emsp;(6)Typy RPC command in Xbee host: parkCar/run d1 d2 east/west  
&emsp;&emsp;(7)The car will start reverse parking.  
Part2  
&emsp;&emsp;(1)Clone the repo: $ git clone https://github.com/Lyds099/hw4.git  
&emsp;&emsp;(2) $ cd part2  
&emsp;&emsp;(3)Compile the program: $ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f  
&emsp;&emsp;(4)Open openMV and execute line.py  
&emsp;&emsp;(5)Aim the camera at the paper with line  
&emsp;&emsp;(6)The car will turn left/right or go stright according to the position of line, and send the parameters of the detected line(x1, y1, x2, y2) to mbed through UART.  
Part3  
&emsp;&emsp;(1)Clone the repo: $ git clone https://github.com/Lyds099/hw4.git  
&emsp;&emsp;(2) $ cd part3 
&emsp;&emsp;(3)Compile the program: $ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f  
&emsp;&emsp;(4)Open openMV and execute AprilTag.py  
&emsp;&emsp;(5)Aim the camera at Apriltag  
&emsp;&emsp;(6)The car will turn left/right or go stright according to the position of Apriltag.  
&emsp;&emsp;(7)Print the distance measured by PING on screen.  
2.what are the results  
Part1  
&emsp;&emsp;demo video:  
Part2  
&emsp;&emsp;demo video:  
Part3  
&emsp;&emsp;demo video:  