#include <DHT.h>

#define DHTPIN 4                      // Temp/humid pin
#define DHTTYPE DHT22                 // Type of sensor
DHT dht(DHTPIN, DHTTYPE);             // Create dht object

void printTemp(void);                 // Gets temp and moist from thermometer and prints on App screen.
void vattnaBlomma(void);              // Waters the flower
void getBlomfukt(void);               // Gets the moisture from the flower pot
void lampOn(void);                    // Turn lamp on
void lampOff(void);                   // Turn lamp off

void setup() {
  
  Serial.begin(9600);
  dht.begin();

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

}

void getBlomfukt(void){

}

void lampOn(void){

}

void lampOff(void){

}