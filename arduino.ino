#include <Process.h>
#include <Bridge.h>
#include <Console.h>
#include <Servo.h>

Servo monServo;
const int ledPin = 13; 

void setup() {
  
  monServo.attach(9); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Bridge.begin();   // Initialize the Bridge
  digitalWrite(ledPin, HIGH);
  Console.begin(); 
  monServo.write(0);
}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl https://velibbulb.mathemagie.repl.co/");
  Console.println("run curl OK");
  
  while(p.running());  

  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    int result = p.parseInt();          // look for an integer
    if (result == 1) {
     
     Serial.println("bus is here");
     digitalWrite(ledPin, HIGH);
     for (int i=0; i <= 100; i++){
          monServo.write(i);
          delay(2);
     } 
     for (int i=100; i >= 1; i--){
          monServo.write(i);
         delay(2);
     }
     digitalWrite(ledPin, LOW); 
    }
    
     if (result == 2) {
        digitalWrite(ledPin, HIGH);//bug in parsing process
     }
       
    if (result == 0) {
        digitalWrite(ledPin, LOW);//bug in parsing process
        Console.println("bus not here");
        Serial.println("bus not here");
    }
  
    
  } 
  delay(100);  // wait 5 seconds before you do it again
}
