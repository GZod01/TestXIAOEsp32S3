#include <Arduino.h>
#include <RPLidar.h>
#include <string>
RPLidar lidar;
// HardwareSerial lidarSerial(0);
TaskHandle_t Task0;
void LidarProcess(void *);
void setup()
{
    lidar.begin(Serial0);
    lidar.startScan();
    Serial.begin(115200);
    Serial.println("setup");
    pinMode(D0, OUTPUT);
    analogWrite(D0, 150);
    xTaskCreatePinnedToCore(LidarProcess, "Task0", 1000, NULL, 1, &Task0, 0);
}

typedef struct RPLidarMeasurement RPLIDARRES;
void loop()
{
    
}

void LidarProcess(void *pvParameters)
{
    for (;;)
    {
        Serial.print("loop core0 :");
        Serial.println(millis());
        if (IS_OK(lidar.waitPoint()))
        {
            RPLIDARRES mesureRes = lidar.getCurrentPoint();
            if (mesureRes.distance < 1000 && mesureRes.quality > 14)
            {
                float angle = mesureRes.angle * (float)DEG_TO_RAD;
                float distance = mesureRes.distance;
                float x = cos(angle) * distance;
                float y = sin(angle) * distance;
                Serial.print(">point:");
                Serial.print((double)x);
                Serial.print(":");
                Serial.print((double)y);
                // Serial.print(":");
                // Serial.print((double)millis());
                Serial.println("|xy");
            }
        }
        else
        {
            // analogWrite(D0, 0); // stop the rplidar motor
            Serial.println("Lidar Stopped");
            // try to detect RPLIDAR...
            rplidar_response_device_info_t info;
            if (IS_OK(lidar.getDeviceInfo(info, 100)))
            {
                Serial.println("Lidar found");
                // detected...
                lidar.startScan();
                // analogWrite(D0, 150);
                delay(1000);
            }
            else
            {
                Serial.println("Lidar not found");
            }
        }
    }
}