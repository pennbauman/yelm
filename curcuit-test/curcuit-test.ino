int connectionPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(connectionPin, INPUT); 
   
  Serial.println("READY");
}

void loop() {
  int connectionState = analogRead(connectionPin);
  Serial.println(connectionState);
  /*if (connectionState > 10) {
    
  } //*/
  delay(500);
}
