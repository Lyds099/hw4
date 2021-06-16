#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"
DigitalInOut pin12(D12);

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

BBCar car(pin5, pin6, servo_ticker);

int angle;

int main() {
   parallax_ping  ping(pin12);
   pc.set_baud(9600);
   uart.set_baud(9600);
   int buf_index = 0;
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
               car.goStraight(-50);
            }else{
               car.stop();
            }                                                                                                               
            pc.write("ping:%f\n", (float)ping);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
      }
   }
}