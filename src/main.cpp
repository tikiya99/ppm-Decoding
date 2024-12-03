#include <PPMReader.h>
#include <definitions.h>

byte interruptPin = 3; //PPM input 
byte channelAmount = 6; //Number of expected channels
PPMReader ppm(interruptPin, channelAmount);

unsigned long c1 =0;
unsigned long c2 =0;
unsigned long c3 =0;
unsigned long c4 =0;
unsigned long C1 =0;
unsigned long C2 =0;
unsigned long C3 =0;
unsigned long C4 =0;


void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void pulsecheck(){

    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);
        //Serial.print(value);
        if(channel < channelAmount) Serial.print('\t');
        if(channel ==1) c1 = value;
        if(channel ==2) c2 = value;
        if(channel ==3) c3 = value;
        if(channel ==4) c4 = value;
    } 
}

void motorsignal(){
    PPMMapping();
    if(C1>= 175){
      Serial.println("C1 Active");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        delay(20);
    }
    else if(C1<=125){
      Serial.println("C1 Down");
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        delay(20);
    }
}

void PPMMapping(){

    pulsecheck();

    C1 = map(c1, 1000, 2000, 0, 255);
    C2 = map(c2, 1000, 2000, 0, 255);
    C3 = map(c3, 1000, 2000, 0, 255);
    C4 = map(c4, 1000, 2000, 0, 255);
}

void loop() {

    motorsignal();

    delay(20);
}