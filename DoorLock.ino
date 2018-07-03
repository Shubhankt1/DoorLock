#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define ledPin A0
MFRC522 rc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //Initialize serial comm. with the PC
  SPI.begin();          //Initialize SPI bus
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  rc522.PCD_Init();     //Initialize card reader
  Serial.println("Scan to Enter");
}

void loop() {
  digitalWrite(ledPin, LOW);
  // put your main code here, to run repeatedly:
  //check for new card
  if(!rc522.PICC_IsNewCardPresent()) {
      return;     //Goto start of loop
  }
  //Read one of the cards
  if(!rc522.PICC_ReadCardSerial()){
    return;       //If ReadCardSerial returns 1, the 'uid' struct contains the ID of the read card
  }

  //Dump debug info about the card.
  digitalWrite(ledPin, HIGH);
  rc522.PICC_DumpToSerial(&(rc522.uid));
}
