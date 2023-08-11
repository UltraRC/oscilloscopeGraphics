#include <Arduino.h>
#include "graphics.h"

void setup()
{
    delay(1500);
    Serial.begin(115200);
    Serial.printf("\n\nSerial initiated!!\n\n");

    draw_line(10,10,40,250);
    draw_line(40,10,100,250);
    draw_line(70,10,160,250);
    draw_line(100,10,220,250);
    draw_line(130,10,255,250);
    draw_line(160,10,255,250);
}


void loop()
{   

    graphics_update();
    // clear_screen();
}
