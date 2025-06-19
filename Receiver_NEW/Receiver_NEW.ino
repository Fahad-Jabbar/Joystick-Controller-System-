#include <RCSwitch.h>
#include <Joystick.h>

RCSwitch mySwitch = RCSwitch();

#define pin 3  // Pro Micro pin for LED blink and receiver status indication

// Define pin outputs for motor controls
#define Forward 4  // Forward movement pin
#define Backward 5 // Backward movement pin
#define Right 6    // Right movement pin
#define Left 7     // Left movement pin
#define Shoot 8    // Shoot action pin
#define VIB 9 
int shootmode=0;
int lastCommand = 0; // Store the last received command
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  16, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);

  //////////////////////////////////////--------MILLIS Delay for AutoFire -----------\\\\\\\\\\\\\\\\\\\\\\\\\\

 unsigned long prevmillis1=0;
 unsigned long interval1=200;
  unsigned long prevmillis2=0;                                //1
 unsigned long interval2=30;
  
 
 unsigned long interval1a=80;
                                                                //2
 unsigned long interval2a=30;
  
 int firecount=0;
 int vibration=0;
void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  // while (!Serial) {
  //   ; // Wait for the Serial port to connect. Needed for native USB port only.
  // }

  Serial.println("Initializing Receiver...");
  // Initialize Joystick
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);

  // Initialize the LED pin for visual indication
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);  

  // Blink on start to indicate the receiver is initializing
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);

  // Initialize the motor output pins
  pinMode(Forward, OUTPUT);
  pinMode(Backward, OUTPUT);
  pinMode(Right, OUTPUT);
  pinMode(Left, OUTPUT);
  pinMode(Shoot, OUTPUT);
  pinMode(VIB, OUTPUT);

  // Set all motor pins to HIGH (inactive state)
  digitalWrite(Forward, HIGH);
  digitalWrite(Backward, HIGH); 
  digitalWrite(Right, HIGH); 
  digitalWrite(Left, HIGH);
  digitalWrite(Shoot, HIGH);
  digitalWrite(VIB, LOW);

  // Enable RF signal reception on interrupt 1 (pin 3 for Pro Micro)
  mySwitch.enableReceive(1);  // Use interrupt 1, which is pin 3 on the Pro Micro
}

void handleCommand(int command) {
  // Reset X and Y axes before setting
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);

  // Handle received command by setting appropriate outputs and joystick positions
  switch (command) {
    case 1: // Forward
      Serial.println("Forward Selected---------------");
      digitalWrite(Forward, LOW);
      Joystick.setYAxis(-1);  // Move forward
      
      delay(50);
            if (command!=1){}
      break;

    case 2: // Backward
      Serial.println("Backward Selected------------------");
      digitalWrite(Backward, LOW);
      Joystick.setYAxis(1);   // Move backward
      
      delay(50);
      if (command!=2){}
      break;

    case 3: // Right
      Serial.println("Right Selected--------------------");
      digitalWrite(Right, LOW);
      Joystick.setXAxis(1);   // Move right
 
      delay(50);
      if (command!=3){}
      break;

    case 4: // Left
      Serial.println("Left Selected------------------------");
      digitalWrite(Left, LOW);    
      Joystick.setXAxis(-1);  // Move left
      
      delay(50);
      if (command!=4){}
      break;

    case 5: // Shoot
      Serial.println("Shoot Selected---------------------------");
      digitalWrite(Shoot, LOW); 
      Joystick.pressButton(1);  // Simulate shoot button press
      Vmotor(vibration,30 );
      
      delay(50);  // Shorter delay for button press
      if (command!=5){}
      break;

     case 6: // Shoot
      firecount++;
       Serial.println(firecount);
      Serial.println("Shoot Mode Changed");
      delay(500);
      break;

      
      case 7: // Shoot
      Joystick.pressButton(8);  // Simulate shoot button press
      delay(50);  // Shorter delay for button press
      Joystick.releaseButton(8);
      // vibration++;
      // Serial.println(vibration);
      Serial.println("Menu ");
      delay(500);
      break;
      
      case 8: // Shoot
      Joystick.pressButton(2);  // Simulate shoot button press
      delay(50);  // Shorter delay for button press
      Joystick.releaseButton(2);
      // vibration++;
      //  Serial.println(vibration);
      Serial.println("select ");
      delay(500);
      break;
    
      case 9: 
      Serial.println("Direction_NULL ");
      Joystick.releaseButton(1);
      digitalWrite(Shoot, HIGH);
      
      
      Joystick.setXAxis(0);
      digitalWrite(Left, HIGH);
      
      
      Joystick.setXAxis(0);
      digitalWrite(Right, HIGH);
      
      Joystick.setYAxis(0);
      digitalWrite(Backward, HIGH);
      
      
      Joystick.setYAxis(0); 
      digitalWrite(Forward, HIGH);
      break;

    default:
      Serial.println("Unknown command received");
      Joystick.setYAxis(0);
       Joystick.setXAxis(0);
      break;
  }

  // Handle combined commands (e.g., Forward + Right)
  if (lastCommand == 1 && command == 3) { // Forward + Right
    Serial.println("Forward + Right Selected");
    digitalWrite(Forward, LOW);
    digitalWrite(Right, LOW);
    Joystick.setYAxis(-1);  // Forward
    Joystick.setXAxis(1);   // Right
    delay(100);
  digitalWrite(Forward, HIGH);
  digitalWrite(Backward, HIGH); 
  digitalWrite(Right, HIGH); 
  digitalWrite(Left, HIGH);
  } 
  
  else if (lastCommand == 1 && command == 4) { // Forward + Left
    Serial.println("Forward + Left Selected");
    digitalWrite(Forward, LOW);
    digitalWrite(Left, LOW);
    Joystick.setYAxis(-1);  // Forward
    Joystick.setXAxis(-1);  // Left
    delay(100);
  digitalWrite(Forward, HIGH);
  digitalWrite(Backward, HIGH); 
  digitalWrite(Right, HIGH); 
  digitalWrite(Left, HIGH);
  } 
  
  else if (lastCommand == 2 && command == 3) { // Backward + Right
    Serial.println("Backward + Right Selected");
    digitalWrite(Backward, LOW);
    digitalWrite(Right, LOW);
    Joystick.setYAxis(1);   // Backward
    Joystick.setXAxis(1);   // Right
    delay(100);
  digitalWrite(Forward, HIGH);
  digitalWrite(Backward, HIGH); 
  digitalWrite(Right, HIGH); 
  digitalWrite(Left, HIGH);
  } 
  
  else if (lastCommand == 2 && command == 4) { // Backward + Left
    Serial.println("Backward + Left Selected");
    digitalWrite(Backward, LOW);
    digitalWrite(Left, LOW);
    Joystick.setYAxis(1);   // Backward
    Joystick.setXAxis(-1);  // Left
    delay(100);
  digitalWrite(Forward, HIGH);
  digitalWrite(Backward, HIGH); 
  digitalWrite(Right, HIGH); 
  digitalWrite(Left, HIGH);
  }
   
     
  
  // Update the last command received
  lastCommand = command;
}

