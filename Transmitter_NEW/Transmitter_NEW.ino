#include <RCSwitch.h>
#include <Adafruit_NeoPixel.h>
int sensorPin = A0;
int sensorValue = 0;
RCSwitch mySwitch = RCSwitch();

int button_pins[] = {3, 4, 10, 6, 7}; // Button pins

#define pinw 12

  //////////////////////////////////////--------MILLIS Delay for AutoFire -----------\\\\\\\\\\\\\\\\\\\\\\\\\\

#define MOTOR_PIN 9 
unsigned long previousMillis = 0;  // Stores the last time the motor was updated
const long motorOnDuration = 500;  // Duration to keep the motor ON (in milliseconds)

 
  //////////////////////////////////////--------MILLIS Delay for AutoFire -----------\\\\\\\\\\\\\\\\\\\\\\\\\\


 unsigned long prevmillis1=0;
 unsigned long interval1=200;
  unsigned long prevmillis2=0;                                //1
 unsigned long interval2=30;
 // Use static to retain its value across function calls
 
 unsigned long interval1a=80;
                                                                //2
 unsigned long interval2a=30;
  
 int firecount=0;
 int vibration=0;
 /////////////////////////////////////////////////////////////////////////////////////////////////
  int count_LEDs=0;
  int count_Menu=0;
  int count_Vibration=0;
  int count_Autofire=0;
  int nullifing=0;   
    //////////////////////////////////////--------MILLIS Delay for LED STRIP -----------\\\\\\\\\\\\\\\\\\\\\\\\\

#define LED_PIN     5  
#define NUM_LEDS    9     

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentMode = 0;                  // Start with the first mode
unsigned long lastButtonPress = 0;    // Last time the button was pressed
const unsigned long debounceDelay = 200; // Debounce time for button press
int buttonPressCount = 0;             // Counter for the number of button presses
int button8PressCount =0;
// Timing variables for non-blocking effects
unsigned long previousMillisa = 0;
unsigned long effectWait = 50;        // Default delay for effects

void setup() {
  Serial.begin(9600);
  pinMode(pinw, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);  // Initially, keep motor off
   strip.begin();
    strip.show(); 
  digitalWrite(pinw, HIGH); // Indicate transmission with LED
  delay(100);
  digitalWrite(pinw, LOW);
  for (int i = 0; i < 5; i++) {pinMode(button_pins[i], INPUT);}
  mySwitch.enableTransmit(2);  // Transmitter is connected to Pin 2
}

