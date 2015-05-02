RGB LED accumulator tank temperature display with Raspberry Pi GPIO
===================================================================

An example of how to display to display your accumulator tank temperatures on 
commonly available 64x32 RGB LED panel with the Raspberry Pi. 

The temperature exaple is (c) Andreas Kingbäck <andreas@flighttronics.se> with
GNU General Public License Version 2.0 <http://www.gnu.org/licenses/gpl-2.0.txt>

The LED-matrix library is (c) Henner Zeller <h.zeller@acm.org> with
GNU General Public License Version 2.0 <http://www.gnu.org/licenses/gpl-2.0.txt>

The curlcpp is Copyright (c) 2014 - Giuseppe Persico

The example code is released in the public domain.

Overview
--------

In my house we are using a log boiler to heat water. Heated water is stored in three accumulator tanks. 
One 500L and two 750L. Water is pumped from the log boiler to the first 500L tank and then it is pumped 
the other two tanks with a transfer pump. 

All three accumulator tanks has three temperature probes top, middle and bottom. Nine DS18B20 digital temperature 
sensors are connected to my AlmUSBIO board. The AlmUSBIO board is then connected to a Raspberry Pi via USB.
Raspberry Pi is running a web server to display the temperatures and supply data via a text file used by this project.

The 64x32 LED-matrix from [AdaFruit] id driven by a level converter board and the Raspberry Pi 2.

<a href="img/tempbars.jpg"><img src="img/tempbars.jpg" width="300px"></a>

Why
---

As we are a little lazy and don't want go out the the boiler room to check the temperatures every now and then, 
so we decided to get the temps on a web-page and a simple LED-display. We could have used a simple TFT but a LED
is more fun. 

Level converter board
---------------------

More info as soon as I get the PCB. 
Display is now connected directly to the Pie but with some flickering.

Software application
--------------------

Software is still in beta. It uses LED-matrix library to drive the display and Curl to get data from a text file 
that is stored on the server in the log boiler room (More info about that later).

Check out the [logitempmatrix.cc](./src/logitempmatrix.cc) to get started 



