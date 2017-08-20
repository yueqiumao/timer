/*
    月球猫的小闹钟
    2788808483
    u2nn@qq.com

    引脚对应关系
    arduino    hpdl1414 
    0-6        data0-data6    7位ascii码
    7-8        a1, a2         2位LED地址，就是当前操作哪个LED，从最右边开始。
    9          WR
*/

#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "user_interface.h"
#include "eagle_soc.h"

long timestamp = 0;
os_timer_t keyTimer;
bool pressed = false;
int cycleTime = 30l * 60 * 1000;
int restTime = 5l * 60 * 1000; // 一次定时周期为30分钟，最后5分钟为休息时间，闪动显示。

void drawChar(int pos, char ch) {
    digitalWrite(10, HIGH);
    delay(1);

    digitalWrite(12, (pos&1) ? HIGH : LOW );
    digitalWrite(13, (pos&2) ? HIGH : LOW);
    delay(1);

    digitalWrite(0, (ch&(1<<0) ? HIGH : LOW ));
    digitalWrite(1, (ch&(1<<1) ? HIGH : LOW ));
    digitalWrite(2, (ch&(1<<2) ? HIGH : LOW ));
    digitalWrite(3, (ch&(1<<3) ? HIGH : LOW ));
    digitalWrite(4, (ch&(1<<4) ? HIGH : LOW ));
    digitalWrite(5, (ch&(1<<5) ? HIGH : LOW ));
    digitalWrite(15, (ch&(1<<6) ? HIGH : LOW ));
    delay(1);

    digitalWrite(10, LOW );
    delay(1);

    digitalWrite(10, HIGH);
    delay(1);
}

void flashScreenOnce() {
    for (int i = 0; i < 4; ++i) {
        drawChar(i, '*');    
    }
    delay(500);
    for (int i = 0; i < 4; ++i) {
        drawChar(i, ' ');    
    }
    delay(500);
}

void intrKeyPress() {
    if (!pressed) {
        pressed = true;
        os_timer_disarm(&keyTimer);
        os_timer_setfn(&keyTimer, (os_timer_func_t*)pressHandler, NULL);
        os_timer_arm(&keyTimer, 50, 0);
    }
}

void pressHandler() {
    pressed = false;
    if (digitalRead(14) == LOW) {
        resetTimer();
    }
}

void resetTimer() {
    timestamp = millis() + cycleTime;
}

void setup() {
    pinMode(0, OUTPUT); // 7bit
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(15, OUTPUT);

    pinMode(12, OUTPUT); //addr
    pinMode(13, OUTPUT);

    pinMode(10, OUTPUT); //wr

    pinMode(14, INPUT_PULLUP);
    attachInterrupt(14, intrKeyPress, FALLING);

    resetTimer();
    // Serial.begin(74880);
}

void loop() {
    if (millis() < timestamp) {
        long interval = (timestamp - millis());
        bool rest;
        interval -= restTime;
        rest = interval < 0;
        interval = abs(interval);
        interval /= 1000;

        int minute = interval / 60;
        int second = interval % 60;

        // Serial.printf("%d %d\n", (second / 10 % 10), (second % 10));

        drawChar(3, '0' + (minute / 10 % 10));
        drawChar(2, '0' + (minute % 10));
        drawChar(1, '0' + (second / 10 % 10));
        drawChar(0, '0' + (second % 10));


        if (rest) {
            delay(500);
            drawChar(3, ' ');
            drawChar(2, ' ');
            drawChar(1, ' ');
            drawChar(0, ' ');
            delay(500);
        }

    } else {
        flashScreenOnce();
    }
}
