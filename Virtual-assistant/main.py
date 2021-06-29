import subprocess
#import os
from Speaker import Speaker
from SpeechRecognizer import SpeechRecognizer
from MqttConnector import MqttConnector

payload = None
flag_connected = 0

def mqtt_connector_on_message(client,userdata, msg):
    print(msg.topic +": "+msg.payload.decode())
    global payload
    global flag_connected
    payload = msg.payload.decode()
    client.disconnect()
    flag_connected = 0



mqtt_client = MqttConnector('python_mqtt', 'localhost', 'ali', 'ali', mqtt_connector_on_message)
flag_connected = 1

speaker = Speaker()
speaker.set_voice(2)
speaker.speak("Hello master, how can I serve you today")

sr = SpeechRecognizer()


while True:
    cmd = sr.recognize()
    if flag_connected == 0:
        mqtt_client = MqttConnector('python_mqtt', 'localhost', 'ali', 'ali', mqtt_connector_on_message)
        flag_connected = 1
        
    if 'light' in cmd : 
    
        if 'on' in cmd :
            
            mqtt_client.publish("room/distance", 1)
            print("on")
        
        elif 'off' in cmd :
            
            mqtt_client.publish("room/distance", 0)
            print("off")
        
    elif 'gate' in cmd :
        if 'open' in cmd :
            
            mqtt_client.publish("house/gate", 1)
            print("open")
            
        elif 'close' in cmd :
            
            mqtt_client.publish("house/gate", 0)
            print("close")
            
    elif 'temperature' in cmd:
        mqtt_client.subscribe('room/temperature')
        speaker.speak("The room temperature is "+str(payload))
        
    
    elif cmd == 'quit':
        speaker.speak("See you later honey")
    
        break
    speaker.speak("Can I do anything else for you")
    
    
     
