#include <Adafruit_PN532.h>

// Set State
solvedState = false;

// Pins
const int plugsPin = 6;
const int buttonPin = 7;
const int piezoPin = 11;
const int LEDPin = 13;
// RFID Pins
Adafruit_PN532 nfc(2, 3);

//Animal RFID Mappings
std::map<int, std::string> animalsIDs;
animalsIDs[0] = std::string("1. ");
animalsIDs[1] = std::string("2. ");
animalsIDs[2] = std::string("3. ");
animalsIDs[3] = std::string("4. ");
animalsIDs[4] = std::string("5. ");
animalsIDs[5] = std::string("6. ");
animalsIDs[6] = std::string("7. ");
animalsIDs[7] = std::string("8. ");
animalsIDs[8] = std::string("9. ");

byte RFIDs[][] = {
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
  {0xA7, 0xE3, 0x2E, 0x70},
}
const int numAnimals = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("-- System Started");

  if(!SetupRFIDShield()) //sets up the RFID
  {
    Serial.print("Didn't find PN53x board");
    while(1) {}
  }

  pinMode(plugsPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
  pinMode(piezoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);

}

void loop() {
  if (solvedState) {
    if (checkButton()) handleButtonReset();
  } else {
    handleRFID();
    if (checkButton()) handleButtonCheck();
    //if (checkPlugs()) handlePlugs();
  }
}

bool checkButton(void) {
  bool fin = false;
  
  int currentButton = digitalRead(buttonPin);
  if(pastButton != currentButton) {
    delay(10); //this is a cheat for debouncing
    if(currentButton == LOW) fin = true;  //button is down => pin reads LOW
  }
  pastButton = currentButton;

  return fin;
}

void handleButtonCheck(void) {
  
}

void handleButtonReset(void) {
  solvedState = false;
  Serial.println("-- System Reset");
  tone(piezoPin, 400, 100);
}

void checkRFID(void) {
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40); // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found 'uid' will be populated with the UID, and uidLength will indicate if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  
  if (success) { 
    /*
    Serial.print("UID: ");
    for (int i = 0; i < uidLength; i++) {
      Serial.print(uid[0]);
      Serial.print(", ");
    }
    Serial.println("");
    //*/
    //Serial.println("Tag found!");
    if(uidLength == 4) {
      for (int i = 0; i < numAnimals; i++) {
        bool animalPresent = true;
        for (int hexI = 0; hexI < uidLength; hexI++) {
          if (RFIDs[i][hexI] != uid[hexI]) animalPresent = false;
        }
        if (animalsPresent) Serial.println(animalsIDs[i]);
      }
      /*
      Serial.print(uid[0],HEX);
      Serial.print(uid[1],HEX);
      Serial.print(uid[2],HEX);
      Serial.print(uid[3],HEX);//*/
      /*
      if(targetID[0] == uid[0] && targetID[1] == uid[1] && targetID[2] == uid[2] && targetID[3] == uid[3])
      {
        Serial.println("Match!");
        return true;
      } else {
        Serial.println("Wrong ID");
      }
    } //*/
  }
}
