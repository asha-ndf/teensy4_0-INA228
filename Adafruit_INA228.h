/*!
 *  @file Adafruit_INA228.h
 *
 * 	I2C Driver for INA228 Current and Power sensor
 *
 * 	This is a library for the Adafruit INA228 breakout:
 * 	http://www.adafruit.com/products/xxxx
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_INA228_H
#define _ADAFRUIT_INA228_H

#include "Arduino.h"
#include "Adafruit_I2CDevice.h"
#include "Adafruit_I2CRegister.h"
#include <Wire.h>

#define INA228_I2CADDR_DEFAULT 0x40 ///< INA228 default i2c address
#define INA228_REG_CONFIG 0x00      ///< Configuration register
#define INA228_REG_ADCCFG 0x01
#define INA228_REG_SHUNTCAL 0x02
#define INA228_REG_SHUNTTEMPCO 0x03
#define INA228_REG_VSHUNT 0x04
#define INA228_REG_VBUS 0x05
#define INA228_REG_DIETEMP 0x06
#define INA228_REG_CURRENT 0x07
#define INA228_REG_POWER 0x08
#define INA228_REG_ENERGY 0x09
#define INA228_REG_CHARGE 0x0A
#define INA228_REG_DIAGALRT 0x0B
#define INA228_REG_SOVL 0x0C
#define INA228_REG_SUVL 0x0D
#define INA228_REG_BOVL 0x0E
#define INA228_REG_BUVL 0x0F
#define INA228_REG_TEMPLIMIT 0x10
#define INA228_REG_PWRLIMIT 0x10
#define INA228_REG_MFG_UID 0x3E ///< Manufacturer ID Register
#define INA228_REG_DVC_UID 0x3F ///< Device ID and Revision Register

/**
 * @brief Mode options.
 *
 * Allowed values for setMode.
 */
typedef enum _mode {
  INA228_MODE_SHUTDOWN = 0x00, /**< SHUTDOWN: Minimize quiescient current and
                                turn off current into the device inputs. Set
                                another mode to exit shutown mode **/
  INA228_MODE_TRIGGERED =
      0x07,                      /**< TRIGGERED: Trigger a one-shot measurement
                                   of temp, current and bus voltage. Set the TRIGGERED
                                   mode again to take a new measurement **/
  INA228_MODE_CONTINUOUS = 0x0F, /**< CONTINUOUS: (Default) Continuously update
                                    the temp, current, bus voltage and power
                                    registers with new measurements **/
} INA228_MeasurementMode;

/**
 * @brief Conversion Time options.
 *
 * Allowed values for setCurrentConversionTime and setVoltageConversionTime.
 */
typedef enum _conversion_time {
  INA228_TIME_50_us,   ///< Measurement time: 50us
  INA228_TIME_84_us,   ///< Measurement time: 84us
  INA228_TIME_150_us,  ///< Measurement time: 150us
  INA228_TIME_280_us,  ///< Measurement time: 280us
  INA228_TIME_540_us,  ///< Measurement time: 540us
  INA228_TIME_1052_us, ///< Measurement time: 1052us
  INA228_TIME_2074_us, ///< Measurement time: 2074us
  INA228_TIME_4120_us, ///< Measurement time: 4120us
} INA228_ConversionTime;

/**
 * @brief Averaging Count options.
 *
 * Allowed values forsetAveragingCount.
 */
typedef enum _count {
  INA228_COUNT_1,    ///< Window size: 1 sample (Default)
  INA228_COUNT_4,    ///< Window size: 4 samples
  INA228_COUNT_16,   ///< Window size: 16 samples
  INA228_COUNT_64,   ///< Window size: 64 samples
  INA228_COUNT_128,  ///< Window size: 128 samples
  INA228_COUNT_256,  ///< Window size: 256 samples
  INA228_COUNT_512,  ///< Window size: 512 samples
  INA228_COUNT_1024, ///< Window size: 1024 samples
} INA228_AveragingCount;

/**
 * @brief Alert trigger options.
 *
 * Allowed values for setAlertType.
 */
typedef enum _alert_type {
  INA228_ALERT_CONVERSION_READY = 0x1, ///< Trigger on conversion ready
  INA228_ALERT_OVERPOWER = 0x2,        ///< Trigger on power over limit
  INA228_ALERT_UNDERVOLTAGE = 0x4,     ///< Trigger on bus voltage under limit
  INA228_ALERT_OVERVOLTAGE = 0x8,      ///< Trigger on bus voltage over limit
  INA228_ALERT_UNDERCURRENT = 0x10,    ///< Trigger on current under limit
  INA228_ALERT_OVERCURRENT = 0x20,     ///< Trigger on current over limit
  INA228_ALERT_NONE = 0x0,             ///< Do not trigger alert pin (Default)
} INA228_AlertType;

/**
 * @brief Alert pin polarity options.
 *
 * Allowed values for setAlertPolarity.
 */
typedef enum _alert_polarity {
  INA228_ALERT_POLARITY_NORMAL = 0x0, ///< Active high open-collector (Default)
  INA228_ALERT_POLARITY_INVERTED = 0x1, ///< Active low open-collector
} INA228_AlertPolarity;

/**
 * @brief Alert pin latch options.
 *
 * Allowed values for setAlertLatch.
 */
typedef enum _alert_latch {
  INA228_ALERT_LATCH_ENABLED = 0x1,     /**< Alert will latch until Mask/Enable
                                           register is read **/
  INA228_ALERT_LATCH_TRANSPARENT = 0x0, /**< Alert will reset when fault is
                                           cleared **/
} INA228_AlertLatch;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            INA228 Current and Power Sensor
 */
class Adafruit_INA228 {
public:
  Adafruit_INA228();
  bool begin(uint8_t i2c_addr = INA228_I2CADDR_DEFAULT,
             TwoWire *theWire = &Wire);
  void reset(void);

  void setShunt(float shunt_res = 0.1, float max_current = 3.2);
  float readDieTemp(void);

  float readCurrent(void);
  float readBusVoltage(void);
  float readShuntVoltage(void);
  float readPower(void);
  float readEnergy(void);

  void setMode(INA228_MeasurementMode mode);
  INA228_MeasurementMode getMode(void);

  bool conversionReady(void);
  uint16_t alertFunctionFlags(void);

  float getAlertLimit(void);
  void setAlertLimit(float limit);
  INA228_AlertLatch getAlertLatch(void);
  void setAlertLatch(INA228_AlertLatch state);
  INA228_AlertPolarity getAlertPolarity(void);
  void setAlertPolarity(INA228_AlertPolarity polarity);
  INA228_AlertType getAlertType(void);
  void setAlertType(INA228_AlertType alert);

  INA228_ConversionTime getCurrentConversionTime(void);
  void setCurrentConversionTime(INA228_ConversionTime time);
  INA228_ConversionTime getVoltageConversionTime(void);
  void setVoltageConversionTime(INA228_ConversionTime time);
  INA228_AveragingCount getAveragingCount(void);
  void setAveragingCount(INA228_AveragingCount count);

  Adafruit_I2CRegister *Config, ///< BusIO Register for Config
      *ADC_Config,              ///< BusIO Register for Config
      *Diag_Alert,              ///< BusIO Register for MaskEnable
      *AlertLimit;              ///< BusIO Register for AlertLimit

private:
  float _current_lsb;
  Adafruit_I2CDevice *i2c_dev;
};

#endif
