/*************************************************************
*     PROJECT TITLE : BANK LOCKER SECURITY SYSTEM            *                                             *     
**************************************************************/

#define s1 2        // Assigning pin 2 for switch 1 input
#define s2 4        // Assigning pin 4 for switch 2 input 
#define s3 7        // Assigning pin 7 for switch 3 input
#define buzzPin 8   // Assigning pin 8 for buzzer output
#define red     9   // Assigning pin 9 for red led output
#define yellow  10  // Assigning pin 10 for yellow led output
#define green   11  // Assigning pin 11 for green led output
#define echoPin 12  // Assigning pin 12 for echo pin input
#define trigPin 13  // Assigning pin 13 for trigger pin output

int flag = 0; 

void setup() {
  // put your setup code here, to run once:

  // Setting baud rate for serial monitor interfacing
  Serial.begin(9600);

  // Setting Mode of pins
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);  
  pinMode(buzzPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  long duration, distance;
  int p1, p2, p3;
  
  // Measuring distance of hand
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if(flag == 0) // Until password matches continue 
  {
    if(distance < 10){
      
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
        
        Serial.println("You can now enter Password: ");
        
        delay(1000);
        tone(buzzPin, 1000, 200);
        delay(5000);

        // Reading password combination from switches 
        p1=digitalRead(s1);
        p2=digitalRead(s2);
        p3=digitalRead(s3);
        
        if(p1 == 1 && p2 == 0 && p3 == 1){  // If combination matches with 101
          Serial.println("Welcome to IIIT Kalyani!!");
          flag = 1;
        }
        else{
          Serial.println("Wrong Password!"); 
          flag = 0;    
        }
        
    }
      
    else if(distance >= 10 && distance <= 20){
        
        digitalWrite(red,LOW);
        digitalWrite(yellow,HIGH);
        digitalWrite(green,LOW);
        
        Serial.println("Almost there!");
        
        delay(1000);
        tone(buzzPin, 500, 500);
        
    }
    else if(distance > 20){
        
        digitalWrite(red,HIGH);
        digitalWrite(green,LOW);
        digitalWrite(yellow,LOW);
        
        Serial.println("Too far !!");
        
        delay(1000);
        tone(buzzPin, 200, 1000);
        
    }
  }
}
