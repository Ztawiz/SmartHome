#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

#define pumpPin 3         // pin som styr pumpen.
#define vattnaValue 1     // värdet som tas emot av radio och innebär att vi ska vattna.
#define fuktValue 2       // Värdet som tas emot av radio och innebär att vi ska mäta och skicka fuktvärde.
#define servoPin 5

void vattna(void);
void fukt(void);

RF24 radio(7, 8);
Servo myServo;


const byte address[6] = "00001";

void setup() {
  pinMode(pumpPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  SPI.begin();
}

void loop() {
  if (Serial.available()){
    int buf = Serial.read();
    if (buf == vattnaValue){
      vattna();
      Serial.println("Vi fick en etta!");
    }
    if (buf == fuktValue){
      fukt();
    }
  }
}

void vattna(void){            // Vattnar blomman.
  Serial.println("i vattna");
  myServo.write(35);
  delay(500);
  digitalWrite(pumpPin, HIGH);
  delay(2000);
  digitalWrite(pumpPin, LOW);
  delay(1000);
  myServo.write(90);
  delay(500);
  digitalWrite(pumpPin, HIGH);
  delay(2000);
  digitalWrite(pumpPin, LOW);
  delay(1000); 
}

void fukt(void){              // Denna ska mäta och skicka fuktvärdet.

}
