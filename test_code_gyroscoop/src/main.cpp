#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>       

Adafruit_MPU6050 mpu;
float x_as = 0;
float y_as = 0;
float z_as = 0;
float tempx_as = 0;
float tempy_as = 0;
float tempz_as = 0;

int teller = 100000;


void setup(void) {
	Serial.begin(115200);

	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

	delay(1000);
}

void loop() {
	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);
	if (teller > 60000){
		if (tempx_as != round(x_as/1000)){
			x_as = tempx_as;
		}
		if (tempy_as != round(y_as/1000)){
			y_as = tempy_as;
		}
		if (tempz_as != round(z_as/1000)){
			z_as = tempz_as;
		}
		tempx_as = round(x_as/1000);
		tempy_as = round(y_as/1000);
		tempz_as = round(z_as/1000);
		teller = 0;
	}

	if (round(x_as/1000) < 0){
		x_as = 359000;
	}
	if (round(x_as/1000) > 359){
		x_as = 0;
	}
	if (round(y_as/1000) < 0){
		y_as = 359000;
	}
	if (round(y_as/1000) > 359){
		y_as = 0;
	}
	if (round(z_as/1000) < 0){
		z_as = 359000;
	}
	if (round(z_as/1000) > 359){
		z_as = 0;
	}
	// rotation
	// x: + 0.12 y: + 0.25 z: + 0.055

	// rotation donker
	// x: + 0.064 y: - 0.01 z: + 0.0044
	x_as += round((g.gyro.x + 0.12)*100)*2.195121951219512;
	y_as += round((g.gyro.y + 0.025)*100)*2.195121951219512;
	z_as += round((g.gyro.z + 0.055)*100)*2.195121951219512;

	Serial.print("Rotation X: ");
	Serial.print(round(x_as/1000));
	Serial.print(", Y: ");
	Serial.print(round(y_as/1000));
	Serial.print(", Z: ");
	Serial.print(round(z_as/1000));
	Serial.println(" grad");
	// Serial.print(" Acceleration X: ");
	// Serial.print(a.acceleration.x);
	// Serial.print(", Y: ");
	// Serial.print(a.acceleration.y);
	// Serial.print(", Z: ");
	// Serial.print(a.acceleration.z);
	// Serial.println(" m/s^2");
	

	// temperature
	// Serial.print("Temperature: ");
	// Serial.print(temp.temperature);
	// Serial.println(" degC");

	delay(0.1);
	teller++;
}

// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>
// #include <Arduino.h>

// Adafruit_MPU6050 mpu;

// void setup(void) {
// 	Serial.begin(115200);

// 	// Try to initialize!
// 	if (!mpu.begin()) {
// 		Serial.println("Failed to find MPU6050 chip");
// 		while (1) {
// 		  delay(10);
// 		}
// 	}
// 	Serial.println("MPU6050 Found!");

// 	// set accelerometer range to +-8G
// 	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

// 	// set gyro range to +- 500 deg/s
// 	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

// 	// set filter bandwidth to 21 Hz
// 	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

// 	delay(100);
// }

// void loop() {
// 	/* Get new sensor events with the readings */
// 	sensors_event_t a, g, temp;
// 	mpu.getEvent(&a, &g, &temp);

// 	/* Print out the values */
// 	Serial.print("Acceleration X: ");
// 	Serial.print(a.acceleration.x);
// 	Serial.print(", Y: ");
// 	Serial.print(a.acceleration.y);
// 	Serial.print(", Z: ");
// 	Serial.print(a.acceleration.z);
// 	Serial.println(" m/s^2");

// 	Serial.print("Rotation X: ");
// 	Serial.print(g.gyro.x);
// 	Serial.print(", Y: ");
// 	Serial.print(g.gyro.y);
// 	Serial.print(", Z: ");
// 	Serial.print(g.gyro.z);
// 	Serial.println(" rad/s");

// 	Serial.print("Temperature: ");
// 	Serial.print(temp.temperature);
// 	Serial.println(" degC");

// 	Serial.println("");
// 	delay(500);
// }