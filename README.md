# sensor_logger
## Serial interface
Functions for getting serial available similar to Arduino framework but simplier. Interface with:
- init( void ). Default and fixed baudrate at first.
- write(string). Write string to output
- available(). Return available char to read
- read( string, N ). Append N character to string
Low level driver function to be implemented or called inside interrupt:
- write(char *, N). Write directly to output
- appendChar(char c). Append new read char to buffer.

## Accelerometer interface
Accelerometer interface:
- init
- set_odr: dummy at first
- get_config
- available: return data available to be read
- read(xyz, N). Write to xyz N*3 accelerometer sensor data. xyz is an union with array with different format data.
    Depending on the configuration it return a specifc format. float, 8 bit, ecc

## Serial command interface
The accelerometer exposes some command in order for the host to interact with it:
- single N: command used to acquire N seconds of accelerometer data
- rcfg: return configuration parameter of accelerometer in human readable format.
- start: start infinite acquisition
- stop: stop infinite acquisition
- wpar A VV: write param with address A and new value VV
- rpar A: read parameter with address A actual value
- thr N: return N second of an acquisition started when a motion event has occured. The start time of acquisition depends on an other parameter which set the time before event to acquire.

### Single N command
Host writes: single N
Sensor writes a packet formatted based on the current configuration. Default configuration use float data types m/s<sup>2</sup> and 50 Hz ODR.

### rcfg command
Return actual module configuration in the format:
- ODR: XXXHz. First value ODR: 50Hz for example
- format: float m/s<sup>2</sup>. Default value for format which is float per axis as m/s<sup>2</sup>

## Parameters list