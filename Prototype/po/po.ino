#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_PIN 4
int RECV_PIN = 2;
int ledPin = 12;
const int buttonPin = 32;
int buttonState = 0;

IRsend irsend(IR_PIN);  // Set the GPIO to be used to sending the message.
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  irsend.begin();
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    digitalWrite(ledPin, HIGH);
  }
  delay(100);
  digitalWrite(ledPin, LOW);
  if (buttonState == LOW) {
          irsend.sendNEC(0xFFA857, 32);
  delay(1000);
    }
}
