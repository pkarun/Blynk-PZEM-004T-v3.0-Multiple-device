# Blynk-PZEM-004T-v3.0-Multiple-device
Blynk ESP8266 (NodeMCU) Program to connect multiple PZEM 004T v3.0 Power Meter. 
<h2> Requirements </h2>
1) <a href="http://s.click.aliexpress.com/e/ElytDjIu" rel="nofollow">PZEM-004T v3.0 </a><br>
2) <a href="http://s.click.aliexpress.com/e/nlefJ4PI" rel="nofollow">NodeMCU </a><br>
3) <a href="https://play.google.com/store/apps/details?id=cc.blynk" rel="nofollow">Blynk App </a><br>
<h2> Installation </h2>
Open settings.h and change Bynk Auth code, Wifi settings, server settings and few other parameters as per your project requirement.


<h2> Hardware Connection </h2>

PZEM-004T v3.0 to NodeMCU

PZEM Device 1:

   5v to vin<br>
   RX to D6 (TX Pin)<br>
   TX to D5 (RX Pin)<br>
   GND to GND<br>

PZEM Device 2:

   5v to vin<br>
   RX to D6 (TX Pin)<br>
   TX to D5 (RX Pin)<br>
   GND to GND<br>

   For wiring image: https://didactronica.com/wp-content/uploads/2019/03/ASDADSASD.png

<h2> Software Setup </h2>

1) Download and install the Blynk Mobile App for iOS or Android.

2) Scan the QR code at the bottom of this page to clone the screenshot below, or create a new project yourself and manually arrange and setup the widgets.

3) Email yourself the Auth code.

4) Download this repo and copy the files in to your sketches directory. Open the sketch in Arduino IDE.

5) Go to the settings.h tab. This is where all the customisable settings are. You should be able to change almost everything from there before compiling.

<b>Note:</b>

For multiple PZEM 004T v3.0 device, first we need to assign address to each device or else this program won't work. Make sure you assign address to each PZEM device one by one by connection only one PZEM device to network/Nodemcu and upload our program and uncomment below line in the program.

<pre>changeAddress(0x01, 0x02);</pre>

This task need to be done once only. Once address assignment is done, comment it again and upload the program to NodeMCU and connect all the new address assigned PZEM devices to network(nodemcu) and now you will start receving data from multipe pzem devices. 

<h2> Screenshot </h2>

<img src="/images/project-screenshot-1.png" alt="project screenshot 1" title="project screenshot 1" width="350" height="">
<h2> Scan QR Code on Blynk App </h2>

<img src="/images/blynk-scan-qr-code.png" alt="Blynk Project QR code" title="Blynk Project QR code">
