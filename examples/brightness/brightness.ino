#include <VFD_13-ST-84GINK.h>

const int rst = 2, cs = 3, scl = 4, sda = 5;
VFD vfd(rst,cs,scl,sda);

void setup() {
    // 初始化VFD控制器
    vfd.begin();
}

void loop() {
    // VFD亮度增加
    for(int i = 0; i <= 255; i++) {
        vfd.set_brightness(i);
        vfd.clear();
        // 显示亮度值
        vfd.print("brig=");
        vfd.print(i);
        delay(10);
    }
    // VFD亮度降低
    for(int i = 255; i > 0; i--) {
        vfd.set_brightness(i);
        vfd.clear();
        // 显示亮度值
        vfd.print("brig=");
        vfd.print(i);
        delay(10);
    }
}