#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);

void parkCar(Arguments *in, Reply *out);
RPCFunction rpcPark(&parkCar, "parkCar");
int car_run;

int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   printf("%s\n", buf);
   RPC::call(buf, outbuf);
   printf("%s\r\n", outbuf);
   }
}

void parkCar(Arguments *in, Reply *out){
   int d1 = in->getArg<int>();
   int d2 = in->getArg<int>();
   const char *dire = in->getArg<const char*>();

   //d2
   car_run = 0;
   car.goStraight(-50);
   while(car_run < d2) { ThisThread::sleep_for(200ms); car_run++; }
   car.stop();
   ThisThread::sleep_for(1000ms);

   if (strcmp(dire, "west") == 0) {
      car.turn(100, -0.2);
   }else if (strcmp(dire, "east") == 0) {
      car.turn(100, 0.2);
   }
   ThisThread::sleep_for(700ms);
   car.stop();
   ThisThread::sleep_for(1000ms);

   //d1
   car_run = 0;
   car.goStraight(-50);
   while(car_run < d1) { ThisThread::sleep_for(200ms); car_run++; }
   car.stop();
   ThisThread::sleep_for(1000ms);
}