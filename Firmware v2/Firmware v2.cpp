// There is a second part.

#include<Arduino.h>
#include<Wire.h>
#include<MPU6050.h>
#include<SimpleKalmanFilter.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




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
    byte First_Joystick_X;
    byte First_Joystick_Y;
    byte Second_Joystick_X;
    byte Second_Joystick_Y;
    byte First_Potentiometer;
    byte Second_Potentiometer;
    byte First_Button;
    byte Second_Button;
    byte Third_Button;
    byte Fourth_Button;

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

    // put the initial value 

    // data.potx = 127;
    // data.poty = 127;

    data.First_Joystick_X = 127;
    data.First_Joystick_Y = 127;
    data.Second_Joystick_X = 127;
    data.Second_Joystick_Y = 127;

    data.First_Potentiometer = 0 ;
    data.Second_Potentiometer = 0;

    data.First_Button = 0 ;
    data.Second_Button = 0;
    data.Third_Button = 0;
    data.Fourth_Button = 0;


    // Initialize with the I2C addr 0x3C (for the 128x64)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Clear the buffer
  display.clearDisplay();

  // Set text color to white
  display.setTextColor(SSD1306_WHITE);

  // Set text size
  display.setTextSize(1);

  // Set cursor position
  display.setCursor(0, 0);

  // Print "Hello, World!"
  display.println("Connection....");

  // Display the message
  display.display();

  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,3);
  display.println("Connected....");
  display.display();




}

void loop(){
    

    data.First_Joystick_X = map(analogRead(FIRST_JOYSTICK_X) , 0 , 1023 , 0 , 255);
    data.First_Joystick_Y = map(analogRead(FIRST_JOYSTICK_Y) , 0 , 1023 , 0 , 255);

    data.Second_Joystick_X = map(analogRead(SECOND_JOYSTICK_X) , 0 , 1023 , 0 , 255);
    data.Second_Joystick_Y = map(analogRead(SECOND_JOYSTICK_Y) , 0 , 1023 , 0 , 255);

    data.First_Potentiometer = map(analogRead(FIRST_POTENTIOMETER) , 0 , 1023 , 0 , 255);
    data.Second_Potentiometer = map(analogRead(SECOND_POTENTIOMETER) , 0 , 1023 , 0 , 255);

    data.First_Button = digitalRead(FIRST_BUTTON);
    data.Second_Button = digitalRead(SECOND_BUTTON);
    data.Third_Button = digitalRead(THIRD_BUTTON);
    data.Fourth_Button = digitalRead(FOURTH_BUTTON);
    

    radio.write(&data , sizeof(data_package));


    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Get raw sensor data

    // Convert raw accelerometer data to G's
    AccX = (float)ax / 16384.0;
    AccY = (float)ay / 16384.0;
    AccZ = (float)az / 16384.0;

    // Check if AccY and AccZ are both non-zero to avoid division by zero

    // Convert raw gyroscope data to degrees/second
    GyroX = (float)gx / 131.0;
    GyroY = (float)gy / 131.0;
    GyroZ = (float)gz / 131.0;

    // Calculate roll, pitch, and yaw angles
    // convert the radian to degree = 180/pi
    Roll = atan2(AccY, AccZ) * 180.0 / M_PI;
    Pitch = atan(-AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180.0 / M_PI;
    Yaw = atan2(-GyroX, sqrt(GyroY * GyroY + GyroZ * GyroZ)) * 180.0 / M_PI;

    // Apply Kalman filter to smooth pitch and roll angles
    Pitch = kalmanPitch.updateEstimate(Pitch);
    Roll = kalmanRoll.updateEstimate(Roll);
    Yaw = kalmanYaw.updateEstimate(Yaw);




    // print all data on oled display 
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Pitch:-");
    display.println(Pitch);

    display.setCursor(0 , 10);
    display.print("Roll:-");
    display.println(Roll);

    display.setCursor(0, 20);
    display.print("Yaw:-");
    display.println(Yaw);

    display.setCursor(0 , 30 );
    display.print("J1_X:- ");
    display.println(data.First_Joystick_X);

    display.setCursor(65 , 30);
    display.print("J1_Y:- ");
    display.println(data.First_Joystick_Y);

    display.setCursor(0 , 40 );
    display.print("J2_X:- ");
    display.println(data.Second_Joystick_X);

    display.setCursor(65 , 40);
    display.print("J2_Y:- ");
    display.println(data.Second_Joystick_Y);

    display.setCursor(0 , 50);
    display.print("P1:-");
    display.println(data.First_Potentiometer);

    display.setCursor(65 , 50);
    display.print("P2:-");
    display.println(data.Second_Potentiometer);

    display.setCursor(80 , 0);
    display.print("B1:-");
    display.println(data.First_Button);

    



    display.display();


}