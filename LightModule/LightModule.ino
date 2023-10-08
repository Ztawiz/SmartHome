#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  pinMode(4, OUTPUT);

}

void loop() {
  if (radio.available()) {
    int input = 0;
    radio.read(&input, sizeof(input));
    if (input == 3){
      digitalWrite(4, HIGH);
    }
    if (input == 4){
      digitalWrite(4, LOW);
    }
  }
}
