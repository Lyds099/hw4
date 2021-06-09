import pyb, sensor, image, time, math

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
THRESHOLD = (0, 110)

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)

while(True):
   img = sensor.snapshot().binary([THRESHOLD])
   line = img.get_regression([(255,255)], robust = True)
   if(line):
       rho_err = abs(line.rho())-img.width()/2
       if line.theta()>90:
           theta_err = line.theta()-180
       else:
           theta_err = line.theta()
   img.draw_line(line.line(), color = 127)
   if(abs(theta_err)>30):
      if(theta_err<0):
         print("l")
      else if(theta_err>0):
         print("r")
   else:
      print("o")

