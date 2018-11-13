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

userNameForUserID[0] = std::string("1. ");
userNameForUserID[1] = std::string("2. ");
userNameForUserID[2] = std::string("3. ");
userNameForUserID[3] = std::string("4. ");
userNameForUserID[4] = std::string("5. ");
userNameForUserID[5] = std::string("6. ");
userNameForUserID[6] = std::string("7. ");
userNameForUserID[7] = std::string("8. ");
userNameForUserID[8] = std::string("9. ");

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


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
