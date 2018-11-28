#include <Adafruit_PN532.h>

// Set State
bool solvedState = false;

// Pins
const int plugsPins[] = {A0, A1, A2};
const int LEDPin = 13;
// RFID Pins
Adafruit_PN532 nfc(2, 3);

//Animal RFID Mappings
const String animalIDs[] = {
  "1. Mon-o'-War",
  "2. Sea Turtle",
  "3. Phytoplankton",
  "4. Brain Coral",
  "5. Copepod",
  "6. Hatchet Fish",
  "7. Coelacanth",
  "8. Brittle Star",
  "9. Blobfish"
};

byte RFIDs[][4] = {
  {0x83, 0x76, 0x4E, 0x9F},
  {0xE3, 0x78, 0x50, 0x9F},
  {0xB3, 0x3A, 0x4D, 0x9F},
  {0xB3, 0xEC, 0x4C, 0x9F},
  
  {0x13, 0x3B, 0x4E, 0x9F},
  {0x63, 0xAA, 0x4E, 0x9F},
  {0x63, 0x58, 0x4C, 0x9F},
  
  {0x83, 0xE4, 0x51, 0x9F},
  {0x63, 0xB5, 0x4E, 0x9F},
};
const int numAnimals = 9;

void setup() {
  nfc.begin();
  Serial.begin(9600);
  delay(400);
  Serial.println("-- System Started");
  
  /*
  if(!SetupRFIDShield()) //sets up the RFID
  {
    Serial.print("Didn't find PN53x board");
    while(1) {}
  } //*/
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  pinMode(plugsPins[0], INPUT);
  pinMode(plugsPins[1], INPUT);
  pinMode(plugsPins[2], INPUT);
  pinMode(LEDPin, OUTPUT);

  nfc.SAMConfig();
}

void loop() {
  checkRFID();
  if (checkPlugs()) {
    setLED(true);
  } else {
    setLED(false);
  }
  delay(100);
}

bool checkPlugs() {
  int level = 0;
  bool fin = true;
  Serial.print("[");
  for (int i = 1; i < 3; i++) {
    int connectionState = analogRead(plugsPins[i]);
    //Serial.print(connectionState);
    if (connectionState <= level) {
      fin = false;
      Serial.print("0");
    } else {
      Serial.print("1");
    } //*/
  } //*/
  Serial.println("]");
  return fin;
}

void setLED(bool state) {
  if (state) {
    digitalWrite(LEDPin, HIGH);
  } else {
    digitalWrite(LEDPin, LOW);
  }
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
        if (animalPresent) Serial.println(animalIDs[i]);
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
      }//*/
    } 
  }
};
