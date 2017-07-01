/*
    月球猫的小闹钟
    u2nn@qq.com
*/
void drawChar(int pos, char ch) {
    digitalWrite(7, HIGH);
    delay(1);

    // 设置地址
    digitalWrite(9, (pos&1) ? HIGH : LOW );
    digitalWrite(8, (pos&2) ? HIGH : LOW);
    delay(1);

    // 开始写入
    digitalWrite(0, LOW );
    delay(1);

    digitalWrite(0, (ch&(1<<0) ? HIGH : LOW ));
    digitalWrite(1, (ch&(1<<1) ? HIGH : LOW ));
    digitalWrite(2, (ch&(1<<2) ? HIGH : LOW ));
    digitalWrite(3, (ch&(1<<3) ? HIGH : LOW ));
    digitalWrite(4, (ch&(1<<4) ? HIGH : LOW ));
    digitalWrite(5, (ch&(1<<5) ? HIGH : LOW ));
    digitalWrite(6, (ch&(1<<6) ? HIGH : LOW ));
    delay(1);

    // 写入完成
    digitalWrite(7, HIGH);
    delay(1);
}

void setup() {

}

void loop() {

}
