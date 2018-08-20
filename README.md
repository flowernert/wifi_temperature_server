# Wifi temperature server for NodeMCU / ESP8266
Server part of a server/client temperature sensing system based on the ESP8266 NodeMCU with a DHT11 temperature sensor.

## Customization
Change the delayMS value to the interval you want the server to wake up and serve requests
Change the sensor ID definitions to match your sensing network needs.

## Flashing
I use the Arduino IDE to flash this code on my Wemos/LoLin NodeMCU D1 mini Pro.

## Usage
After flashing, open the serial console to lookup for the ip address of the server (for this example 192.168.0.35).
On your computer, in your internet browser go to http://192.168.0.35. You'll e able to see the temperatures sent by the remote sensors.

## Security
This is a simple prototype, no security is implemented between the sensor and the server. 
It means that any device connected to your local network can send fake temperature data to your server.
So you maybe should not use this sensor to monitor the temperature of you nuclear power plant ;)

## Client/sensor part of the project
https://github.com/flowernert/wifi_temperature_sensor

## License
Creative Commons BY-NC-SA
This software is provided "as is" and its user should assume no liability of its author on any consequence resulting of its usage.
