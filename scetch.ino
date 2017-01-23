#include <SPI.h>
#include <Ethernet.h>
#include <Ultrasonic.h>
#define CM 1

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
char server[] = "www.kanifol-group.ru";

void connection();
int distance();

int trigPin = 5; 
int echoPin = 6;

IPAddress ip(192,168,0,102);
EthernetClient client;

Ultrasonic ultrasonic(trigPin, echoPin);

void setup() {

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);


   
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }

  // start connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a time to initialize:
  delay(500);
  
}

void loop() {
  while(true){
    if (distance()){
      connection();
      delay(3500);
    }
    else {
      delay(250);
    }
  }
};


void connection(){
  if (client.connect(server, 5000)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /?say=somebody_entered HTTP/1.1");
    client.println("Host: www.kanifol-group.ru");
    client.println("Connection: close");
    client.println();
    client.stop();
  } else {
    Serial.println("connection failed");
  }
}



int distance(){
  int enteredstate = 0;
  int mindist = 20;
  float dist_cm = ultrasonic.Ranging(CM);  // get distance
  Serial.println(dist_cm);
  if (dist_cm<mindist){
    enteredstate = 1;
  }
  return(enteredstate);
}

