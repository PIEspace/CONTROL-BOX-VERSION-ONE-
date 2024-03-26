// In this code we will check the joystick. Basically we have two joysticks, we will check both the joysticks one by one.
// This is the code, you will get it easily on github. https://github.com/PIEspace?tab=repositories
// You can also follow me on Instagram? https://www.instagram.com/creativeindia__/?hl=en

#include <Arduino.h>

// define the joystick pins
int FIRST_JOYSTICK_X = A0;
int FIRST_JOYSTICK_Y = A1;
int SECOND_JOYSTICK_X = A2;
int SECOND_JOYSTICK_Y = A3;

int FIRST_JOYSTICK_X_VALUE = 0;
int FIRST_JOYSTICK_Y_VALUE = 0;
int SECOND_JOYSTICK_X_VALUE = 0;
int SECOND_JOYSTICK_Y_VALUE = 0;

void setup()
{
    // define the bud rate
    Serial.begin(9600);

    // DEFINE THE pinMode
    pinMode(FIRST_JOYSTICK_X, INPUT);
    pinMode(FIRST_JOYSTICK_Y, INPUT);

    pinMode(SECOND_JOYSTICK_X, INPUT);
    pinMode(SECOND_JOYSTICK_Y, INPUT);
}

void loop()
{

    FIRST_JOYSTICK_X_VALUE = analogRead(FIRST_JOYSTICK_X);
    FIRST_JOYSTICK_Y_VALUE = analogRead(FIRST_JOYSTICK_Y);

    SECOND_JOYSTICK_X_VALUE = analogRead(SECOND_JOYSTICK_X);
    SECOND_JOYSTICK_Y_VALUE = analogRead(SECOND_JOYSTICK_Y);

    // print on the serial monitor
    Serial.print(" FIRST_JOYSTICK_X = ");
    Serial.print(FIRST_JOYSTICK_X_VALUE);
    Serial.print(" , ");

    Serial.print(" FIRST_JOYSTICK_Y = ");
    Serial.print(FIRST_JOYSTICK_Y_VALUE);
    Serial.print(" , ");

    Serial.print(" SECOND_JOYSTICK_X = ");
    Serial.print(SECOND_JOYSTICK_X_VALUE);
    Serial.print(" , ");

    Serial.print(" SECOND_JOYSTICK_Y = ");
    Serial.println(SECOND_JOYSTICK_Y_VALUE);

    delay(15);
}