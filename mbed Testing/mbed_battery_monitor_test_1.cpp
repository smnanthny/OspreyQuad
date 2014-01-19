/*
    OspreyQuad Project
    ~~~~~~~~~~~~~~~~~~~~~~~~
    Title: Battery Monitor Test 1
    Author: Simon Anthony
    Created: 19/01/2014
*/

#include "mbed.h"

// Analog inputs - cells 1 to 3
AnalogIn ain1(p18);
AnalogIn ain2(p19);
AnalogIn ain3(p20);

// PC debug port
Serial pc(USBTX, USBRX);

int main()
{
    // Cell values
    float c1;
    float c2;
    float c3;
    
    while(1)
    {
        // Convert normalised reading back into volts
        // (AnalogIn x 3.3V) x (R1 + R2) - Previous Cell(s)
        c1 = (ain1.read()*3.3)*2;
        c2 = ((ain2.read()*3.3)*4.3)-c1;
        c3 = ((ain3.read()*3.3)*6.6)-(c1+c2);

        pc.printf("Cell 1 = %f\n", c1);
        pc.printf("Cell 2 = %f\n", c2);
        pc.printf("Cell 3 = %f\n", c3);
        pc.printf("---------------------------\n\n");
        
        wait(1);
    }
}