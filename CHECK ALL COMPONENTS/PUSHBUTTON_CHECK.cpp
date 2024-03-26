// check the pushbutton

#include <Arduino.h>

const int FIRST_BUTTON = 2;
const int SECOND_BUTTON = 3;
const int THIRD_BUTTON = 4;
const int FOURTH_BUTTON = 5;

int FIRST_BUTTON_VALUE = 0;
int SECOND_BUTTON_VALUE = 0;
int THIRD_BUTTON_VALUE = 0;
int FOURTH_BUTTON_VALUE = 0;

void setup()
{
    // define the bud rate

    Serial.begin(9600);

    pinMode(FIRST_BUTTON, INPUT);
    pinMode(SECOND_BUTTON, INPUT);
    pinMode(THIRD_BUTTON, INPUT);
    pinMode(FOURTH_BUTTON, INPUT);
}

void loop()
{

    FIRST_BUTTON_VALUE = digitalRead(FIRST_BUTTON);
    SECOND_BUTTON_VALUE = digitalRead(SECOND_BUTTON);
    THIRD_BUTTON_VALUE = digitalRead(THIRD_BUTTON);
    FOURTH_BUTTON_VALUE = digitalRead(FOURTH_BUTTON);

    // print on the serial monitor
    Serial.print(" FIRST_BUTTON = ");
    Serial.print(FIRST_BUTTON_VALUE);
    Serial.print(" , ");

    Serial.print(" SECOND_BUTTON = ");
    Serial.print(SECOND_BUTTON_VALUE);
    Serial.print(" , ");

    Serial.print(" THIRD_BUTTON = ");
    Serial.print(THIRD_BUTTON_VALUE);
    Serial.print(" , ");

    Serial.print(" FOURTH_BUTTON = ");
    Serial.println(FOURTH_BUTTON_VALUE);

    delay(15);
}