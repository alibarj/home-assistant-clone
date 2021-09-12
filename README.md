# home-assistant-clone
Home assistant clone is a school project that aims to replicate few of the basic features of modern-day home assistants. It gives voice control over distant leds (on/off), distant gates (open/close), and reading home temperature, and it uses Python, Arduino, and a bunch of ESP8266 microchips to achieve that. For the time being, the program only works on computer but we'll try to migrate to a mobile app if we ever get the change to.
## Features
Upon executing the main python script, the vocal assistant asks for your inquiry which you can express vocally. The inquiries can be one of the following:
* Turn on or off the led.
* Open or close the gate.
* Get the curent room temperature.

The assistant then sends the corresponding command to the microchips connected to the different sensors and actuators, and the process keeps looping until you explicitely tell it to quit.
## Stack
### Python
The vocal assistant part is coded in Python, we've used various open source packages and wired them together to get the desired result. Thes packages are:
* [pyttsx3](https://github.com/nateshmbhat/pyttsx3), a text-to-speech conversion library that works offline
* [SpeechRecognition](https://github.com/Uberi/speech_recognition#readme), a library for performing speech recognition, with support for several engines and APIs, online and offline.
* [paho-mqtt](https://github.com/eclipse/paho.mqtt.python) that provides a client class which enable applications to connect to an MQTT broker to publish messages, and to subscribe to topics and receive published messages (more on MQTT later).
### Arduino
The esp8266 microcontrollers are programed using the standard API known as the Arduino language. The programs in these microcontrollers are responsible of establishing the connection with the MQTT broker, publish and subscribe to MQTT topics, and control their respective sensors and actuators based on the messages in these topics.
### MQTT
MQTT is a lightweight network protocol that wirelessly transports messages between devices. The MQTT protocol defines two types of entities, a broker and clients.
The MQTT broker is a server (we used our local machine) that receives all messages from the clients and then routes the messages to the appropriate destination clients. An MQTT client is any device, from a micro controller up to a fully-fledged server (LEDs, tempretature sensor, and a small actuator in our case), that runs an MQTT library and connects to an MQTT broker over a network.
