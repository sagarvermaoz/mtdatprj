# Mtdataprj
MtData assigment

# Brief
It reads the data being output by the PacificScales_Simulator_1.0 every 10 seconds.
The serial port baudrate is set to 9600 and the com port device is configurable via the command line.
Its tested using the tty0tty VCP emulator, one end being fed by the python app and other end being consumed by mtdata app.

The JSON formatted output is displayed on stderr. JSON library name is Parson and its a simple .h and .c file included in the repo itself.
JSON library git URL - 

https://github.com/kgabis/parson

# Build
Clone the complete repo to a directory and give following commands-

$ make clean

$ make all

The MtdataApp executable will get generated in the CWD, no special packages necessary to be instatted, its a completely self contained code.


# Usage 
sudo ./MtdataApp -p port

I used the virtual com port tty0tty, which provides a connected pair of virtual serial ports.

On Terminal 1                      

$ sudo ./MtdataApp -p /dev/tnt2   

On Terminal 2 (config : dev = /dev/tnt3 at 9600)
 
$ sudo python pacific_scales_simulator.py 


-- Screenshot is checked in into the repo to visualise the working of the application.




