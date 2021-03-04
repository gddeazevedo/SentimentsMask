#include "LedMatrix.h"
#include <math.h>


LedMatrix::LedMatrix(int dataIn, int load, int clock) {
	this->pins = {
        .dataIn = dataIn,
        .load = load,
        .clock = clock
    };

    this->maxInUse = 1;
}


LedMatrix::LedMatrix(int dataIn, int load, int clock, int maxInUse) {
    this->pins = {
        .dataIn = dataIn,
        .load = load,
        .clock = clock
    };

    this->maxInUse = maxInUse;
}


void LedMatrix::putByte(byte data) {
    byte mask;

    for (byte i = 8; i > 0; i--) {
        mask = 0x01 << (i - 1);
        digitalWrite(this->pins.clock, LOW);

        if (data & mask) {
            digitalWrite(this->pins.dataIn, HIGH);
        } else {
            digitalWrite(this->pins.dataIn, LOW);
        }

        digitalWrite(this->pins.clock, HIGH);
    }
}


int LedMatrix::binaryToDecimal(int binaryNumber) {
    int aux = binaryNumber;
    int binaryNumberLen = 0;
    int decimalNumber = 0;

    while (aux != 0) {
        binaryNumberLen++;
        aux /= 10;
    }

    aux = binaryNumber;

    for (int i = 0; i < binaryNumberLen; i++) {
        decimalNumber += (aux % 10) * pow(2, i);
        aux /= 10;
    }

    return decimalNumber;
}


void LedMatrix::maxSingle(byte reg, byte col) {
    digitalWrite(this->pins.load, LOW);
    this->putByte(reg);
    this->putByte(col);
    digitalWrite(this->pins.load, LOW);
    digitalWrite(this->pins.load, HIGH);
}


void LedMatrix::maxAll(byte reg, byte col) {
    digitalWrite(this->pins.load, LOW);

    for (int i = 0; i < maxInUse; i++) {
        this->putByte(reg);
        this->putByte(col);
    }

    digitalWrite(this->pins.load, LOW);
    digitalWrite(this->pins.load, HIGH);
}


void LedMatrix::maxOne(byte maxNr, byte reg, byte col) {
    digitalWrite(this->pins.load, LOW);

    for (int i = this->maxInUse; i > maxNr; i--) {
        this->putByte(0);
        this->putByte(0);
    }

    this->putByte(reg);
    this->putByte(col);

    for (int i = maxNr - 1; i > 0; i--) {
        this->putByte(0);
        this->putByte(0);
    }

    digitalWrite(this->pins.load, LOW);
    digitalWrite(this->pins.load, HIGH);
}


void LedMatrix::clear() {
    for (int e = 1; e < 9; e++) {
        this->maxAll(e, 0);
    }
}


void LedMatrix::drawMatrix(byte pointMatrix[8][8]) {
    String str = "";
    int converted_str;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            str += String(pointMatrix[i][j]);
        }
        converted_str = this->binaryToDecimal(str.toInt());
        str = "";
        this->maxSingle(i + 1, converted_str);
    }
}


void LedMatrix::setup() {
    pinMode(this->pins.dataIn, OUTPUT);
    pinMode(this->pins.clock, OUTPUT);
    pinMode(this->pins.load, OUTPUT);
    digitalWrite(2, HIGH);

    //initiation of the max7219
    this->maxAll(max7219_reg_scanLimit, 0x07);
    this->maxAll(max7219_reg_decodeMode, 0x00);
    this->maxAll(max7219_reg_shutdown, 0x01);
    this->maxAll(max7219_reg_displayTest, 0x00);
    this->clear();
    this->maxAll(max7219_reg_intensity, 0x0f & 0x0f);
}