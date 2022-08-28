import json
import sys
import serial
import numpy as np
import struct
import pandas as pd
from datetime import datetime

f = open("config.json")

cfg = json.load( f )
portname = cfg["portname"]
baudrate = cfg["baudrate"]

odr = cfg["odr"]
sample_format = 'f'
bytes_per_samples = cfg["bytes_per_samples"]

df_cols = ['class', 'x','y','z']

df = pd.DataFrame(data=None, columns=df_cols)

print("odr: " +str(odr) +" Hz")
print("bytes per samples (3 axis): "+str(bytes_per_samples))

print("Classes found: "+str( len(cfg["classes"]) ))

for i in range(0, len(cfg["classes"])):
    c = cfg["classes"][i]
    print( "Class "+str(i)+": "+str(c) )

# Try opening serial
print("Opening port: "+str(portname))
print("Baudrate: "+str(baudrate))

try:
    ser = serial.Serial(port = portname, baudrate = baudrate) 
except:
    print("Error opening serial post")
    sys.exit()
finally:
    pass

# Select class index to capture
try:
    sel_class_idx = int(input("Select class:"))
except:
    print("Class must be integer index")
    sys.exit()

if sel_class_idx < 0 or sel_class_idx >= len(cfg["classes"]):
    print("Class index is not valid")
    sys.exit()
else:
    print("Selected class: "+str(cfg["classes"][sel_class_idx]))

# Select number of seconds to acquire
try:
    seconds = int(input("How many seconds per capute? [1 to 10 seconds] "))
except:
    print("Seconds must be integer index")
    sys.exit()

if seconds < 1 or seconds > 10:
    print("Seconds must be from 1 to 10!")
    sys.exit()
else:
    print("Choosen "+str(seconds)+" seconds per capture")

ser.timeout = seconds * 1.5
bytes_to_read = odr*seconds*bytes_per_samples
num_samples = odr*seconds

def single():
    global seconds
    global bytes_to_read
    global num_samples
    command = "single "+str(seconds)
    #print("Sending command: "+command)
    ser.write( (command).encode('utf-8') )
    raws = ser.read(bytes_to_read)
    if len(raws) != bytes_to_read:
        #print("Error reading data. Read "+str(len(raws)+" bytes"))
        return None
    #print( raws )
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
    return {"x" : x, "y" : y, "z" : z}

goon = True
num_captures = 0
while goon:
    capture_error = False
    print("\n  Starting capture!")
    capture = single()
    is_valid = False
    save_capture = True
    if capture == None:
        capture_error = True
        print("Error during capture!")
        save_capture = False
        while is_valid == False:
            print("\nChoose an option:")
            print("  c: retry")
            print("  e: save and exit")
            cmd = input("")
            if cmd == "c":
                is_valid = True
            elif cmd == "e":
                is_valid = True
                goon = False
            else:
                print("Input not valid")
    else:
        while is_valid == False:
            print("\nChoose an option:")
            print("  c: save this capture and continue")
            print("  d: delete this capture and continue")
            print("  e: save this capture and exit")
            print("  x: delete this capture and exit")
            cmd = input("")
            if cmd == "c" or cmd == "":
                is_valid = True
            elif cmd == "d":
                is_valid = True
                save_capture = False
                goon = True
            elif cmd == "e":
                is_valid = True
                save_capture = True
                goon = False
            elif cmd == "x":
                is_valid = True
                save_capture = False
                goon = False
            else:
                print("Input not valid")
    if save_capture:
        print("Saving capture to dataframe")
        row = { "class": sel_class_idx, "x" : [capture["x"]], "y" : [capture["y"]], "z" : [capture["z"]] }
        row = pd.DataFrame(data=row)
        print(row)
        df = pd.concat( [df, row], ignore_index=True )
        num_captures = num_captures + 1
        print("\nNum of capture registered :"+str(num_captures))


now = datetime.now()
df_name = "capture_ODR"+str(odr)+"_SECS"+str(seconds)+"_CLASS"+str(sel_class_idx)+"_N"+str(num_captures)+"_"+now.strftime("%d-%m-%Y %H:%M")+".json"

print("Saving dataframe file to disk: "+str(df_name))

#df.to_csv(df_name, index=False)
#df.reset_index(inplace=True)
#data = df.to_dict(orient='split')
#print(data)
print( df )
df.to_json(df_name)
