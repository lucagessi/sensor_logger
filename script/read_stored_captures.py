import json
import sys
import serial
import numpy as np
import struct
import pandas as pd
from datetime import datetime

df = pd.read_json( "dataset_28-08-2022 08:35.json" )

print(df)
cell = df.iloc[0]['x']

print("Printing x value example")
print(cell)
print("Printing x single values")
print(cell[0])