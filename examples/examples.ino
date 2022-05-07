#include "DFRobot_Microwave_Radar_Module.h"

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Use soft serial port
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
DFRobot_Microwave_Radar_Module Sensor(/*softSerial =*/&softSerial);
#elif defined(ESP32)   // Hard serial port using remappable pins: Serial1
DFRobot_Microwave_Radar_Module Sensor(/*hardSerial =*/&Serial1, /*rx =*/D3, /*tx =*/D2);
#else   // Use hard serial port: Serial1
DFRobot_Microwave_Radar_Module Sensor(/*hardSerial =*/&Serial1);
#endif

int ledPin = 13;

void setup()
{
  Serial.begin(115200);

  //Initialize sensor
  while ( !( Sensor.begin() ) ) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  pinMode(ledPin, OUTPUT);

  /**
     @brief Restore factory settings
  */
  Sensor.factoryReset();

  /**
     @brief Configuration distance, 0~11m, default is 6m.
  */
  Sensor.detRangeCfg(6);

  /**
     @brief Configure the detection sensitivity. The greater the value of 0~9, the higher the sensitivity. The default value is 7.
  */
  Sensor.setSensitivity(3);

  /**
     @brief Configure output delay time
  */
  Sensor.outputLatency(1, 15);

  /**
     @brief Configure interface polarity of output control signal.
  */
  Sensor.setGpioMode(1);
}

void loop()
{
  int val = Sensor.readPresenceDetection();
  digitalWrite(ledPin, val);
  Serial.println(val);
}