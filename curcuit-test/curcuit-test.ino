const int connectionPin = A0;
const int ledPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(connectionPin, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT); 
   
  Serial.println("READY");
}

void setLED(bool state) {
  if (state) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  int connectionState = analogRead(connectionPin);
  Serial.println(connectionState);
  bool connected (connectionState > 400);
  setLED(connected);
  
  delay(500);
}


/* LAYOUT
 * Transistor Emitter -> 330ohm resistor -> ground
 *                    -> Checking wire (A0)
 * Transistor Base -> 330ohm resistor -> end of checked curcuit
 * Transistor Collector -> 5V+
 */
