#include "DFRobot_Microwave_Radar_Module.h"

DFRobot_Microwave_Radar_Module::DFRobot_Microwave_Radar_Module(HardwareSerial *hardSerial)
{
  hardSerial->begin(115200);
  _ser = hardSerial;
}

#if defined(__AVR__)||defined(ESP8266)
DFRobot_Microwave_Radar_Module::DFRobot_Microwave_Radar_Module(SoftwareSerial *softSerial)
{
  softSerial->begin(115200);
  _ser = softSerial;
}
#elif defined(ESP32)
DFRobot_Microwave_Radar_Module::DFRobot_Microwave_Radar_Module(HardwareSerial *hardSerial, uint8_t rx, uint8_t tx)
{
  hardSerial->begin(115200, SERIAL_8N1, rx, tx);
  _ser = hardSerial;
}
#endif

bool DFRobot_Microwave_Radar_Module::begin()
{
  if (NULL == _ser) {
    return false;
  }
  return true;
}

size_t DFRobot_Microwave_Radar_Module::readN(char *buf, size_t len)
{
  size_t offset = 0, left = len;
  int16_t Tineout = 1500;
  char *buffer = buf;
  long curr = millis();
  while (left) {
    if (_ser->available()) {
      buffer[offset] = _ser->read();
      offset++;
      left--;
    }
    if (millis() - curr > Tineout) {
      break;
    }
  }
  return offset;
}

bool DFRobot_Microwave_Radar_Module::sendCommand(const char* COM)
{
  long curr = millis();    //Used to judge timeout.
  long curr1 = curr;       //Used to judge timeout.
  _ser->write(COM);
  while (1) {

    if (millis() - curr > 1000) {
      DBG(COM);
      DBG("Error\n");
      return false;    //If the correct data has not been read for more than 1000 milliseconds, it will be regarded as a timeout and false will be returned.
    }

    if (millis() - curr1 > 300) {
      _ser->write(COM);  //Send a read instruction
      curr1 = millis();
    }

    delay(100);
    if (readDone()) {
      DBG(COM);
      DBG("Done\n");
      return true;
    }
  }
}

bool DFRobot_Microwave_Radar_Module::readDone()
{
  int len = _ser->available();
  if (len > 0) {
    char Data[len] = {0};
    for (int i = 0; i < len; i++) {
      Data[i] = _ser->read();
    }
    //DBG(Data);
    if (strstr(Data, "Done") > 0) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool DFRobot_Microwave_Radar_Module::readPresenceDetection()
{
  char dat[16] = {0};
  while (1) {
    if (recdData(dat)) {
      DBG(dat);
      if (dat[7] == '1') {
        return true;
      } else {
        if (dat[7] == '0') {
          return false;
        }
      }
    }
  }

}

bool DFRobot_Microwave_Radar_Module::recdData(char *buf)
{

  int Tineout = 50000;
  long curr = millis();
  char ch;
  bool ret = false;
  while (!ret) {
    if (millis() - curr > Tineout) {
      break;
    }

    if (readN(&ch, 1) == 1) {
      if (ch == '$') {
        buf[0] = ch;
        if (readN(&ch, 1) == 1) {
          if (ch == 'J') {
            buf[1] = ch;
            if (readN(&ch, 1) == 1) {
              if (ch == 'Y') {
                buf[2] = ch;
                if (readN(&ch, 1) == 1) {
                  if (ch == 'B') {
                    buf[3] = ch;
                    if (readN(&ch, 1) == 1) {
                      if (ch == 'S') {
                        buf[4] = ch;
                        if (readN(&ch, 1) == 1) {
                          if (ch == 'S') {
                            buf[5] = ch;
                            if (readN(&buf[6], 9) == 9) {
                              ret = true;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return ret;
}

void DFRobot_Microwave_Radar_Module::detRangeCfg(int distance)
{
  char comDetRangeCfg[14] = {0};
  sprintf(comDetRangeCfg, "setRange 0 %d", distance);
  sendCommand("sensorStop");                                  //Stop detection
  sendCommand(comDetRangeCfg);                                //Configuration distance
  sendCommand("saveConfig");                                  //Save configuration
  sendCommand("sensorStart");                                 //Start the module to start running.
}

void DFRobot_Microwave_Radar_Module::setSensitivity(int sensitivity)
{
  char comSetSensitivity[18] = {0};
  sprintf(comSetSensitivity, "setSensitivity %d", sensitivity);
  sendCommand("sensorStop");                                     //Stop detection
  sendCommand(comSetSensitivity);                                //Configuration sensitivity
  sendCommand("saveConfig");                                     //Save configuration
  sendCommand("sensorStart");                                    //Start the module to start running.
}

void DFRobot_Microwave_Radar_Module::outputLatency(int par1, int par2)
{
  char comOutputLatency[20] = {0};
  sprintf(comOutputLatency, "setLatency %d %d", par1, par2);
  sendCommand("sensorStop");                                      //Stop detection
  sendCommand(comOutputLatency);                                  //Configure output delay time
  sendCommand("saveConfig");                                      //Save configuration
  sendCommand("sensorStart");                                     //Start the module to start running.
}

void DFRobot_Microwave_Radar_Module::factoryReset ( void )
{
  sendCommand("sensorStop");                    //Stop detection
  sendCommand("resetCfg");                      //Restore factory settings
  sendCommand("sensorStart");                   //Start the module to start running.
}

void DFRobot_Microwave_Radar_Module::setGpioMode(bool voltage)
{
  char comsetGpioMode[18] = {0};
  sprintf(comsetGpioMode, "setGpioMode 1 %d", voltage);
  sendCommand("sensorStop");                              //Stop detection
  sendCommand(comsetGpioMode);                            //Configure interface polarity of output control signal.
  sendCommand("saveConfig");                              //Save configuration
  sendCommand("sensorStart");                             //Start the module to start running.
}
