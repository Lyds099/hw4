#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

BBCar car(pin5, pin6, servo_ticker);

void follow_line(char* buf);
Thread followL_Thread(osPriorityLow);
char buf[64];

int main() {
   uart.set_baud(9600);
   int buf_index = 0;
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            if(recv[0] == '\n') {
               followL_Thread.start(&follow_line(buf));
               memset(buf,'0',sizeof(buf));
               buf_index = 0;
            }
            else{
               buf[buf_index++] = recv[0];
            }
      }
   }
}

void follow_line(char* buf){
   if((strcmp(dire, "left") == 0){
      car.stop();
      car.turn(100, 0.2);
      ThisThread::sleep_for(200ms);
      car.stop();
   }else if((strcmp(dire, "right") == 0){
      car.stop();
      car.turn(100, -0.2);
      ThisThread::sleep_for(200ms);
      car.stop();
   }else if((strcmp(dire, "ok") == 0){
      car.goStraight(50);
   }
}