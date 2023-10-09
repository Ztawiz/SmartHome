#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>
#include "Adafruit_seesaw.h"

#define pumpPin 3         // pin som styr pumpen.
#define vattnaValue 1     // värdet som tas emot av radio och innebär att vi ska vattna.
#define fuktValue 5       // Värdet som tas emot av radio och innebär att vi ska mäta och skicka fuktvärde.
#define servoPin 5

void vattna(void);
void fukt(void);

RF24 radio(7, 8);
Servo myServo;
Adafruit_seesaw ss;


const byte address[6] = "00001";

void setup() {
  pinMode(pumpPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
  ss.begin(0x36);
  ss.UARTSetBaud(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  //SPI.begin();
}

void loop() {
  if (radio.available()){
    int input = 0;
    radio.read(&input, sizeof(input));
    Serial.print("value: "); Serial.println(input);
    if (input == vattnaValue){
      vattna();
      Serial.println("Vi ska vattna!");
    }
    if (input == fuktValue){
      Serial.println("vi ska mata fukt!");
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
  uint16_t capread = ss.touchRead(0);
  uint16_t percent = (capread - 320);
  percent = map(percent, 0, 665, 0, 100);

  Serial.print("Capacitive: "); Serial.println(capread);
  Serial.print("Moisture: "); Serial.print(percent); Serial.println("%");      // sensorns pins är jord, Vin, SDA(A4), SCL(A5).

  radio.openWritingPipe(address);
  radio.stopListening();
  radio.write(&percent, sizeof(percent));

  radio.openReadingPipe(0, address);
  radio.startListening();
}
