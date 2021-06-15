# VFD_13-ST-84GINK

VFD模组13-ST-84GINK Arduino 驱动库

MCU与VFD模组通过软件SPI进行通讯

## Usage

构造对象：

```c++
VFD::VFD(uint8_t RSTpin/*复位引脚*/,uint8_t CSpin/*片选引脚*/,uint8_t SCLpin/*SPI时钟*/,uint8_t SDApin/*SPI数据*/);
```

初始化：

```c++
void VFD::begin();
```

写一个字符：

```c++
size_t VFD::write(uint8_t chr);
```

写字符串或数字（继承了内建class Print）：

```c++
void VFD::print(...);
```

设置DRAM偏移量：

```c++
void VFD::set_offset(int offset);
```

软件清屏：

```c++
void VFD::clear();
```

写用户字符到CGRAM：

```c++
void VFD::write_CGRAM(uint8_t addr,uint8_t *val);
```

设置亮度：

```c++
void VFD::set_brightness(uint8_t val);
```

开启显示：

```c++
void VFD::on();
```

关闭显示：

```c++
void VFD::off();
```

设置ICON开关：

```c++
void VFD::set_ICON(uint8_t id,bool on);
```

## DEMO

[Datasheet](docs/datasheet)

[DEMO Schenatic](docs/VFD_13ST84GINK.SchDoc)

Testing：

![IMG_20210615_232715](images/IMG_20210615_232715.jpg)

