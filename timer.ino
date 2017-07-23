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

long timestamp = 0;

void drawChar(int pos, char ch) {
    digitalWrite(14, HIGH);
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

    digitalWrite(14, LOW );
    delay(1);

    digitalWrite(14, HIGH);
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

void setup() {
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);

    timestamp = millis() + 25l*60*1000;
}

void loop() {
    if (timestamp >= millis()) {
        long interval = (timestamp - millis()) / 1000;
        int minute = interval / 60;
        int second = interval % 60;

        drawChar(3, '0' + (minute / 10 % 10));
        drawChar(2, '0' + (minute % 10));
        drawChar(1, '0' + (second / 10 % 10));
        drawChar(0, '0' + (second % 10));
    } else {
        flashScreenOnce();
    }
}
