#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define ledPin1 A0
#define ledPin2 A1
#define Buzz A2
Servo servo;
int pos = 0;
MFRC522 rc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rc522.PCD_Init();     //Initialize card reader
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  servo.attach(3);
  servo.write(0);
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

  //Do the verification
  if(strID.indexOf("35:7B:2C:D9") >=0){
    Serial.println("Access Granted");
    digitalWrite(A0, HIGH);
    tone(Buzz, 3000, 500);
    for (pos = 0; pos <= 60; pos += 1) { // goes from 0 degrees to 60 degrees
                                         // in steps of 1 degree
    servo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(10);                           // waits 10ms for the servo to reach the position
  }
  delay(1500);
  for (pos = 60; pos >= 0; pos -= 1) {   // goes from 60 degrees to 0 degrees
    servo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(10);                           // waits 10ms for the servo to reach the position
  }
    digitalWrite(A0, LOW);
    delay(500);
  }
  else{
    Serial.println("Access Denied");
    digitalWrite(A1, HIGH);
    tone(Buzz, 300, 200);
    delay(250);
    tone(Buzz, 300, 200);
    delay(250);
    tone(Buzz, 300, 200);
    digitalWrite(A1, LOW);
    delay(400);
  }
}
