#include <Adafruit_NeoPixel.h>

// We have used this code library for the implementation of LEDs
 
int ledPin= 3;
int ledNo= 12;

// We have joined the following pins of the LED to the Arduino

Adafruit_NeoPixel strip= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);

// Code connecting the Arduino to the LEDs

int buzzerPin= 2;
int echoPin= 6;
int trigPin= 5;

// We have joined the following pins of the Arduino to the Ultrasonic Sensor

int minDistance = 100;
int maxDistance = 300;

// Here, the distance that the ultrasonic sensor needs to scan has been programmed
// We can edit the distance that the sensor would sense as per the situation

void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial. begin(9600);  
  strip.begin();
  for(int i = 0; i < ledNo; i++)
  {
   strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

// This is the initialisation of the program which is used for setting the appropriate colour to the LEDs according to the distance.
// This code will help the LEDs take the required distance data from the ultrasonic sensor and translate it to its resepctive indicating colour

void loop() 
{
  int distance = calcDistance();
  Serial.println(distance);
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  Serial.println(ledsToGlow);
  if(ledsToGlow == 12)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }

// Here, the code of the buzzer has been programmed
// It will help the buzzer to activate by taking the required distance data from the LED

  for(int i = 0; i < ledsToGlow; i++)
  {
    if(i < 4)
    {
      strip.setPixelColor(i,strip.Color(50,0,0));//red,green,blue
    }
    else if(i >= 4 && i < 8)
    {
      strip.setPixelColor(i,strip.Color(50,50,0));//red,green,blue
    }
    else if(i >= 8 && i < 12)
    {
      strip.setPixelColor(i,strip.Color(0,50,0));//red,green,blue
    }
  }
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(50);
}

// This is the code for showing the respective grren, yellow and red colour according to the distance that the vehicle has moved.
// setPixelColor is from the NeoPixel code librabry and it helps to implement the colours

int calcDistance()
{
  long distance,duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;
  if(distance >= maxDistance)
  {
    distance = maxDistance;
  }
  if(distance <= minDistance)
  {
    distance = minDistance;
  }
  return distance;
}

// And finally, this is the code for Arduino
// As mentioned, the Arduino is the brain of this circuit
// This code indicates all the calculations it will peform such as calculating the minimum and maximum distance, sending out a pings to trigger the LEDs and the buzzer to operate when needed