void loop() {

   sensorValue = analogRead(sensorPin);
    // Serial.print("Analog value: ");
    // Serial.println(sensorValue);
  
  
  for (int i = 0; i < 5; i++) {
    if (digitalRead(button_pins[i]) == LOW) {
      int commandToSend = i + 1;  // Map buttons to numbers 1-5
      Serial.println(commandToSend);
      nullifing=1;
      // Send using 3 bits instead of 8 bits
      mySwitch.send(commandToSend, 3); // Send command using 3 bits
      if (button8PressCount == 1 && i==0){for(int a=0; a<strip.numPixels(); a++) {strip.setPixelColor(a,255,255,255);strip.show();delay(5);}}
      if (button8PressCount == 1 && i==1){for(int b=0; b<strip.numPixels(); b++) {strip.setPixelColor(b,0,255,0);strip.show();delay(5);}}
      if (button8PressCount == 1 && i==2){for(int c=0; c<strip.numPixels(); c++) {strip.setPixelColor(c,0,0,255);strip.show();delay(5);}}
      if (button8PressCount == 1 && i==3){for(int d=0; d<strip.numPixels(); d++) {strip.setPixelColor(d,255,0,255);strip.show();delay(5);}}
      if (button8PressCount == 1 && i==4){for(int e=0; e<strip.numPixels(); e++) {strip.setPixelColor(e,255,0,0);;strip.show();delay(5);}}
      // Indicate transmission with LED
      digitalWrite(pinw, HIGH);
      delay(10);
      digitalWrite(pinw, LOW);
    }
  }

  if (digitalRead(button_pins[0])==HIGH && digitalRead(button_pins[1])==HIGH && digitalRead(button_pins[2])==HIGH && digitalRead(button_pins[3])==HIGH && digitalRead(button_pins[4])==HIGH && nullifing==1)
  {int abc=9;
    mySwitch.send(abc, 4); // Send command using 3 bits
    Serial.println("No direction button");
    strip.clear();strip.show();
    nullifing=0;}

if (sensorValue>1020){
count_Autofire=0;
count_Vibration=0;
count_Menu=0;
count_LEDs=0;}

if (sensorValue<1020){
    if (sensorValue<10){count_Autofire++;if (count_Autofire==1){
         
         int commandToSend = 6 ;
         mySwitch.send(commandToSend, 3); // Send command using 3 bits
         Serial.println(commandToSend);
          Serial.println("---------------AUTO FIRE Mode is Changed--------------");  
           firecount++;
      // Indicate transmission with LED
        digitalWrite(pinw, HIGH);
        delay(400);
        digitalWrite(pinw, LOW);
    }}

     if (sensorValue>=640 && sensorValue<=670){count_Vibration++;if(count_Vibration==1){
          Serial.println("---------------Vibraton Mode is Changed--------------");
        vibration++;
        if (vibration == 2) {
          vibration = 0;
        digitalWrite(MOTOR_PIN, LOW); // Ensure the vibration is turned off
         
        Serial.println("Vibration Mode OFF-----------------");
         }
      // Indicate transmission with LED
        Serial.println(vibration);
        digitalWrite(pinw, HIGH);
        delay(400);
        digitalWrite(pinw, LOW);

    }}

    if (sensorValue>=865 && sensorValue<=890){count_Menu++;if(count_Menu==1){
         Serial.println(" ---------------- MENU is Selected ----------------");
         int commandToSend = 7 ;
         mySwitch.send(commandToSend, 3); // Send command using 3 bits
         Serial.println(commandToSend);       
    
      // Indicate transmission with LED
        digitalWrite(pinw, HIGH);
        delay(400);
        digitalWrite(pinw, LOW);

    }}

    if (sensorValue>=20 && sensorValue<=35){count_LEDs++;if(count_LEDs==1){
         Serial.println(" /////////////////LED button Mode  is Changed\\\\\\\\\\\\\\\\\\\\");
         int commandToSend = 8 ;
         mySwitch.send(commandToSend, 4); // Send command using 3 bits
         Serial.println(commandToSend);
         button8PressCount++;
         if (button8PressCount==2) { 
                button8PressCount = 0;      // Loop back to the first mode
            }
            delay(500);
      // Indicate_transmission_with_LED
        digitalWrite(pinw, HIGH);
        delay(50);
        digitalWrite(pinw, LOW);

    }}
}
  AutoF(firecount);


  if (vibration==1 && digitalRead(button_pins[4]) == LOW) {
    digitalWrite(MOTOR_PIN, HIGH); 
    Serial.println("Motor on");// Turn on the motor while button7 is pressed

  } else {
    digitalWrite(MOTOR_PIN, LOW);  // Turn off the motor
    // Serial.println("Motor off");
      strip.clear();
      strip.show();  // Turn off the motor
    // Serial.println("Motor off");
  }

}


void Vmotor( const long motorOnDuration) {
    
      // Get the current time
     
    // Vibration ON Mode
    if (vibration == 1) {
        digitalWrite(MOTOR_PIN, HIGH);  // Turn the motor ON
        Serial.println("MOTOR RUNNING...");
        unsigned long currentMillis = millis();
        // Check if it's time to turn the motor OFF
        if (currentMillis - previousMillis >= motorOnDuration) {
            Serial.println(currentMillis - previousMillis);
            digitalWrite(MOTOR_PIN, LOW);  // Turn the motor OFF
            Serial.println("MOTOR STOPPED");
            previousMillis=currentMillis ;  // Update previousMillis to the current time
        }
    }
}



void AutoF(int B){
  if (B==1)
    {
      Serial.println("Fire mode 3 shoots per second Selected---------------------------");
      
    for (int i = 0; i < 3; i++) 
      { 
      unsigned long millis1=millis();
      if (millis1-prevmillis1>=interval1)
          {
          unsigned long millis2=millis();
         
        
          Vmotor(50 );
            if (millis2-prevmillis2>=interval2)
              {  
                
                Serial.println("Fire mode 3 ---------------------------");
                  millis2=prevmillis2;
                  millis1=prevmillis1;
              }
          }
      }
    } 
    if (B==2)
    {  
      Serial.println("Fire mode 10 shoots per second Selected---------------------------");
      
    for (int i = 0; i < 10; i++) 
      {
      unsigned long millis1=millis();
      if (millis1-prevmillis1>=interval1a)
          {
          unsigned long millis2=millis();
          
          
          Vmotor(50 );
            if (millis2-prevmillis2>=interval2a)
              {
                
                Serial.println("Fire mode 10 ---------------------------");
                  millis2=prevmillis2;
                  millis1=prevmillis1;
              }
          }
      }
    }
    if (B==3){
      firecount=0;
      Serial.println("Fire mode off ---------------------------");
    digitalWrite(MOTOR_PIN, LOW);  // Turn off the motor
    }

}
