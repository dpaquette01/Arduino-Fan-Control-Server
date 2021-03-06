Fan Control with Arduino Web Server

Update May 17, 2015 (about 3 years after last commit):
After having this on Apple’s App store for the past couple years I decided to stop paying the developer fee.
Also, just a heads up/warning to anyone who wants to use this: this was one of my first projects out of high school, so the quality is very poor.

If anyone is still interested, the Arduino code is still avialable here.
I have removed the iOS application from the app store, you can view the project in its entirety here: https://github.com/paquettedavid/ArduinoFanControl

This sketch allows the user to view:

-the current temperature of the room
-the max and min temp the room has reached
-the status of a connected fan(on, off, auto-on or auto-off)
-(the iPhone app allows control of the connected fan, such as turning it on, off or to auto, as well as displayed the data specified above.(can also be tested on basic web browser.

This Arduino sketch has been tested on the Arduino Uno Rev3 with
the Arduino Ethernet Shield Rev3.

This sketch is the server side of the software with the iPhone(or other web connected devices) as the client.

///Software

The sketch must be edited with YOUR specific IP address in place of the dummy one.
(I am currently using a global IP address so the server can be accessed from anywhere in the world. My router is set up to forward the http web sharing port, a google search can show how simple this is)
A local IP address (such as 192.168.1.2) is the more common and simple way to set it up.

Once you have edited the sketch with your IP address you can use a computer or any web connected device(on the same network) to test if the server is up and running.

The iPhone app will be available and will allow full control of the device.

The sketch has a preset temperature(when on Auto mode) which is 70 degrees. This can be changed to your preferred value.


The sketch uses the OneWire, DallasTemperature libraries, as well as the ones needed for ethernet control.

You can search for these libraries and download them as needed.

Feel free to change any part of this sketch to fit your own needs.

///Hardware

My build uses the one wire digital temperature sensor which can be found here https://www.sparkfun.com/products/245

You can find the spec sheet and how to implement it on this site as well.

The fan control uses a digital pin to with on or off a connected relay. ( I am not responsible for how you decide to implement the hardware, including how the relay gets its main power source, this can be dangerous if electrical safety standards are not followed)
Do not attempt this if you do not have experience with electrical safety. 
By using the source code, and my instructions, you are agreeing that I am not liable for any damages, or injuries, that this project may cause to you, others or your equipment.

------------------------------------------
You can contact the developer, David Paquette, with any questions or suggestions
at dpaquette01@aol.com

