#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>

const byte max7219_reg_noop = 0x00;
const byte max7219_reg_digit0 = 0x01;
const byte max7219_reg_digit1 = 0x02;
const byte max7219_reg_digit2 = 0x03;
const byte max7219_reg_digit3 = 0x04;
const byte max7219_reg_digit4 = 0x05;
const byte max7219_reg_digit5 = 0x06;
const byte max7219_reg_digit6 = 0x07;
const byte max7219_reg_digit7 = 0x08;
const byte max7219_reg_decodeMode = 0x09;
const byte max7219_reg_intensity = 0x0a;
const byte max7219_reg_scanLimit = 0x0b;
const byte max7219_reg_shutdown = 0x0c;
const byte max7219_reg_displayTest = 0x0f;


typedef struct {
    int dataIn;
    int load;
    int clock;
} Pins;


class LedMatrix {
    public:
        LedMatrix(int dataIn, int load, int clock, int maxInUse);
        void maxSingle(byte reg, byte col);
        void maxAll(byte reg, byte col);
        void maxOne(byte maxNr, byte reg, byte col);
        void clear();
        void drawMatrix(byte pointMatrix[8][8]);
        void setup();
        
    private:
        Pins pins;
        int maxInUse;
        void putByte(byte data);
};


int binaryToDecimal(int binaryNumber);


#endif