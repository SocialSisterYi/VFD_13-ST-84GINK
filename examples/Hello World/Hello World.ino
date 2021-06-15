#include <VFD_13-ST-84GINK.h>

const int rst = 2, cs = 3, scl = 4, sda = 5;
VFD vfd(rst,cs,scl,sda);

void setup() {
    // 初始化VFD控制器
    vfd.begin();
    // 在屏幕上打印字符串
    vfd.print("Hello,World!");
}

void loop() {

}