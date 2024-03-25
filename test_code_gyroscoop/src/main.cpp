#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>       

Adafruit_MPU6050 mpu;
float x_as = 0;
float y_as = 0;
float z_as = 0;


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

	// speed
	// Serial.print("Acceleration X: ");
	// Serial.print(a.acceleration.x);
	// Serial.print(", Y: ");
	// Serial.print(a.acceleration.y);
	// Serial.print(", Z: ");
	// Serial.print(a.acceleration.z);
	// Serial.println(" m/s^2");

	// rotation
	x_as += round((g.gyro.x + 0.12)*10);
	y_as += round((g.gyro.y + 0.025)*10);
	z_as += round((g.gyro.z + 0.055)*10);


	Serial.print("Rotation X: ");
	Serial.print(x_as);
	Serial.print(", Y: ");
	Serial.print(y_as);
	Serial.print(", Z: ");
	Serial.print(z_as);
	Serial.println(" rad");

	// temperature
	// Serial.print("Temperature: ");
	// Serial.print(temp.temperature);
	// Serial.println(" degC");

	delay(0.1);
}