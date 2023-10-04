#include <DHT.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define diodPin 9                     // Blink diod for testing
#define DHTPIN 4                      // Temp/humid pin
#define DHTTYPE DHT22                 // Type of sensor
DHT dht(DHTPIN, DHTTYPE);             // Create dht object

void printTemp(void);                 // Gets temp and moist from thermometer and prints on App screen.
void vattnaBlomma(void);              // Waters the flower
void getBlomfukt(void);               // Gets the moisture from the flower pot
void lampOn(void);                    // Turn lamp on
void lampOff(void);                   // Turn lamp off
void testFunction(void);

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(115);
  SPI.begin();

}

void loop() {
  
  if (Serial.available()){
    int input = Serial.read();

    switch (input){
      case 0: printTemp(); break;

      case 1: vattnaBlomma(); break;

      case 2: getBlomfukt(); break;

      case 3: lampOn(); break;

      case 4: lampOff(); break;
    }
  }
  
  
}

void printTemp(){
  int temp = (dht.readTemperature() + 100);     // Send a big number so the App can differentiate temp from humid. >100 mean temp, <=100 means humid. App deducts 100.
  Serial.write(temp);

  int humid = dht.readHumidity();
  Serial.write(humid);

}

void vattnaBlomma(){
  testFunction();
  
}

void getBlomfukt(void){
  testFunction();
  testFunction();
}

void lampOn(void){
  int buf = 1;
  radio.write(&buf, sizeof(buf));
}

void lampOff(void){
  int buf = 2;
  radio.write(&buf, sizeof(buf));
}

void
 testFunction(void){
  digitalWrite(diodPin, 1);
  delay(500);
  digitalWrite(diodPin, 0);
  delay(500);
 }