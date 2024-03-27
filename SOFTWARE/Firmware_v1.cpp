// this is a first version of this control box 


#include<Arduino.h>
#include<Wire.h>
#include<MPU6050.h>
#include<SimpleKalmanFilter.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>


//define the CE and CNS pin 
const int CE_PIN = 7 ;
const int CNS_PIN = 8;

//define the radio
RF24 radio (CE_PIN , CNS_PIN);

//define the address 
const byte address[][7] = {"12345" , "123456"};


// define the mpu6050 class
MPU6050 mpu;

int16_t ax , ay , az ; //define the accelerometer raw data
int16_t gx , gy , gz ; //define the gyroscope raw data 

float AccX , AccY , AccZ ; //define the accelerometer scaled data 
float GyroX , GyroY , GyroZ ; //define the gyroscope scaled data 

float Roll , Pitch , Yaw ; //calculate roll , pitch and yaw 

// Define Kalman filter parameters
SimpleKalmanFilter kalmanPitch(2, 2, 0.15); // Q, R, initial estimate
SimpleKalmanFilter kalmanRoll(2, 2, 0.15);  // Q, R, initial estimate
SimpleKalmanFilter kalmanYaw(2, 2, 0.15);   // Q , R , initial estimate


// define the buzzer 
const int BUZZER = 10 ;
// define the joystick 
const int FIRST_JOYSTICK_X = A0;
const int FIRST_JOYSTICK_Y = A1;
const int SECOND_JOYSTICK_X = A2;
const int SECOND_JOYSTICK_Y = A3;
// define the potentiometer
const int FIRST_POTENTIOMETER = A6;
const int SECOND_POTENTIOMETER = A7;
// define the pushbutton 
const int FIRST_BUTTON = 2;
const int SECOND_BUTTON = 3;
const int THIRD_BUTTON = 4;
const int FOURTH_BUTTON = 5;




// define the global variable FOR JOYSTICK 
int FIRST_JOYSTICK_X_VALUE = 0;
int FIRST_JOYSTICK_Y_VALUE = 0;
int SECOND_JOYSTICK_X_VALUE = 0;
int SECOND_JOYSTICK_Y_VALUE = 0;
// DEFINE THE GLOBAL VARIABLES FOR POTENTIOMETER 
int FIRST_POT_VALUE = 0;
int SECOND_POT_VALUE = 0;
// DEFINE THE GLOBAL VARIABLES FOR PUSHBUTTON 
int FIRST_BUTTON_VALUE = 0;
int SECOND_BUTTON_VALUE = 0;
int THIRD_BUTTON_VALUE = 0;
int FOURTH_BUTTON_VALUE = 0;


struct data_package
{
    byte potx;
    byte poty;

};
data_package data;







void setup(){
    // DEFINE THE BUD RATE IN THIS CASE I AM USING 9600 BITS PER SECOND (BPS)
    Serial.begin(9600);

    // define the mpu6050 
    Wire.begin();
    mpu.initialize();
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2) ; // set the accelerometer +- 2g 
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000) ; //set the gyro range 2000 degree 
    //define the pinMode for buzzer 
    pinMode(BUZZER , OUTPUT);
    //define the pinMode for joystick 
    pinMode(FIRST_JOYSTICK_X , INPUT);
    pinMode(FIRST_JOYSTICK_Y , INPUT);
    pinMode(SECOND_JOYSTICK_X , INPUT);
    pinMode(SECOND_JOYSTICK_Y , INPUT);
    //define the pinMode for potentiometer 
    pinMode(FIRST_POTENTIOMETER , INPUT);
    pinMode(SECOND_POTENTIOMETER  , INPUT);
    //define the pinMode for button 
    pinMode(FIRST_BUTTON , INPUT);
    pinMode(SECOND_BUTTON , INPUT);
    pinMode(THIRD_BUTTON , INPUT);
    pinMode(FOURTH_BUTTON , INPUT);
    // DEFINE THE NRF24L01 MODULE 
    radio.begin();
    radio.openWritingPipe(address[0]); //the address is = 12345
    radio.openReadingPipe(1 , address[1]); //the address is = 123456
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();

    data.potx = 127;
    data.poty = 127;




}

void loop(){

    data.potx = map(analogRead(FIRST_JOYSTICK_X) , 0 , 1023 , 0 , 255);
    data.poty = map(analogRead(FIRST_JOYSTICK_Y) , 0 , 1023 , 0 , 255);

    radio.write(&data , sizeof(data_package));

}