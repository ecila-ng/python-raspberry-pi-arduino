# Folder map 🌳

##### Button.ino:
Make the LED blink faster, get LEDs to blink alternately 

##### TMP36_Button.ino:
Use the TMP36 component to: 
- Get temperature based on TMP36 read
- Print result on serial console 
- With flat side of TMP36 facing you, left pin should receive voltage, right pin should be grounded, middle pin sends data

##### WiFi_connect.ino:
Have NodeMCU connect to wireless router. After connecting, prints out the NodeMCU’s IP address 

##### WiFi_dweet.ino:
Decide if the node MCU will be a:
- Client - which sends requests to servers and processes response(s)
- Server - which waits for clients to send it data (and responds accordingly)

Have NodeMCU connect to wireless router. After connecting, prints out the NodeMCU’s IP address 
Then connects to dweet.io and reads latest dweet then shows dweet on Serial Monitor.

##### WiFi_webserver.ino:
Have NodeMCU connect to wireless router. After connecting, prints out the NodeMCU’s IP address 
Waits for web browser to send NodeMCU a GET command then shows command on Serial Monitor.

##### WiFi_webserver_button.ino:
Wire an external LED on breadboard to NodeMCU with a brown banded resistor
Have NodeMCU connect to wireless router. After connecting, prints out the NodeMCU’s IP address 
Waits for web browser to send NodeMCU a GET command then shows command on Serial Monitor. 
The command is the sequence that comes after the “GET”
- If the command is “/on”, then turn on the external LED 
- If the command is “/off”, then turn off the external LED 

##### servo.ino:

##### LDR_Analog.ino:	

##### LDR_Digital.ino:
