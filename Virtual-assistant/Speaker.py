"""
Speaker class
"""
import pyttsx3

class Speaker:
    
    def __init__(self):
        self.engine = pyttsx3.init()
        
    def get_voice(self):
        return self.voice
    
    def set_voice(self, id):
        if id in [1, 2, 3]:
            voices = self.engine.getProperty('voices')
            if id == 1 :
                print(voices[0].id)
                self.engine.setProperty('voice',voices[0].id)
            elif id == 2 :
                self.engine.setProperty('voice',voices[1].id)
            elif id == 3 :
                self.engine.setProperty('voice',voices[2].id) 
            print("The voice has been changed")
        else:
            print("Process failed, id must be 1, 2 or 3")
    
    def speak(self, text):
        self.engine.say(text)
        self.engine.runAndWait()
        
        

