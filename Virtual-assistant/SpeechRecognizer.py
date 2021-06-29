import speech_recognition as rv #Biblio de reconnaissance vocale, Utilise PyAudio et pipwin

class SpeechRecognizer:
    
    def __init__(self):
        self.recognizer = rv.Recognizer()
        
    def recognize(self):
        with rv.Microphone() as source:
            print("Speak...\n")
            self.recognizer.pause_threshold=1
            audio = self.recognizer.listen(source)#signal sonore
        try :
            print("Please wait...")
            txt=self.recognizer.recognize_google(audio,language="en-US")
            print("You said: ", txt)
        except Exception as e :
            print(e)
            print("I couldnt understand you...")
            return "None"
        return txt

