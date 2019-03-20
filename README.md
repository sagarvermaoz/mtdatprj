# mtdatprj
mtdata assigment

# Brief
It reads the data being output by the PacificScales_Simulator_1.0.
The serial pot baudrate is set to 9600 and the com port device is configurable via the command line
Its tested using the Tnt VCP emulator, one end being fed by the python app and other enf being consumed by mtdata app.

# Usage 
./MtdataApp -p port
e.g. ./MtdataApp -p /dev/tnt2

# Build
clone the complete repo to a directory and give following commands-
$ make clean
$ make all

The MtdataApp executable will get generated in the CWD, no special packages necessary to be instatted, its a completely self contained code.
