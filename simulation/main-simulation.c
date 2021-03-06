/* Main.ino file generated by New Project wizard
 *
 * Created:   Thu Mar 18 2021
 * Processor: Arduino Uno
 * Compiler:  Arduino AVR (Proteus)
 */

// Peripheral Configuration Code (do not edit)
//---CONFIG_BEGIN---
#pragma GCC push_options
#pragma GCC optimize ("Os")

#include <core.h> // Required by cpu
#include <cpu.h>

#pragma GCC pop_options

// Peripheral Constructors
CPU &cpu = Cpu;

void peripheral_setup () {
}

void peripheral_loop() {
}
//---CONFIG_END---

#include <SoftwareSerial.h>
// declare tx and rx pins for the monitor
SoftwareSerial mySerial(3,4);

// pins
unsigned int five_bob = 8;
unsigned int ten_bob = 7;
unsigned int twenty_bob = 6;
unsigned int forty_bob = 5;
unsigned int start_button = 2;
unsigned int motor = 9;
unsigned int led_indicator = 0;

// volume
unsigned int volume;
unsigned int coin_value;



void setup () {
   peripheral_setup();
   mySerial.begin(9600);
   Serial.begin(9600);
   delay(500);
   
   // set pinModes
   pinMode(five_bob, INPUT);
   pinMode(ten_bob, INPUT);
   pinMode(twenty_bob, INPUT);
   pinMode(forty_bob, INPUT);
   pinMode(motor, OUTPUT);
   
}

void loop() {
   peripheral_loop();
   
   // check which coin has been inserted
   if(digitalRead(five_bob) == HIGH){
      mySerial.println("Ksh 5 ");	// show coin value inserted
      coin_value = 5;	// assign coin value
      volume = calculateVolume(5); 	// calculate the volume of oil to be pumped
      mySerial.println("Volume:  ");
      mySerial.print(volume);
      mySerial.println();
      
      mySerial.println("Press the start buton: ");
      
      // start dispensing the volume calculated
      runMotor();
      
   }else if(digitalRead(ten_bob) == HIGH){
      mySerial.println("Kshs 10");
      coin_value = 10;
      volume = calculateVolume(coin_value);
      mySerial.println("Volume:  ");
      mySerial.print(volume);
      mySerial.println();
      
      // start dispensing the volume calculated
      runMotor();
      
   }else if(digitalRead(twenty_bob) == HIGH){
      mySerial.println("Ksh 20");
      coin_value = 20;
      volume = calculateVolume(coin_value);
      mySerial.println("Volume:  ");
      mySerial.print(volume);
      mySerial.println();
      
      // start dispensing the volume calculated
      runMotor();
      
   }else if(digitalRead(forty_bob) == HIGH){
      mySerial.println("Ksh 40");
      coin_value = 40;
      volume = calculateVolume(coin_value);
      mySerial.println("Volume:  ");
      mySerial.print(volume);
      mySerial.print(" mls");
      mySerial.println();
      
      // start dispensing the volume calculated
      runMotor();
      
   }   
   delay(500);
   
}

int calculateVolume(int coin_value){
   // switch case
   // volume values are approximations
   switch(coin_value){
      case 5:
	 return 30;
	 break;
	 
      case 10:
	 return 60;
	 break;
	 
      case 20:
	    return 120;
	    break;
	    
      case 40:
	 return 240;
	 break;
	 
	default:
	 return 0;
   }
   
}

void runMotor(){

      while(digitalRead(start_button) == LOW){
	 // wait for the start button to be pressed
	 mySerial.println("Press the start button...");
	 delay(200);
      }
      
      if(digitalRead(start_button) == HIGH){
	 // start pumping the volume of oil
	 // run the dc motor as pump for simulation
	 //using PWM here
	 
	 mySerial.println("Dispensing...");
	 mySerial.print(volume);
	 for(unsigned int i=0; i <volume; i++){
	    analogWrite(motor, i);
	    digitalWrite(led_indicator, HIGH);
	    mySerial.print(i);
	    mySerial.print(" mls");
	    mySerial.println();
	    delay(10);
	 } 
	 
	 // stop the motor
	 analogWrite(motor, LOW);
	 
	 // show message when done
	 mySerial.println("Done. Please remove container");
	 
	 }
      
}
