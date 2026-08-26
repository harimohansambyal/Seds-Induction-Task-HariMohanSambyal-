// LCD
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

//STORM
const int LDR_sensor_pin = A1;
const int led_pin = A0;
const int light_threshold = 550;

//CHARYBDIS
const int ping_pin = 6;
const int buzzer_pin = 7;
const int dist_threshold = 100;

//ANCHOR
const int button_pin = A2;
bool buttonON = false;
int lastbuttonsignal=LOW;

//WRECKED
bool wrecked;
float timer=0;

/*CUSTOM FUNCTIONS
___________________________________________________________________________________________________________________________________________________
 DEFINED FUNCTION TO GET DATA FROM ULTRASONIC DISTANCE SENSOR*/
int cm_distance_ping() {
  pinMode(ping_pin, OUTPUT);
  digitalWrite(ping_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_pin, LOW);

  pinMode(ping_pin, INPUT);
  int input_signal = pulseIn(ping_pin, HIGH);
  
  return input_signal / 29 / 2; 
  // The speed of sound is 340 m/s or 29 microseconds per centimeter, so divide time signal by 29
  // The ping travels out and back, so to find the distance of the object we take half of the distance travelled.
  }
/*__________________________________________________________________________________________________________________________________________________
 DEFINED FUNCTION TO GET THE TOGGLE STATE OF THE BUTTON*/
void buttonCheck(){
  int buttonsignal = digitalRead(button_pin);
  if (buttonsignal == HIGH && lastbuttonsignal == LOW){
    buttonON=!buttonON;
    delay(50);
  }
  lastbuttonsignal = buttonsignal;
  }
//___________________________________________________________________________________________________________________________________________________



void setup() {
  pinMode(led_pin,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(button_pin,INPUT);
  lcd.begin(16,2);
}


void loop() {
    if(wrecked){                           //if entered wrecked state, requires restart
      lcd.setCursor(0,0);
      lcd.print("SHIP WRECKED");
      lcd.setCursor(0,1);
      lcd.print("RESTART SYSTEM");
      wrecked = true;
    }
    
    else{
      
      lcd.setCursor(0,0);
      lcd.print("VESSEL STATE    ");
      lcd.setCursor(0,1);
      lcd.print("OPEN SEA        ");

//reading LDR SENSOR 
      int LDR_reading=analogRead(LDR_sensor_pin);
//reading DISTANCE SENSOR
      int distance_cm = cm_distance_ping();
 //reading BUTTON SENSOR and calling buttoncheck to get anchor dropped state when previous state is open sea
      int buttonsignal = digitalRead(button_pin);
      //makes anchor work in open sea
      buttonCheck();
      while(buttonON){
          timer = 0;
          lcd.setCursor(0,0);
          lcd.print("VESSELSTATE:SAFE");
          lcd.setCursor(0,1);
          lcd.print("ANCHOR DROPPED");
          buttonCheck();
      }

//STORM LOOP
      while(LDR_reading<light_threshold){
        timer +=0.25;
        lcd.setCursor(0,0);
        lcd.print("!STORM!         ");
        lcd.setCursor(0,1);
        lcd.print("Time Remaining");
        lcd.setCursor(15,1);
        lcd.print(timer);
        digitalWrite(led_pin,HIGH);
        delay(125);
        digitalWrite(led_pin,LOW);
        delay(125);

        if(timer == 5){       
          wrecked = true;
          lcd.clear();
          goto wreckedloop;  // when timer hits 5, exits to end and enters the starting if statement permanently looping over it in wrecked state
        }
      
        buttonCheck();
        while(buttonON){
          timer = 0;
          lcd.setCursor(0,0);
          lcd.print("VESSELSTATE:SAFE");
          lcd.setCursor(0,1);
          lcd.print("ANCHOR DROPPED");
          lcd.setCursor(15,1);
          lcd.print(" ");
          buttonCheck();
              
          }
        LDR_reading=analogRead(LDR_sensor_pin);
      }
      timer = 0;

// CHARYBDIS LOOP
      while(distance_cm < dist_threshold){
        timer +=0.25;
        lcd.setCursor(0,0);
        lcd.print("!CHARYBDIS!     ");
        lcd.setCursor(0,1);
        lcd.print("Time Remaining");
        lcd.setCursor(15,1);
        lcd.print(timer);
        tone(buzzer_pin,1000,250);
        delay(125);
        tone(buzzer_pin,500,250);
        delay(125);

        if(timer == 5){
          wrecked = true;
          lcd.clear();
          goto wreckedloop;  //when timer hits 5, exits to end and enters the starting is staement permanently looping over it in wrecked state
        }
       
        buttonCheck();
        while(buttonON){
          timer = 0;
          lcd.setCursor(0,0);
          lcd.print("VESSELSTATE:SAFE");
          lcd.setCursor(0,1);
          lcd.print("ANCHOR DROPPED");
          lcd.setCursor(15,1);
          lcd.print(" ");
          buttonCheck();
        }     
        distance_cm = cm_distance_ping();
      }
    
    wreckedloop:
    timer=0;
    }
}












    



