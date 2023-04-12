/**
 * @file tp_ft3168.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-04-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <driver/i2c.h>



void ft3168_i2c_init();

uint8_t ft3168_is_touched(i2c_port_t i2c_num, TickType_t ticks_to_wait);

void ft3168_read_p1_coor(int* x, int* y);

void ft3168_read_p2_coor(int* x, int* y);



