# DFRobot_Microwave_Radar_Module

- This is a 5.8G Hz millimeter wave human presence detection radar module with high sensitivity. Different from the traditional way of judging whether people exist only by detecting large movements of the human body, this module can judge whether people exist by detecting tiny movements such as human breathing with high sensitivity. Therefore, no matter whether the human body is sitting still, sleeping and so on, it can accurately perceive the existence of people. The sensing results can be output through serial port or high-low level output through I/O port, and the sensor module has the characteristics of strong sensing reliability, high sensitivity, small size, simple use, strong anti-interference and easy integration. It can be widely used in lighting, security, home, household appliances, hotels, garages, buildings, traffic and other industries that need to detect human micro-motion.

## Table of Contents

* [Installation](#installation)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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
```

## Compatibility

| MCU           | Work Well | Work Wrong | Untested | Remarks |
| ------------- | :-------: | :--------: | :------: | ------- |
| Arduino uno   |     √     |            |          |         |
| Mega2560      |     √     |            |          |         |
| Leonardo      |           |            |      √   |         |
| ATTiny84 |     √     |            |          |         |
| ESP32         |     √     |            |          |         |
|               |           |            |          |         |


## History

- data 2022-05-7
- version V1.0


## Credits

Written by huyujie(yujie.hu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))

# DFRobot_mmWave_Radar
