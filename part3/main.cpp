#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"
DigitalInOut ping(D12);
Timer t;

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

BBCar car(pin5, pin6, servo_ticker);

int angle;
int count=0;

int main() {
   float val;
   pc.set_baud(9600);
   uart.set_baud(9600);
   int buf_index = 0;
   char buf[20];
   while(1){
      if(uart.readable()){                                                    
            char recv[1];
            uart.read(recv, sizeof(recv));                              
            //pc.write(recv, sizeof(recv));
            if(recv[0]=='l'){
               car.stop();
               car.turn(-100, 0.2);
               ThisThread::sleep_for(400ms);
               car.stop();
            }else if(recv[0]=='r'){
               car.stop();
               car.turn(-100, -0.2);
               ThisThread::sleep_for(400ms);
               car.stop();
            }else if(recv[0]=='o'){
               car.goStraight(-100);
               ThisThread::sleep_for(1000ms);
               car.stop();
            }else{
               car.stop();
            }
            if(count<10) count++;
            else{
               count = 0;
               ping.output();
               ping = 0; wait_us(200);
               ping = 1; wait_us(5);
               ping = 0; wait_us(5);
               ping.input();
               while(ping.read() == 0);
               t.start();
               while(ping.read() == 1);
               val = t.read();
               sprintf(buf, "Ping = %lf\r\n", val*17700.4f);
               pc.write(buf, sizeof(buf));
               t.stop();
               t.reset();                                                                                                              
            }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
      }
   }
}