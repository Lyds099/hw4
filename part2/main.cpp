#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

BBCar car(pin5, pin6, servo_ticker);

void follow_line(char* dire);
Thread followL_Thread(osPriorityLow);

int main() {
   uart.set_baud(9600);
   int buf_index = 0;
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            //pc.write(recv, sizeof(recv));
            followL_Thread.start(&follow_line(recv));
      }
   }
}

void follow_line(char* dire){
   if((strcmp(dire, "l") == 0){
      car.stop();
      car.turn(100, 0.2);
      ThisThread::sleep_for(200ms);
      car.stop();
   }else if((strcmp(dire, "r") == 0){
      car.stop();
      car.turn(100, -0.2);
      ThisThread::sleep_for(200ms);
      car.stop();
   }else if((strcmp(dire, "o") == 0){
      car.goStraight(50);
   }else{
      car.stop();
   }
}