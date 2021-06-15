#include <Arduino.h>
#include "VFD_13-ST-84GINK.h"

VFD::VFD(uint8_t RSTpin,uint8_t CSpin,uint8_t SCLpin,uint8_t SDApin) {
    _SDApin = SDApin;
    _SCLpin = SCLpin;
    _CSpin = CSpin;
    _RSTpin = RSTpin;
    pinMode(_SDApin,OUTPUT);
    pinMode(_SCLpin,OUTPUT);
    pinMode(_CSpin,OUTPUT);
    pinMode(_RSTpin,OUTPUT);
    digitalWrite(_CSpin,HIGH);
    digitalWrite(_RSTpin,HIGH);
}

// 初始化VFD控制器
void VFD::begin() {
    // 硬复位VFD
    digitalWrite(_RSTpin,LOW);
    delay(10);
    digitalWrite(_RSTpin,HIGH);

    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_TIMING);
    this->write_data(0x0D);
    digitalWrite(_CSpin,HIGH);

    this->set_brightness(255);
    this->on();
}

// 写一个字节
void VFD::write_data(uint8_t dat) {
    shiftOut(_SDApin,_SCLpin,LSBFIRST,dat); // 软件SPI 小端
}

// 写一个字符
size_t VFD::write(uint8_t chr) {
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_WRITE_DRAM | DDRAM_ptr++); // 自增指针
    this->write_data(chr);
    digitalWrite(_CSpin,HIGH);
    return 1;
}

// 设置DDRAM偏移量
void VFD::set_offset(int offset) {
    this->DDRAM_ptr = min(max(offset,DDRAM_OFFSET_MIN),DDRAM_OFFSET_MAX);
}

// 软件清屏
void VFD::clear() {
    this->set_offset(1);
    this->print("            ");
    this->set_offset(1);
}

// 写用户字符到CGRAM
void VFD::write_CGRAM(uint8_t addr,uint8_t *val) {
    addr = min(addr,CGRAM_MAX);
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_WRITE_CGRAM | addr);
    for(int i=0; i<5; i++)
        this->write_data(*val++);
    digitalWrite(_CSpin,HIGH);
}

// 写0段图标(使用CGRAM 7)
void VFD::write_G0ICON() {
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_WRITE_CGRAM | 0x07);
    for(int i=0; i<5; i++)
        this->write_data(ICON1[i]);
    digitalWrite(_CSpin,HIGH);

    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_WRITE_DRAM | 0x00);
    this->write_data(0x07);
    digitalWrite(_CSpin,HIGH);
}

// 写ADRAM
void VFD::write_ADRAM(uint8_t addr,uint8_t val)
{
    addr = min(max(addr,ICONRAM_MIX),ICONRAM_MAX);
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_WRITE_ADRAM | (addr+1));
    this->write_data(val);
    digitalWrite(_CSpin,HIGH);
}

// 设置亮度
void VFD::set_brightness(uint8_t val) {
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_BRIGHTNESS);
    this->write_data(val);
    digitalWrite(_CSpin,HIGH);
}

// 开启显示
void VFD::on() {
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_ON_OFF | 0x00);
    digitalWrite(_CSpin,HIGH);
}

// 关闭显示
void VFD::off() {
    digitalWrite(_CSpin,LOW);
    this->write_data(VFD_ON_OFF | 0x02);
    digitalWrite(_CSpin,HIGH);
}

// 设置ICON开关
void VFD::set_ICON(uint8_t id,bool on) {
    if(id <= ICON_480_P) {
        if(on)
			ICON1[id % 5] |= (uint8_t)0x01 << (id / 5);
		else
			ICON1[id % 5] &=~ (uint8_t)(0x01 << (id / 5));
        this->write_G0ICON();
    } else if(id <= ICON_LOOP) {
        id -= ICON_TIME;
        if(on)
            ICON2[id] |= 0x02;
        else
            ICON2[id] &= ~0x02;
        this->write_ADRAM(id,ICON2[id]);
    } else if(id <= ICON_COLON3) {
        id = (id-ICON_COLON1)*2+ICON_LOCK-ICON_TIME;
        if(on) {
            ICON2[id] |= 0x01;
            ICON2[id+1] |= 0x01;
        } else {
            ICON2[id] &= ~0x01;
            ICON2[id+1] &= ~0x01;
        }
        this->write_ADRAM(id,ICON2[id]);
        this->write_ADRAM(id+1,ICON2[id+1]);
    }
}

