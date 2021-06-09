#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "string.h"

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);

DigitalIn encoder(D11);
volatile int steps;
volatile int last;

void parkCar(Arguments *in, Reply *out);
RPCFunction rpcPark(&parkCar, "parkCar");

void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

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
   encoder_ticker.attach(&encoder_control, 10ms);
   double d1 = in->getArg<double>();
   double d2 = in->getArg<double>();
   const char *dire = in->getArg<const char*>();

   //d2
   steps = 0;
   last = 0;
   car.goStraight(-50);
   while(steps*6.5*3.14/32 < (int)d2) { ThisThread::sleep_for(20ms); }
   car.stop();
   ThisThread::sleep_for(500ms);

   if (strcmp(dire, "west") == 0) {
      car.turn(100, -0.3);
   }else if (strcmp(dire, "east") == 0) {
      car.turn(100, 0.3);
   }
   ThisThread::sleep_for(700ms);
   car.stop();
   ThisThread::sleep_for(500ms);

   //d1
   steps = 0;
   last = 0;
   car.goStraight(-50);
   while(steps*6.5*3.14/32 < (int)d1) { ThisThread::sleep_for(20ms); }
   car.stop();
   ThisThread::sleep_for(500ms);
}