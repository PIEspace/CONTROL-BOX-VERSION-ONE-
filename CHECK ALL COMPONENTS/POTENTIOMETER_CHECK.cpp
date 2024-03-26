// check the potentiometer 

#include<Arduino.h>

// define the potentiometer 
const int FIRST_POT = A6;
const int SECOND_POT = A7;

int FIRST_POT_VALUE = 0 ;
int SECOND_POT_VALUE = 0;



void setup(){
    // define the bud rate 
    Serial.begin(9600);

    pinMode(FIRST_POT , INPUT);
    pinMode(SECOND_POT , INPUT);
}


void loop(){

    FIRST_POT_VALUE = analogRead(FIRST_POT);
    SECOND_POT_VALUE = analogRead(SECOND_POT);


    // print on the serial monitor
    Serial.print("pot = ");
    Serial.print(FIRST_POT_VALUE);
    Serial.print(" , ");

    Serial.print("pot b = ");
    Serial.println(SECOND_POT_VALUE);
    

    delay(15);

}