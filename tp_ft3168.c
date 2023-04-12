/**
 * @file tp_ft3168.c
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-04-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "tp_ft3168.h"



static const uint8_t _ADDR_SLAVE                        = 0x00;

static const uint8_t _ADDR_REG_MODE_SWITCH              = 0x00;
static const uint8_t _ADDR_REG_TD_STATUS                = 0x02;

static const uint8_t _ADDR_REG_P1_XH                    = 0x03;
static const uint8_t _ADDR_REG_P1_XL                    = 0x04;
static const uint8_t _ADDR_REG_P1_YH                    = 0x05;
static const uint8_t _ADDR_REG_P1_YL                    = 0x06;
static const uint8_t _ADDR_REG_P1_WEIGHT                = 0x07;
static const uint8_t _ADDR_REG_P1_MISC                  = 0x08;

static const uint8_t _ADDR_REG_P2_XH                    = 0x09;
static const uint8_t _ADDR_REG_P2_XL                    = 0x0A;
static const uint8_t _ADDR_REG_P2_YH                    = 0x0B;
static const uint8_t _ADDR_REG_P2_YL                    = 0x0C;
static const uint8_t _ADDR_REG_P2_WEIGHT                = 0x0D;
static const uint8_t _ADDR_REG_P2_MISC                  = 0x0E;

static const uint8_t _ADDR_REG_ID_G_THGROUP             = 0x80;
static const uint8_t _ADDR_REG_ID_G_THDIFF              = 0x85;
static const uint8_t _ADDR_REG_ID_G_CTRL                = 0x86;
static const uint8_t _ADDR_REG_ID_G_TIMEENTERMONITOR    = 0x87;
static const uint8_t _ADDR_REG_ID_G_PERIODACTIVE        = 0x88;
static const uint8_t _ADDR_REG_ID_G_PERIODMONITOR       = 0x89;
static const uint8_t _ADDR_REG_ID_G_FREQ_HOPPING_EN     = 0x8B;

static const uint8_t _ADDR_REG_ID_G_CIPHER_MID          = 0x9F;
static const uint8_t _ADDR_REG_ID_G_CIPHER_LOW          = 0xA0;
static const uint8_t _ADDR_REG_ID_G_CIPHER_HIGH         = 0xA3;

static const uint8_t _ADDR_REG_ID_G_MODE                = 0xA4;
static const uint8_t _ADDR_REG_ID_G_PMODE               = 0xA5;
static const uint8_t _ADDR_REG_ID_G_FACE_DEC_MODE       = 0xB0;
static const uint8_t _ADDR_REG_ID_G_STATE               = 0xBC;








void ft3168_i2c_init()
{




}



uint8_t ft3168_is_touched(i2c_port_t i2c_num, TickType_t ticks_to_wait)
{
    uint8_t touched_num = 0;
    i2c_master_write_read_device(i2c_num, _ADDR_SLAVE, &_ADDR_REG_TD_STATUS, 1, &touched_num, 1, ticks_to_wait);
    return touched_num;
}





void ft3168_read_p1_coor(int* x, int* y)
{

    
}



void ft3168_read_p2_coor(int* x, int* y)
{



}
