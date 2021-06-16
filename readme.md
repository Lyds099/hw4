1.how to setup and run your program  
Part1
&emsp;&emsp;(1)Clone the repo: $ git clone https://github.com/Lyds099/hw4.git  
&emsp;&emsp;(2) $ cd part1  
&emsp;&emsp;(3)Compile the program: $ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f  
&emsp;&emsp;(4)Open the screen for main.cpp: $ sudo screen /dev/ttyACM0  
&emsp;&emsp;(5)Open the screen for Xbee host: $ sudo python3 wifi_mqtt/mqtt_client.py  
&emsp;&emsp;(6)Typy RPC command in Xbee host: parkCar/run d1 d2 east/west  
&emsp;&emsp;(7)The car will start reverse parking.  

2.what are the results
Part1
