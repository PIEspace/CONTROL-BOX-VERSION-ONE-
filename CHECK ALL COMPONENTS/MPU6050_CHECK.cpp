#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize the MPU6050 sensor
  mpu.initialize();

  // Check if the sensor connection was successful
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Set the gyro range to +/- 250 degrees/sec
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

  // Set the accelerometer range to +/- 2g
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
}

void loop() {
  // Read accelerometer and gyroscope data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Print accelerometer and gyroscope data
  Serial.print("Accelerometer: ");
  Serial.print("x = "); Serial.print(ax); Serial.print(" | ");
  Serial.print("y = "); Serial.print(ay); Serial.print(" | ");
  Serial.print("z = "); Serial.println(az);

  Serial.print("Gyroscope: ");
  Serial.print("x = "); Serial.print(gx); Serial.print(" | ");
  Serial.print("y = "); Serial.print(gy); Serial.print(" | ");
  Serial.print("z = "); Serial.println(gz);

  delay(1000); // Delay for 1 second
}
