import serial
import matplotlib.pyplot as plt
import sys
import numpy as np
import struct

portname = '/dev/ttyUSB0'

try:
    ser = serial.Serial(port = portname, baudrate = 115200) 
except:
    print("Error opening serial post")
    sys.exit()
finally:
    pass
seconds = 3
odr = 25
sample_format = 'f'
bytes_per_samples = 4*3
bytes_to_read = odr*seconds*bytes_per_samples
num_samples = odr*seconds

print("Reading " + str(bytes_to_read) + " bytes from accelerometer")

ser.timeout = seconds * 1.5
command = "single "+str(seconds)
print("Sending command: "+command)
ser.write( (command).encode('utf-8') )
raws = ser.read(bytes_to_read)
if len(raws) != bytes_to_read:
    print("Error reading data. Read "+str(len(raws)+" bytes"))
    sys.exit()
print( raws )
x = np.zeros(num_samples)
y = np.zeros(num_samples)
z = np.zeros(num_samples)
idx_sample = 0
## Decode rx data
for idx in range(0, bytes_to_read, bytes_per_samples):
    v = struct.unpack(sample_format, raws[idx:idx+4])
    x[idx_sample] = v[0]
    v = struct.unpack(sample_format, raws[idx+4:idx+8])
    y[idx_sample] = v[0]
    v = struct.unpack(sample_format, raws[idx+8:idx+12])
    z[idx_sample] = v[0]
    idx_sample = idx_sample + 1

t = np.arange(num_samples) / odr

plt.plot(t, x)
plt.plot(t, y)
plt.plot(t, z)
plt.ylabel('Acceleration [mg]')
plt.xlabel('Time [s]')
plt.show()

sys.exit()
ser.write(b'hello') 

