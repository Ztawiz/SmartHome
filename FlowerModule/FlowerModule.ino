#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define pumpPin 3         // pin som styr pumpen.
#define vattnaValue 3     // värdet som tas emot av radio och innebär att vi ska vattna.
#define fuktValue 4       // Värdet som tas emot av radio och innebär att vi ska mäta och skicka fuktvärde.

void vattna(void);
void fukt(void);

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  pinMode(pumpPin, OUTPUT);
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
    }
    if (buf == fuktValue){
      fukt();
    }
    
  }

}

void vattna(void){            // Vattnar blomman.
  digitalWrite(pumpPin, HIGH);
  delay(2000);
  digitalWrite(pumpPin, LOW);
}

void fukt(void){              // Denna ska mäta och skicka fuktvärdet.

}