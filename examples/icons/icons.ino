#include <VFD_13-ST-84GINK.h>

const int rst = 2, cs = 3, scl = 4, sda = 5;
VFD vfd(rst,cs,scl,sda);

void setup() {
    // 初始化VFD控制器
    vfd.begin();
}

void loop() {
    // 按顺序点亮ICON
    for(int i = ICON_POWER; i <= ICON_COLON3; i++) {
        vfd.set_ICON(i,true);
        vfd.clear();
        // 显示ICON id
        vfd.print("ICON_id=");
        vfd.print(i);
        delay(200);
    }
    // 按顺序熄灭ICON
    for(int i = ICON_COLON3; i > ICON_POWER; i--) {
        vfd.set_ICON(i,false);
        vfd.clear();
        // 显示ICON id
        vfd.print("ICON_id=");
        vfd.print(i);
        delay(200);
    }
}