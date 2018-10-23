import serial

ser = serial.Serial("/dev/tty.Setareh-DevB")
ser.write(chr(int(115)))
ser.write(chr(int(0)))
ser.write(chr(int(0)))
ser.write(chr(int(0)))
ser.write(chr(int(0)))
ser.write(chr(int(0)))