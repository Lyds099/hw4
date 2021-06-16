import pyb, sensor, image, time, math

enable_lens_corr = False
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)

find = 0
while(True):
   img = sensor.snapshot()
   if enable_lens_corr: img.lens_corr(1.8) # for 2.8mm lens...
   for line in img.find_line_segments(merge_distance = 200, max_theta_diff = 200):
       img.draw_line(line.line(), color = (255, 255, 0))
       uart.write("/goStraight/run -50 \n".encode())
       uart.write(("#x1:%d\r\n" % line.x1()).encode())
       uart.write(("#x2:%d\r\n" % line.x2()).encode())
       uart.write(("#y1:%d\r\n" % line.y1()).encode())
       uart.write(("#y2:%d\r\n" % line.y2()).encode())
       find = 1
   if find==0 :
       uart.write("/stop/run \n".encode())


