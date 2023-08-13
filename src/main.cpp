#include <Arduino.h>
#include "graphics.h"

void setup()
{
    delay(1500);
    Serial.begin(115200);
    Serial.printf("\n\nSerial initiated!!\n\n");
}

void loop()
{

    static int32_t x_pos = 127;
    static int32_t y_pos = 127;

    if (Serial.available() > 0)
    {
        char received_char = Serial.read();
        clear_screen();

        int32_t box_speed = 5;

        if (received_char == 'D' || received_char == 'd') x_pos += box_speed;     // Right
        if (received_char == 'A' || received_char == 'a') x_pos -= box_speed;     // Left
        if (received_char == 'W' || received_char == 'w') y_pos += box_speed;     // Up
        if (received_char == 'S' || received_char == 's') y_pos -= box_speed;     // Down
        
        if (x_pos < 0)   x_pos = 255;
        if (x_pos > 255) x_pos = 0;
        if (y_pos < 0)   y_pos = 255;
        if (y_pos > 255) y_pos = 0;

        draw_center_rectangle(20,20,x_pos,y_pos);
    }

    graphics_update();
}
