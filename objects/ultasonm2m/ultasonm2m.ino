#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "Zikas";
const char* password = "hh123456";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.129.93";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);

// Lamp - LED - GPIO 4 = D2 on ESP-12E NodeMCU board
long duree, distance;


// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }


  // Feel free to add more if statements to control more GPIOs with MQTT


}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", "ali", "ali")) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("room/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  pinMode(D5, OUTPUT);                     // Initialise la broche "trigger" (déclencheur) du capteur ultrason qui est connecté au pin 4
  pinMode(D6, INPUT);                      // Initialise la broche "echo" du capteur ultrason qui est connecté au pin 2
  Serial.begin(9600);
  setup_wifi();
  pinMode(4, OUTPUT);// out put car on l envoie des messages (declancher la mesure)// initialise la broche "trigger" declencheur de capteur utason qui est connecte au pin 4
  pinMode(2, INPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop()) {
    client.connect("ESP8266Client");
  }

  digitalWrite(D5, LOW);                   ///////////////////////////////////////////////////////////////////////////////////////////////
  delayMicroseconds(2);                   //
  digitalWrite(D5, HIGH);                  // Envoi d'un signal carré  sur le pin 2 (déclencheur) afin de déclencher une mesure de sitance
  delayMicroseconds(2);                   //
  digitalWrite(D5, LOW);                   ///////////////////////////////////////////////////////////////////////////////////////////////

  duree = pulseIn(D6, HIGH);               // Lecture du temps écoulé avant que le pin 2 reçoive un signal
  distance = duree * 340 / (2 * 10000);
  // Transforme le temps en distance (cm) 340=Vitesse du son en m/s  duree = temps mis pour l'aller retour en microsecondes
  Serial.print("La distance est : ");     // affiche le message entre guillemets sur le moniteur série
  Serial.print(distance);                 // affiche la valeur de la variable distance sur le moniteur série
  Serial.println(" cm");                  // affiche le message entre guillemets sur le moniteur série
  delay(1000);
  char msg;
  if (distance < 10) {
    client.publish("room/distance", "1");
  }
  else {
    client.publish("room/distance", "0");
  }
}
