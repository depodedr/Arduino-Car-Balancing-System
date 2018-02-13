#include <LedControl.h> // Library for Dot Matrix
#include <NewPing.h> // Library for Ultrasonic Sensor 
#include <SoftwareSerial.h> // Library for DC motor driver

#define TRIGGER_PIN1 8 // Front Ultrasonic Sensor
#define ECHO_PIN1 7  
#define MAX_DISTANCE1 400 

#define TRIGGER_PIN2 2 // Back Ultrasonic Sensor
#define ECHO_PIN2 4
#define MAX_DISTANCE2 400

int Reverse1 = 10; // Wheel 1
int Speed1 = 3;
int Forward1 = 11;

int Forward2 = 5; // Wheel 2
int Reverse2 = 6;
int Speed2 = 9;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // Activation of forward ultrasonic sensor 
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2); // Activation of backward ultrasonic sensor

LedControl lc = LedControl(13,14,12,1); // Activation of dot matrix
unsigned long delayTime = 200;

byte row1[] = // Dot matrix left most row is on
{
   B11111111,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte row2[] = // Dot matrix second left most row is on
{
   B00000000,  
   B11111111,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte row3[] = // Dot matrix third left most row is on
{
   B00000000,  
   B00000000,
   B11111111,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte rowMiddle[] = // Dot matrix middle 2 rows are on 
{
   B00000000,  
   B00000000,
   B00000000,
   B11111111,
   B11111111,
   B00000000,
   B00000000,
   B00000000
};

byte row6[] = // Dot matrix third right most row is on 
{
   B00000000,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B11111111,
   B00000000,
   B00000000
};

byte row7[] = // Dot matrix second right most row is on 
{
   B00000000,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B11111111,
   B00000000
};

byte row8[] = // Dot matrix right most row is on
{
   B00000000,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B11111111
};

void setup() {
  
pinMode(Speed1, OUTPUT); // Setting up pinmodes for motor 1
pinMode(Forward1, OUTPUT);
pinMode(Reverse1, OUTPUT);

pinMode(Speed2, OUTPUT); // Setting up pinmodes for motor 2
pinMode(Forward2, OUTPUT);
pinMode(Reverse2, OUTPUT);

Serial.begin(115200); // Channel to use on serial monitor

lc.shutdown(0,false);  // Wake up displays
lc.shutdown(1,false);
lc.setIntensity(0,5);  // Set intensity levels
lc.setIntensity(1,5);
lc.clearDisplay(0);  // Clear Displays
lc.clearDisplay(1);
}

void loop() {

delay(600);                     
Serial.print("Sensor1 (FRONT): "); // Prints ultrasonic sensor values in serial monitor
Serial.print(sonar1.ping_cm());
Serial.print("cm    ");

Serial.print("Sensor2 (REAR): ");
Serial.print(sonar2.ping_cm());
Serial.println("cm");

if (sonar1.ping_cm() > sonar2.ping_cm()){ // When sensor 1 is greater than sensor 2
analogWrite(Speed1, 250); // the motor will go forward
analogWrite(Speed2, 250);
digitalWrite(Reverse1, LOW);
digitalWrite(Reverse2, LOW);
digitalWrite(Forward1, HIGH);
digitalWrite(Forward2, HIGH);
}

else if (sonar2.ping_cm() > sonar1.ping_cm()){ // When sensor 2 is greater than sensor 1
analogWrite(Speed1, 250); // the motor will go backward
analogWrite(Speed2, 250);
digitalWrite(Forward1, LOW);
digitalWrite(Forward2, LOW);
digitalWrite(Reverse1, HIGH);
digitalWrite(Reverse2, HIGH);
}

while (sonar1.ping_cm() == sonar2.ping_cm()){ // When the sensors are equal, the motors will stop
analogWrite(Speed1, 0);
analogWrite(Speed2, 0);
digitalWrite(Reverse1, LOW);
digitalWrite(Reverse2, LOW);
digitalWrite(Forward1, LOW);
digitalWrite(Forward2, LOW);
delay(2000);
}

// These if statements turn on the varies rows of light on the dot matrix

if (sonar1.ping_cm()/sonar2.ping_cm() <= (1 / sonar2.ping_cm())) { 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row8[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() > (1 / sonar2.ping_cm()) && (sonar1.ping_cm()/sonar2.ping_cm() < (2 / sonar2.ping_cm()))){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row7[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() > (2 / sonar2.ping_cm()) && (sonar1.ping_cm()/sonar2.ping_cm() < (3 / sonar2.ping_cm()))){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row6[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() == 1){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,rowMiddle[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() > (2 / sonar1.ping_cm()) && (sonar1.ping_cm()/sonar2.ping_cm() < (3 / sonar1.ping_cm()))){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row3[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() > (1 / sonar1.ping_cm()) && (sonar1.ping_cm()/sonar2.ping_cm() < (1 / sonar1.ping_cm()))){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row2[i]);
    }
}

if (sonar1.ping_cm()/sonar2.ping_cm() <= (1 / sonar1.ping_cm())){ 
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,row1[i]);
    }
}

}
