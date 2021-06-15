#ifndef VFD_13_ST_84GINK
#define VFD_13_ST_84GINK

#include <Arduino.h>

#define VFD_WRITE_DRAM          0x20 // 写显示RAM
#define VFD_DISPLAY_MODE        0x00 // 
#define VFD_WRITE_CGRAM         0x40 // 写用户字符RAM
#define VFD_WRITE_ADRAM         0x60 // 写图标RAM
#define VFD_WRITE_URAM          0x80 // 
#define VFD_TIMING              0xE0 // 
#define VFD_BRIGHTNESS          0xE4 // 设置亮度
#define VFD_GARY_LEVEL_DATA     0xA0 // 
#define VFD_GARY_LEVEL_ONOFFSET 0xC0 //
#define VFD_ON_OFF              0xE8 // VFD显示开关
#define VFD_STAND_BY            0xEC // 

#define DDRAM_OFFSET_MIN        1
#define DDRAM_OFFSET_MAX        12
#define CGRAM_MAX               6
#define ICONRAM_MIX             0
#define ICONRAM_MAX             11

// ICON_id
#define ICON_POWER  0
#define ICON_SAT    1
#define ICON_REC    2
#define ICON_TVBOX  3
#define ICON_TER    4
#define ICON_TV     5
#define ICON_FILE   6
#define ICON_S1     7
#define ICON_S2     8
#define ICON_S3     9
#define ICON_S4     10
#define ICON_S5     11
#define ICON_S6     12
#define ICON_S7     13  
#define ICON_S8     14
#define ICON_S9     15
#define ICON_S10    16
#define ICON_1080P  17
#define ICON_1080i  18
#define ICON_720P   19
#define ICON_576    20
#define ICON_576_i  21
#define ICON_576_P  22
#define ICON_480    23
#define ICON_480_i  24
#define ICON_480_P  25
#define ICON_TIME   26  // ADRAM部0
#define ICON_SHIFT  27  // ADRAM部1
#define ICON_CLOCK  28  // ADRAM部2
#define ICON_HD     29  // ADRAM部3
#define ICON_USB    30  // ADRAM部4
#define ICON_LOCK   31  // ADRAM部5
#define ICON_DOLBY  32  // ADRAM部6
#define ICON_MUTE   33  // ADRAM部7
#define ICON_TU1    34  // ADRAM部8
#define ICON_TU2    35  // ADRAM部9
#define ICON_MP3    36  // ADRAM部10
#define ICON_LOOP   37  // ADRAM部11
#define ICON_COLON1 38  // ADRAM部12
#define ICON_COLON2 39  // ADRAM部13
#define ICON_COLON3 40  // ADRAM部14

class VFD: public Print
{
    public:
        VFD(uint8_t RSTpin,uint8_t CSpin,uint8_t SCLpin,uint8_t SDApin);
        void begin();
        virtual size_t write(uint8_t chr);
        void set_offset(int offset);
        void clear();
        void write_CGRAM(uint8_t addr,uint8_t *val);
        void set_brightness(uint8_t val);
        void on();
        void off();
        void set_ICON(uint8_t id,bool on);
    protected:
        uint8_t _SDApin,_SCLpin,_CSpin,_RSTpin;
        uint8_t DDRAM_ptr = 1;
        uint8_t ICON1[5] = {0};
        uint8_t ICON2[12] = {0};
        void write_data(uint8_t dat);
        void write_G0ICON();
        void write_ADRAM(uint8_t addr,uint8_t val);
};

#endif