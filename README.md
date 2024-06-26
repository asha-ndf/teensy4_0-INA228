# teensy4_0-INA228  
[![Teensy Compile Check](https://github.com/asha-ndf/teensy4_0-INA228/actions/workflows/compile.yml/badge.svg)](https://github.com/asha-ndf/teensy4_0-INA228/actions/workflows/compile.yml)  

* INA228をTeensy4.0で使用するプログラム

## 参考資料

* [INA228 モジュール データシート](https://www.strawberry-linux.com/pub/ina228-manual.pdf)
* [INA228 IC データシート](https://www.ti.com/jp/lit/ds/symlink/ina228.pdf)

## 出力データ例

* [デバッグモード](./data/debug-ture.txt)
* [ノーマルモード](./data/debug-false.txt)

## 使用しているライブラリ

* [Adafruit_INA228](https://github.com/adafruit/Adafruit_INA228) (三条項BSDライセンス)
  * [Adafruit_INA228.cpp](./Adafruit_INA228.cpp)
  * [Adafruit_INA228.h](./Adafruit_INA228.h)
* [Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO) (MITライセンス)
  * [Adafruit_BusIO_Register.cpp](./Adafruit_BusIO_Register.cpp)
  * [Adafruit_BusIO_Register.h](./Adafruit_BusIO_Register.h)
  * [Adafruit_I2CDevice.cpp](./Adafruit_I2CDevice.cpp)
  * [Adafruit_I2CDevice.h](./Adafruit_I2CDevice.h)
  * [Adafruit_I2CRegister.h](./Adafruit_I2CRegister.h)
