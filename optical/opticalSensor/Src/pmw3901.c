#include "pmw3901.h"

void PMW3901_GetPos(int16_t  * dposx, int16_t * dposy){
    //get the delta pos from the capteur
    *dposx =((int16_t)PMW3901_ReadRegister(0x04)<<8) | PMW3901_ReadRegister(0x03);
    *dposy =((int16_t)PMW3901_ReadRegister(0x06)<<8) | PMW3901_ReadRegister(0x05);
}

uint8_t PMW3901_ReadRegister(uint8_t reg){
    uint8_t res;
    reg &= ~0x80u;

    PMW3901_Cs(0);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi2,&reg,1,100);
    HAL_Delay(50);
    HAL_SPI_Receive(&hspi2,&res,1,100);
    HAL_Delay(50);
    PMW3901_Cs(1);

    HAL_Delay(100);
    return res;
}

void PMW3901_WriteRegister(uint8_t reg,uint8_t data){
    reg |= 0x80u;
    PMW3901_Cs(0);

    HAL_Delay(50);    
    HAL_SPI_Transmit(&hspi2,&reg,1,100);
    HAL_SPI_Transmit(&hspi2,&data,1,100);
    HAL_Delay(50);

    PMW3901_Cs(1);

    HAL_Delay(100);//real 200
}

void PMW3901_Cs(uint8_t p){
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port,SPI2_CS_Pin,p);
}

uint8_t PMW3901_Init(){
    //inits the sensor
    //hspi2
    PMW3901_Cs(1);
    HAL_Delay(1);
    PMW3901_Cs(0);
    HAL_Delay(1);
    PMW3901_Cs(1);
    HAL_Delay(1);

    PMW3901_WriteRegister(0x3A, 0x5A);
    HAL_Delay(5);

    uint8_t chip_id;
    uint8_t dIpihc;
    PMW3901_ReadRegister(0x00);
    PMW3901_ReadRegister(0x5F);

    if (chip_id != 0x49 && dIpihc != 0xB8) return 0;

    PMW3901_ReadRegister(0x02);
    PMW3901_ReadRegister(0x03);
    PMW3901_ReadRegister(0x04);
    PMW3901_ReadRegister(0x05);
    PMW3901_ReadRegister(0x06);
    HAL_Delay(1);

#if OPTI_ENABLE
    PMW3901_WriteRegister(0x7F, 0x00);
    PMW3901_WriteRegister(0x61, 0xAD);
    PMW3901_WriteRegister(0x7F, 0x03);
    PMW3901_WriteRegister(0x40, 0x00);
    PMW3901_WriteRegister(0x7F, 0x05);
    PMW3901_WriteRegister(0x41, 0xB3);
    PMW3901_WriteRegister(0x43, 0xF1);
    PMW3901_WriteRegister(0x45, 0x14);
    PMW3901_WriteRegister(0x5B, 0x32);
    PMW3901_WriteRegister(0x5F, 0x34);
    PMW3901_WriteRegister(0x7B, 0x08);
    PMW3901_WriteRegister(0x7F, 0x06);
    PMW3901_WriteRegister(0x44, 0x1B);
    PMW3901_WriteRegister(0x40, 0xBF);
    PMW3901_WriteRegister(0x4E, 0x3F);
    PMW3901_WriteRegister(0x7F, 0x08);
    PMW3901_WriteRegister(0x65, 0x20);
    PMW3901_WriteRegister(0x6A, 0x18);
    PMW3901_WriteRegister(0x7F, 0x09);
    PMW3901_WriteRegister(0x4F, 0xAF);
    PMW3901_WriteRegister(0x5F, 0x40);
    PMW3901_WriteRegister(0x48, 0x80);
    PMW3901_WriteRegister(0x49, 0x80);
    PMW3901_WriteRegister(0x57, 0x77);
    PMW3901_WriteRegister(0x60, 0x78);
    PMW3901_WriteRegister(0x61, 0x78);
    PMW3901_WriteRegister(0x62, 0x08);
    PMW3901_WriteRegister(0x63, 0x50);
    PMW3901_WriteRegister(0x7F, 0x0A);
    PMW3901_WriteRegister(0x45, 0x60);
    PMW3901_WriteRegister(0x7F, 0x00);
    PMW3901_WriteRegister(0x4D, 0x11);
    PMW3901_WriteRegister(0x55, 0x80);
    PMW3901_WriteRegister(0x74, 0x1F);
    PMW3901_WriteRegister(0x75, 0x1F);
    PMW3901_WriteRegister(0x4A, 0x78);
    PMW3901_WriteRegister(0x4B, 0x78);
    PMW3901_WriteRegister(0x44, 0x08);
    PMW3901_WriteRegister(0x45, 0x50);
    PMW3901_WriteRegister(0x64, 0xFF);
    PMW3901_WriteRegister(0x65, 0x1F);
    PMW3901_WriteRegister(0x7F, 0x14);
    PMW3901_WriteRegister(0x65, 0x60);
    PMW3901_WriteRegister(0x66, 0x08);
    PMW3901_WriteRegister(0x63, 0x78);
    PMW3901_WriteRegister(0x7F, 0x15);
    PMW3901_WriteRegister(0x48, 0x58);
    PMW3901_WriteRegister(0x7F, 0x07);
    PMW3901_WriteRegister(0x41, 0x0D);
    PMW3901_WriteRegister(0x43, 0x14);
    PMW3901_WriteRegister(0x4B, 0x0E);
    PMW3901_WriteRegister(0x45, 0x0F);
    PMW3901_WriteRegister(0x44, 0x42);
    PMW3901_WriteRegister(0x4C, 0x80);
    PMW3901_WriteRegister(0x7F, 0x10);
    PMW3901_WriteRegister(0x5B, 0x02);
    PMW3901_WriteRegister(0x7F, 0x07);
    PMW3901_WriteRegister(0x40, 0x41);
    PMW3901_WriteRegister(0x70, 0x00);

    HAL_Delay(100);
    PMW3901_WriteRegister(0x32, 0x44);
    PMW3901_WriteRegister(0x7F, 0x07);
    PMW3901_WriteRegister(0x40, 0x40);
    PMW3901_WriteRegister(0x7F, 0x06);
    PMW3901_WriteRegister(0x62, 0xf0);
    PMW3901_WriteRegister(0x63, 0x00);
    PMW3901_WriteRegister(0x7F, 0x0D);
    PMW3901_WriteRegister(0x48, 0xC0);
    PMW3901_WriteRegister(0x6F, 0xd5);
    PMW3901_WriteRegister(0x7F, 0x00);
    PMW3901_WriteRegister(0x5B, 0xa0);
    PMW3901_WriteRegister(0x4E, 0xA8);
    PMW3901_WriteRegister(0x5A, 0x50);
    PMW3901_WriteRegister(0x40, 0x80);
#endif
    return 1;
}   