#include <Arduino.h>
#include "graphics.h"

int32_t x_offset = 0;

shape_t square0 = {{{0,0},{0,255},{255,255},{255,0},{0,0}}, 5};
shape_t square1 = {{{10,10},{10,245},{245,245},{245,10},{10,10}}, 5};
shape_t square2 = {{{20,20},{20,235},{235,235},{235,20},{20,20}}, 5};
shape_t square3 = {{{30,30},{30,225},{225,225},{225,30},{30,30}}, 5};
shape_t square4 = {{{40,40},{40,215},{215,215},{215,40},{40,40}}, 5};
shape_t square5 = {{{50,50},{50,205},{205,205},{205,50},{50,50}}, 5};
shape_t square6 = {{{60,60},{60,195},{195,195},{195,60},{60,60}}, 5};
shape_t square7 = {{{70,70},{70,185},{185,185},{185,70},{70,70}}, 5};
shape_t square8 = {{{80,80},{80,175},{175,175},{175,80},{80,80}}, 5};
shape_t square9 = {{{90,90},{90,165},{165,165},{165,90},{90,90}}, 5};
shape_t square10 = {{{100,100},{100,155},{155,155},{155,100},{100,100}}, 5};
shape_t square11 = {{{110,110},{110,145},{145,145},{145,110},{110,110}}, 5};
shape_t square12 = {{{120,120},{120,135},{135,135},{135,120},{120,120}}, 5};
shape_t square13 = {{{125,125},{125,130},{130,130},{130,125},{125,125}}, 5};

// shape_t big_triangle = {{{10,10},{10,200},{160,95},{10,10}}, 4};
// shape_t small_triangle = {{{50,50},{180,70},{100,25},{50,50}},4};

void setup()
{
    delay(1500);
    Serial.begin(115200);
    Serial.printf("\n\nSerial initiated!!\n\n");
    add_shape(&square0);
}


void loop()
{
    update_graphics();

    static uint64_t last_move = 0;
    if(millis()-last_move > 50)
    {
        last_move = millis();
        clear_shapes();
        static int32_t shape_num = 0;
        shape_t* new_shape;

        if(shape_num == 0)  new_shape = &square0;
        if(shape_num == 1)  new_shape = &square1;
        if(shape_num == 2)  new_shape = &square2;
        if(shape_num == 3)  new_shape = &square3;
        if(shape_num == 4)  new_shape = &square4;
        if(shape_num == 5)  new_shape = &square5;
        if(shape_num == 6)  new_shape = &square6;
        if(shape_num == 7)  new_shape = &square7;
        if(shape_num == 8)  new_shape = &square8;
        if(shape_num == 9)  new_shape = &square9;
        if(shape_num == 10)  new_shape = &square10;
        if(shape_num == 11)  new_shape = &square11;
        if(shape_num == 12)  new_shape = &square12;
        if(shape_num == 13)  new_shape = &square13;


        shape_num++;
        if(shape_num > 13)   shape_num = 0;
        add_shape(new_shape);
    }

}
