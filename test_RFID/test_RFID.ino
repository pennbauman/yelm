#include <Adafruit_PN532.h>

//Defines the pins for the RFID reader. Note that pins 2 & 3 are used by the shield and cannot be used for anything else.
Adafruit_PN532 nfc(2, 3);

//This will be the ID of the tag you will use to deactivate your system
//YOU'LL HAVE TO EDIT THESE FOR YOUR SPECIFIC TAG!!
byte targetID[] = {0x7B, 0x46, 0x20, 0x2D};

void setup() {
  Serial.begin(9600);
  
  if(!SetupRFIDShield()) //sets up the RFID
  {
    Serial.print("Didn't find PN53x board");
    while(1) {}
  }

  Serial.println("Started");
}

void loop() {
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40);
  if (success) {
    Serial.println("UID: ");
    Serial.print(uid[0],HEX);
    Serial.print(uid[1],HEX);
    Serial.print(uid[2],HEX);
    Serial.print(uid[3],HEX);
    Serial.println("");
  }

  delay(400);
}