void loop() {
  if (mySwitch.available()) {
    // Receive the incoming message
    unsigned long receivedValue = mySwitch.getReceivedValue();

    if (receivedValue == 0) {
      Serial.println("Unknown encoding received, ignoring...");
    } else {
      // Print the received value for debugging
      Serial.print("Message Received: ");
      Serial.println(receivedValue);

      int currentCommand = (int)receivedValue; // Cast to int for easier handling

      // Handle the command
      handleCommand(currentCommand);
    }

    // Blink LED to indicate data reception
    digitalWrite(pin, HIGH);
    delay(10);  // Shorter delay for more responsiveness
    digitalWrite(pin, LOW);
    
    
    // Reset the switch after handling the received value
    mySwitch.resetAvailable();
    delay(10);
  }
  AutoF(firecount);
}


////////////////////////////----------------------VIBRATION MODES---------------\\\\\\\\\\\\\\\\\\\\\\\\\\\


void Vmotor(int A,unsigned long interval3a){
   if(A==1){
    Serial.println("Vibration Mode ON");
     digitalWrite(VIB, HIGH);
     
     unsigned long millis2=millis(); 
            if (millis2-prevmillis2>=interval3a)
              {
                digitalWrite(VIB, LOW);
                Serial.println("Vibration Executed ---------------------------");
                  millis2=prevmillis2;
                
              }

   }
   if(A==2){
       vibration= 0;
       Serial.println("Vibration Mode OFF-----------------");
       
   }
}

////////////////////////////----------------------AUTO FIRE MODES---------------\\\\\\\\\\\\\\\\\\\\\\\\\\\

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
          Joystick.pressButton(1);
          digitalWrite(Shoot, LOW);
          Vmotor(vibration,30 );
            if (millis2-prevmillis2>=interval2)
              {  digitalWrite(Shoot, HIGH);
                Joystick.releaseButton(1);
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
          Joystick.pressButton(1);
          digitalWrite(Shoot, LOW);
          Vmotor(vibration,30 );
            if (millis2-prevmillis2>=interval2a)
              { digitalWrite(Shoot, HIGH);
                Joystick.releaseButton(1);
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
    }

}


////////////////////////////----------------------LED_STRIP_MODES---------------\\\\\\\\\\\\\\\\\\\\\\\\\\\