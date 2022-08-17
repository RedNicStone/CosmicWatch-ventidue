//
// Created by nic on 07/08/22.
//

#ifndef __unix_
#ifndef GRAPHICS_OLED_1_5INCH_128X128_H
#define GRAPHICS_OLED_1_5INCH_128X128_H

#include <SPI.h>
#include <vector>
#include <cstdint>

#include "../renderer/stream_converters.h"
#include "../types.h"


#define OLED_CS 10
#define OLED_CS_0     digitalWrite(OLED_CS, LOW)
#define OLED_CS_1     digitalWrite(OLED_CS, HIGH)

#define OLED_RST 7
#define OLED_RST_0    digitalWrite(OLED_RST, LOW)
#define OLED_RST_1    digitalWrite(OLED_RST, HIGH)

#define OLED_DC 6
#define OLED_DC_0     digitalWrite(OLED_DC, LOW)
#define OLED_DC_1     digitalWrite(OLED_DC, HIGH)

#define OLED_1in5_RGB_WIDTH  128 //OLED width
#define OLED_1in5_RGB_HEIGHT 128 //OLED height


class OLED_1inch5_128 {
  private:
    static void System_Init() {
        pinMode(OLED_CS, OUTPUT);
        pinMode(OLED_RST, OUTPUT);
        pinMode(OLED_DC, OUTPUT);

        //SPI.setDataMode(SPI_MODE3);
        //SPI.setBitOrder(MSBFIRST);
        //SPI.setClockDivider(SPI_CLOCK_DIV2);
        SPI.begin();
        SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE3));
    }

    static void SPI4W_Write_Byte(uint8_t DATA) {
        SPI.transfer(DATA);
    }

    static void Driver_Delay_ms(unsigned long xms) {
        delay(xms);
    }

    static void OLED_Reset() {
        OLED_RST_1;
        Driver_Delay_ms(100);
        OLED_RST_0;
        Driver_Delay_ms(100);
        OLED_RST_1;
        Driver_Delay_ms(100);
    }

    static void OLED_WriteReg(uint8_t Reg) {
        OLED_DC_0;
        OLED_CS_0;
        SPI4W_Write_Byte(Reg);
        OLED_CS_1;
    }

    static void OLED_WriteData(uint8_t Data) {
        OLED_DC_1;
        OLED_CS_0;
        SPI4W_Write_Byte(Data);
        OLED_CS_1;
    }


    static void OLED_InitReg() {
        OLED_WriteReg(0xfd);  // command lock
        OLED_WriteData(0x12);
        OLED_WriteReg(0xfd);  // command lock
        OLED_WriteData(0xB1);

        OLED_WriteReg(0xae);  // display off
        OLED_WriteReg(0xa4);  // Normal Display mode

        OLED_WriteReg(0x15);  //set column address
        OLED_WriteData(0x00);     //column address start 00
        OLED_WriteData(0x7f);     //column address end 127
        OLED_WriteReg(0x75);  //set row address
        OLED_WriteData(0x00);     //row address start 00
        OLED_WriteData(0x7f);     //row address end 127

        OLED_WriteReg(0xB3);
        OLED_WriteData(0xF1);

        OLED_WriteReg(0xCA);
        OLED_WriteData(0x7F);

        OLED_WriteReg(0xa0);  //set re-map & data format
        OLED_WriteData(0x74);     //Horizontal address increment

        OLED_WriteReg(0xa1);  //set display start line
        OLED_WriteData(0x00);     //start 00 line

        OLED_WriteReg(0xa2);  //set display offset
        OLED_WriteData(0x00);

        OLED_WriteReg(0xAB);
        OLED_WriteReg(0x01);

        OLED_WriteReg(0xB4);
        OLED_WriteData(0xA0);
        OLED_WriteData(0xB5);
        OLED_WriteData(0x55);

        OLED_WriteReg(0xC1);
        OLED_WriteData(0xC8);
        OLED_WriteData(0x80);
        OLED_WriteData(0xC0);

        OLED_WriteReg(0xC7);
        OLED_WriteData(0x0F);

        OLED_WriteReg(0xB1);
        OLED_WriteData(0x32);

        OLED_WriteReg(0xB2);
        OLED_WriteData(0xA4);
        OLED_WriteData(0x00);
        OLED_WriteData(0x00);

        OLED_WriteReg(0xBB);
        OLED_WriteData(0x17);

        OLED_WriteReg(0xB6);
        OLED_WriteData(0x01);

        OLED_WriteReg(0xBE);
        OLED_WriteData(0x05);

        OLED_WriteReg(0xA6);
    }

    static RGB565 dmaBuffer[OLED_1in5_RGB_HEIGHT * OLED_1in5_RGB_WIDTH] __attribute__((aligned(32))) DMAMEM;

  public:
    OLED_1inch5_128() = default;

    explicit OLED_1inch5_128(int) {
        init();
    }

    void init() {
        System_Init();

        //Hardware reset
        OLED_Reset();

        //Set the initialization register
        OLED_InitReg();
        Driver_Delay_ms(200);

        //Turn on the OLED display
        OLED_WriteReg(0xAF);
    }

    void clear() {
        uint32_t i;

        OLED_WriteReg(0x15);
        OLED_WriteData(0);
        OLED_WriteData(127);
        OLED_WriteReg(0x75);
        OLED_WriteData(0);
        OLED_WriteData(127);
        // fill!
        OLED_WriteReg(0x5C);

        for(i=0; i<OLED_1in5_RGB_WIDTH*OLED_1in5_RGB_HEIGHT*2; i++){
            OLED_WriteData(0x00);
        }
    }

    template<StreamSignature<RGB565> Source>
    void bake(Source src);

    void transfer() {
        OLED_WriteReg(0x15);
        OLED_WriteData(0);
        OLED_WriteData(127);
        OLED_WriteReg(0x75);
        OLED_WriteData(0);
        OLED_WriteData(127);
        // fill!
        OLED_WriteReg(0x5C);

        OLED_DC_1;
        OLED_CS_0;
        SPI.transfer((void*) dmaBuffer, nullptr, OLED_1in5_RGB_WIDTH * OLED_1in5_RGB_HEIGHT * 2);
        OLED_CS_1;
    };
};

RGB565 OLED_1inch5_128::dmaBuffer[OLED_1in5_RGB_WIDTH * OLED_1in5_RGB_HEIGHT];

template<StreamSignature<RGB565> Source>
void OLED_1inch5_128::bake(Source src) {
    for(uint32_t x = 0; x < OLED_1in5_RGB_WIDTH; x++) {
        for(uint32_t y = 0; y < OLED_1in5_RGB_HEIGHT; y++) {
            dmaBuffer[x + y * OLED_1in5_RGB_WIDTH] = src.operator() ( {x, y} );
        }
    }
}

#endif //GRAPHICS_OLED_1_5INCH_128X128_H
#endif
