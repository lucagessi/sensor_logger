import json
import sys
import serial
import numpy as np
import struct
import pandas as pd
from datetime import datetime

df = pd.read_csv( "capture_c1_27-08-2022 11:06.csv" )

print(df)
x = df.x.str.split(' ', expand=True).apply(pd.to_numeric, errors='coerce').values
#df.iloc[0]['x']
print("Printing x value example")
print(x)
print("Printing x single value")
print(x[0][1])