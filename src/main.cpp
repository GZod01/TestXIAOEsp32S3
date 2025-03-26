#include <Arduino.h>
#include <RPLidar.h>
#include <string>
RPLidar lidar;
HardwareSerial lidarSerial(1);
void setup() {
  lidar.begin(lidarSerial);
  Serial.begin(115200);
  Serial.println("Hello WOrld");
  analogWrite(0,125);
}

typedef struct RPLidarMeasurement RPLIDARRES;
void loop() {
  if(IS_OK(lidar.waitPoint())){
    RPLIDARRES mesureRes = lidar.getCurrentPoint();
    if(mesureRes.quality>14){
      Serial.print("Distance: ");Serial.print(mesureRes.distance);Serial.print("Angle: ");Serial.print(mesureRes.angle);Serial.print("Quality: ");Serial.print(mesureRes.quality);Serial.print("\n");
    }
  }
  Serial.println("Hello");
  delay(500);
}