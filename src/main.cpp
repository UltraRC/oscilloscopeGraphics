#include <Arduino.h>
#include "graphics.h"

void setup()
{
    Serial.begin(115200);
}
typedef enum
{
    up,
    down,
    left,
    right
} state_t;

int32_t x      = 0;
int32_t y      = 0;
uint32_t count  = 127;
state_t state = up;


int max_size = 255;
int min_size = 0;

int increment = 5;

int32_t delay_time = 20000;

bool sheesh = 0;

void loop()
{
    // Write to the screen
    dacWrite(X_PIN, x);
    dacWrite(Y_PIN, y);

    // Update the x/y values
    switch (state)
    {
    case up:
        y+=increment;
        if (y >= max_size)
        {
            y = max_size;
            state = right;
        }
        break;
        
    case right:
        x+=increment;
        if (x >= max_size)
        {
            x = max_size;
            state = down;
        }
        break;

    case down:
        y-=increment;
        if (y <= min_size)
        {
            y = min_size;
            state = left;
        }
        break;
    
    case left:
        x-=increment;
        if (x <= min_size)
        {
            x = min_size;
            state = up;
        }
        break;
    
    default:
        break;
    }

    // delay(20);

}


// void setup()
// {
//     delay(1500);
//     Serial.begin(115200);
//     Serial.printf("\n\nSerial initiated!!\n\n");
// }


// void loop()
// {
//     update_graphics();

//     static uint64_t last_move = 0;
//     if(millis()-last_move > 1000)
//     {
//         last_move = millis();
//         clear_screen();
//         // draw_line(0,0,127,127);
//         draw_line(250,250,0,0);
//     }

// }
