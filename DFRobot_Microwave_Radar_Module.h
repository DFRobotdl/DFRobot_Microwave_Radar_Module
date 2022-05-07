#ifndef DFRobot_Microwave_Radar_Module_H
#define DFRobot_Microwave_Radar_Module_H

#include <Arduino.h>
#include <Wire.h>
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
#include <SoftwareSerial.h>
#endif


//#define ENABLE_DBG   //!< Open this macro and you can see the details of the program
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif


class DFRobot_Microwave_Radar_Module
{
  public:
    /**
       @brief  Constructor
       @param serial - Serial port for communication, supporting hard serial port and soft serial port.
       @param rx - UART Pin for receiving data
       @param tx - UART Pin for sending data
       @return None
    */
    DFRobot_Microwave_Radar_Module(HardwareSerial *hardSerial);
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
    DFRobot_Microwave_Radar_Module(SoftwareSerial *softSerial);
#elif defined(ESP32)
    DFRobot_Microwave_Radar_Module(HardwareSerial *hardSerial, uint8_t rx, uint8_t tx);
#endif

    /**
       @brief 初始化函数

       @return true success
       @return false mistake
    */
    bool begin();

    /**
       @brief Read whether the sensor detects the target.

       @return true Target detected.
       @return false Target not detected.
    */
    bool readPresenceDetection();

    /**
       @brief Configuration distance

       @param distance Detection distance, 0~11 meters, the default is 6 meters.
    */
    void detRangeCfg(int distance);

    /**
       @brief Configure detection sensitivity

       @param sensitivity Detection sensitivity, the greater the value from 0 to 9, the higher the sensitivity, and the default value is 7.
    */
    void setSensitivity(int sensitivity);

    /**
       @brief Configure output delay time

       @param par1 Confirm delay; When the target is detected, the target valid signal will be output after the par1 duration. The value range is 0 ~ 100, unit second, and the default value is 1 second
                   For scenes where the detection response speed is not high, it is recommended that it be no less than 1 second, which can greatly reduce the false alarm rate.

       @param par2 Disappearing delay; If the target is not detected, an invalid target signal will be output after the par2 duration. The value range is 1 ~ 1500, and the unit second is 15 seconds by default.
    */
    void outputLatency(int par1, int par2);

    /**
       @brief Configure interface polarity of output control signal.

       @param voltage True:outputs high level when there is a target, low level when there is no target (default state), False:outputs low level when there is a target, and outputs high level when there is no target.
    */
    void setGpioMode(bool voltage);

    /**
       @brief Restore factory settings

    */
    void factoryReset ( void );

  protected:


    size_t readN(char *buf, size_t len);

    /**
       @brief Send commands to sensors.

       @param COM Command to be sent
       @return true Sensor successfully executed.
       @return false Sensor not executed.
    */
    bool sendCommand(const char *COM);

    /**
       @brief Read command execution status

       @return true Execution succeeded.
       @return false Execution error
    */
    bool readDone();

    /**
       @brief Read the original data detected by the sensor

       @param buf Used to store raw data.
       @return true Read successfully.
       @return false Read failed.
    */
    bool recdData(char *buf);

  private:
    // uart *_uartSerial;
    Stream *_ser;

};
#endif
