#include <Basecamp.hpp>

Basecamp iot;
static const int LedPin1 = 4; //pin 7
static const int LedPin2 = 16; //pin 8
static const int LedPin3 = 17; //pin 9
static const int Led = 2; //onboard led

void setup() {
  // put your setup code here, to run once:
  pinMode (LedPin1, OUTPUT);
  pinMode (LedPin2, OUTPUT);
  pinMode (LedPin3, OUTPUT);
  pinMode (Led, OUTPUT);
  digitalWrite(Led, LOW);
  iot.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iot.mqtt.onConnect(onMqttConnect);
  iot.mqtt.onMessage(onMqttMessage);
}

//This function is called when the MQTT-Server is connected
void onMqttConnect(bool sessionPresent) {
  //Subscribe to the delay topic
  iot.mqtt.subscribe("testtopic/receive", 0);
  //Trigger the transmission of the current state.
  //transmitStatus();
  Serial.println("Connected to mqtt server.");
  digitalWrite(Led, HIGH);
}

//This topic is called if an MQTT message is received
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  //Check if the payload eqals "true" and set delaySleep correspondigly
  //Since we only subscribed to one topic, we only have to compare the payload
  /*if (strcmp(payload, "true") == 0)  {
    delaySleep = true;
    } else  {
    delaySleep = false;
    }*/
  for (int i = 0; i < len; i++) {
    Serial.print((char)payload[i]);
  }

  digitalWrite(LedPin1, LOW);
  digitalWrite(LedPin2, LOW);
  digitalWrite(LedPin3, LOW);

  switch ((char)payload[0]) {
    case '1':
      digitalWrite(LedPin1, HIGH);
      break;
    case '2':
      digitalWrite(LedPin2, HIGH);
      break;
    case '3':
      digitalWrite(LedPin3, HIGH);
      break;
  }

  /*if ((char)payload[0] == '1') {
    Serial.println("ON");
    digitalWrite(LedPin, HIGH);
    } else {
     we got '0' -> on
    Serial.println("OFF");
    digitalWrite(LedPin, LOW);
    }*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
