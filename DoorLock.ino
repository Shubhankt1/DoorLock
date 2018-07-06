#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define ledPin1 A0
#define ledPin2 A1
#define Buzz A2
const int Rows = 4;
const int Cols = 4;
char keymap[Rows][Cols] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rPins[Rows] = {8,7,6,5};
byte cPins[Cols] = {4,3,2,A3};
String pw = "123A";
String keypressed = "";
Keypad kpd = Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);
//MFRC522 rc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  //rc522.PCD_Init();     //Initialize card reader
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.println("Enter the CODE:");
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = kpd.getKey();
  if(key!=NO_KEY){
  Serial.print(key);
  keypressed.concat(key);
  if(keypressed == pw){
    digitalWrite(A0, HIGH);
    tone(Buzz, 1000,500);
    Serial.println("\nWelcome Shubhank");
    delay(500);
    digitalWrite(A0, LOW);
    keypressed = "";
    }
  else{
    digitalWrite(A1, HIGH);
    tone(Buzz, 300, 200);
    Serial.println("\nWRONG!");
    delay(250);
    tone(Buzz, 300, 200);
    delay(250);
    tone(Buzz, 300, 200);
    digitalWrite(A1, LOW);
    }
  }
}
