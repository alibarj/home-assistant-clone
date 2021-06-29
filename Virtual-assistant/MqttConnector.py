import paho.mqtt.client as mqtt
import time


def on_message(client,userdata, msg):
    print(msg.topic +": "+msg.payload.decode())
    client.disconnect()


        
 


class MqttConnector:

    def __init__(self, name, host, username, pswd, on_message):
        
        # self.name = name
        # self.host = host
        # self.value = None
        # self.username = username
        # self.pswd = pswd
        self.connection = mqtt.Client(name)
        self.connection.username_pw_set(username=username, password=pswd)
        self.connection.on_message=on_message
        self.connection.connect(host)
        
        
    
    
    # def get_host(self):
    #     return self.host
    
    # def set_host(self, host):
    #     self.host = host
        
    # def get_name(self):
    #     return self.name
    
    # def set_name(self, topic):
    #     self.topic = name
        
    # def get_value(self):
    #     return self.value
    
    # def set_value(self, value):
    #     self.value = value
        
    # def get_username(self):
    #     return self.username
    
    # def set_username(self, username):
    #     self.username = username
        
    # def get_pswd(self):
    #     return self.pswd
    
    # def set_pswd(self, pswd):
    #     self.pswd = pswd
        
    
    def publish(self, topic, value):
        self.connection.publish(topic, value)
        
    def subscribe(self, topic):
        self.connection.subscribe(topic)
        self.connection.loop_forever()
        self.connection.disconnect()
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        