#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int IN1 = 6;                     

int IN2 = 7;                      

int IN3 = 8;              

int IN4 = 9;

int IN5 = 10;                     

int IN6 = 11;                      

int IN7 = 12;              

int IN8 = 13;

int Plastic = 2;

bool Plastic_push = false;

int Paper = 3;

bool Paper_push = false;

int Red = 5;

int Green = 4;

int motorSpeed = 1200;

int lookup1[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int lookup2[8] = {B01001, B00001, B00011, B00010, B00110, B00100, B01100, B01000};

int count = 0;

int countnum = 80;

 

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(IN1, OUTPUT);    

  pinMode(IN2, OUTPUT);   

  pinMode(IN3, OUTPUT);   

  pinMode(IN4, OUTPUT);

  pinMode(IN5, OUTPUT);    

  pinMode(IN6, OUTPUT);   

  pinMode(IN7, OUTPUT);   

  pinMode(IN8, OUTPUT);    

  pinMode(Plastic, INPUT);

  pinMode(Paper, INPUT);

  pinMode(Red, OUTPUT);
  pinMode(Green,OUTPUT);

  digitalWrite(Green, HIGH);

}

 

void loop() {

  if (digitalRead(Plastic)){

    Plastic_push = true;

        

  }

 

  if (Plastic_push){

    motor();

  }

 

  if (digitalRead(Paper)){

    Paper_push = true;

  }

 

  if (Paper_push){

    motor();

  }

  lcd.setCursor(3,0);   
  lcd.print("Save Earth!");  

}

 

void motor(){

  if (count < countnum){ 

    clockwise();

    digitalWrite(Red,HIGH);

    digitalWrite(Green,LOW);

  }


   
  else if (count == countnum){

    delay(3000);

    digitalWrite(Red,HIGH);

    digitalWrite(Green,LOW);

  }

 
  else if (count == countnum * 2) {

    count = 0;

    Plastic_push = false;

    Paper_push = false;

    digitalWrite(Red, LOW);

    digitalWrite(Green,HIGH);

  }

 

  else {

    anticlockwise();

    digitalWrite(Red,HIGH);

    digitalWrite(Green,LOW);

  }

  count++;  

}

 

void anticlockwise()

{

  for (int i = 0; i < 8; i++)                                         

  {

    setOutput(i);                                                     

    delayMicroseconds(motorSpeed);                      

  }

}

 

void clockwise()

{

  for (int i = 7; i >= 0; i--)                                     

  {

    setOutput(i);                                                    

    delayMicroseconds(motorSpeed);                     

  }

}

 

void setOutput(int out)

{ 

  if (Plastic_push) {

  digitalWrite(IN1, bitRead(lookup1[out], 0));            

  digitalWrite(IN2, bitRead(lookup1[out], 1));            

  digitalWrite(IN3, bitRead(lookup1[out], 2));             

  digitalWrite(IN4, bitRead(lookup1[out], 3));

  }

 

  else {

  digitalWrite(IN5, bitRead(lookup2[out], 0));            

  digitalWrite(IN6, bitRead(lookup2[out], 1));            

  digitalWrite(IN7, bitRead(lookup2[out], 2));             

  digitalWrite(IN8, bitRead(lookup2[out], 3));    

  }

}
