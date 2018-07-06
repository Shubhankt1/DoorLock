#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define ledPin1 A0
#define ledPin2 A1
#define Buzz A2
MFRC522 rc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rc522.PCD_Init();     //Initialize card reader
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.println("Scan the Card:");
}

void loop() {
  // put your main code here, to run repeatedly:

  //check if any card is present and also scan only one card if multiple are present
  if(!rc522.PICC_IsNewCardPresent() || !rc522.PICC_ReadCardSerial())  return;

  //check if the type of the card is what we need and not any other card.
  MFRC522::PICC_Type type = rc522.PICC_GetType(rc522.uid.sak);
  if(type!= MFRC522::PICC_TYPE_MIFARE_MINI &&
     type!= MFRC522::PICC_TYPE_MIFARE_1K &&
     type!= MFRC522::PICC_TYPE_MIFARE_4K) return;
  String strID = "";
  for(byte i=0; i<4; i++) strID += (rc522.uid.uidByte[i] < 0x10 ? "0" : "") + String(rc522.uid.uidByte[i], HEX) + (i != 3 ? ":" : "");

  //put ID in capitals
  strID.toUpperCase();
  Serial.print("Card: ");
  Serial.println(strID);
  delay(1000);

  //Do the verification
}
