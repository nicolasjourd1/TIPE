#include <Wire.h>//https://www.arduino.cc/en/reference/wire
#include <Adafruit_MPU6050.h>//https://github.com/adafruit/Adafruit_MPU6050
#include <Adafruit_Sensor.h>//https://github.com/adafruit/Adafruit_Sensor

Adafruit_MPU6050 mpu;

void setup() {
 	Serial.begin(115200);
  if (!mpu.begin(0x68)) { 
 			Serial.println("MPU6050 non trouvé !");
 	}
 	mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
 	mpu.setGyroRange(MPU6050_RANGE_250_DEG);
 	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
void loop() {
 	readMPU();
  delay(10);
}

void readMPU( ) { 
 	sensors_event_t a, g, temp;
 	mpu.getEvent(&a, &g, &temp);
  String res = "Arduino:";
 	res += (a.acceleration.x);
 	res += (",");
 	res += (a.acceleration.y);
 	res += (",");
 	res += (a.acceleration.z);
  res += (",");
 	res += (g.gyro.x);
 	res += (",");
 	res += (g.gyro.y);
 	res += (",");
 	res += (g.gyro.z);
  Serial.println(res);
}