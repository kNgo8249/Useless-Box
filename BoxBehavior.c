#include <Servo.h>
Servo myservo;  // create servo object to control a servo,,  


const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int Flash =  7;       // flashing LED 

// variables will change:
volatile int toggleSwitch = 0;         // variable for reading the pushbutton status

// twelve servo objects can be created on most boards

int pos = 6;    // variable to store the servo position

int randNum;
boolean derek = true;

void setup()
{
	Serial.begin(9600);
	
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  pinMode(Flash, OUTPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, CHANGE);
  // attaches the servo on pin 9 to the servo object 
   myservo.attach(9);  
	randomSeed(analogRead(0));
}

void loop()
{
	randNum = random(8);
	if (toggleSwitch == LOW){
		pos = 0;
		derek = true;
		myservo.write(pos);
	} 
	else if(derek){
		pos = 115;	
		
		Serial.println(randNum);
		switch(randNum) {
			// Behavior 1: immediate
			case 0:
			case 1:
			case 2:
			case 3:
			{
				myservo.write(pos);
				derek = false;
			}
			break;
			// Behavior 2: servo goes slow
			case 4:
			{
				for(int i = 0; i <= pos+5; i+= 10) {
					myservo.write(i);
					delay(200);
				}
				derek = false;
			}
			break;
			// Behavior 3: servo waits a bit
			case 5:
			{
				delay(2500);
				myservo.write(pos);
				derek = false;
			}
			break;
			// Behavior 4: servo tricks by not hitting it at first
			case 6:
			{
				myservo.write(pos - 40);
				delay(2500);
				myservo.write(pos);
				derek = false;
			}
			break;
			// Behavior 5: get rekt
			case 7:
			{
				delay(1500);
				myservo.write(pos - 50);
				delay(1000);
				myservo.write(0);
				delay(2500);
				myservo.write(pos);
				derek = false;
			}
			break;
		}
	
	}
}

void pin_ISR() {
  toggleSwitch = digitalRead(buttonPin);
  digitalWrite(ledPin, toggleSwitch);
} 
