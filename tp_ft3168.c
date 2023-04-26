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



static const uint8_t _ADDR_SLAVE                        = 0x38;

// static const uint8_t _ADDR_REG_MODE_SWITCH              = 0x00;
static const uint8_t _ADDR_REG_TD_STATUS                = 0x02;

// static const uint8_t _ADDR_REG_P1_XH                    = 0x03;
// static const uint8_t _ADDR_REG_P1_XL                    = 0x04;
// static const uint8_t _ADDR_REG_P1_YH                    = 0x05;
// static const uint8_t _ADDR_REG_P1_YL                    = 0x06;
// static const uint8_t _ADDR_REG_P1_WEIGHT                = 0x07;
// static const uint8_t _ADDR_REG_P1_MISC                  = 0x08;

// static const uint8_t _ADDR_REG_P2_XH                    = 0x09;
// static const uint8_t _ADDR_REG_P2_XL                    = 0x0A;
// static const uint8_t _ADDR_REG_P2_YH                    = 0x0B;
// static const uint8_t _ADDR_REG_P2_YL                    = 0x0C;
// static const uint8_t _ADDR_REG_P2_WEIGHT                = 0x0D;
// static const uint8_t _ADDR_REG_P2_MISC                  = 0x0E;

// static const uint8_t _ADDR_REG_ID_G_THGROUP             = 0x80;
// static const uint8_t _ADDR_REG_ID_G_THDIFF              = 0x85;
// static const uint8_t _ADDR_REG_ID_G_CTRL                = 0x86;
// static const uint8_t _ADDR_REG_ID_G_TIMEENTERMONITOR    = 0x87;
// static const uint8_t _ADDR_REG_ID_G_PERIODACTIVE        = 0x88;
// static const uint8_t _ADDR_REG_ID_G_PERIODMONITOR       = 0x89;
// static const uint8_t _ADDR_REG_ID_G_FREQ_HOPPING_EN     = 0x8B;

// static const uint8_t _ADDR_REG_ID_G_CIPHER_MID          = 0x9F;
// static const uint8_t _ADDR_REG_ID_G_CIPHER_LOW          = 0xA0;
// static const uint8_t _ADDR_REG_ID_G_CIPHER_HIGH         = 0xA3;

// static const uint8_t _ADDR_REG_ID_G_MODE                = 0xA4;
static const uint8_t _ADDR_REG_ID_G_PMODE               = 0xA5;
// static const uint8_t _ADDR_REG_ID_G_FACE_DEC_MODE       = 0xB0;
// static const uint8_t _ADDR_REG_ID_G_STATE               = 0xBC;








esp_err_t ft3168_i2c_init(i2c_port_t i2c_port, int sda, int scl)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        // .sda_pullup_en = GPIO_PULLUP_DISABLE,
        // .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = 100000,
    };

    i2c_param_config(i2c_port, &conf);

    return i2c_driver_install(i2c_port, conf.mode, 0, 0, 0);
}



uint8_t ft3168_is_touched(i2c_port_t i2c_num, TickType_t ticks_to_wait)
{
    uint8_t touched_num = 0;
    i2c_master_write_read_device(i2c_num, _ADDR_SLAVE, &_ADDR_REG_TD_STATUS, 1, &touched_num, 1, ticks_to_wait);
    return touched_num;
}


uint8_t ft3168_get_id(i2c_port_t i2c_num, TickType_t ticks_to_wait)
{
    uint8_t id = 0;
    uint8_t shit = 0xA0;
    // i2c_master_write_read_device(i2c_num, _ADDR_SLAVE, &_ADDR_REG_ID_G_CIPHER_HIGH, 1, &id, 1, ticks_to_wait);
    i2c_master_write_read_device(i2c_num, _ADDR_SLAVE, &shit, 1, &id, 1, ticks_to_wait);
    return id;
}



void ft3168_read_p1_coor(int* x, int* y)
{

    
}



void ft3168_read_p2_coor(int* x, int* y)
{



}


void ft3168_read_coor(i2c_port_t i2c_num, TickType_t ticks_to_wait, int* x, int* y)
{
    uint8_t ret_buffer[5] = {0};
    i2c_master_write_read_device(i2c_num, _ADDR_SLAVE, &_ADDR_REG_TD_STATUS, 1, ret_buffer, 5, ticks_to_wait);

    printf("%d 0x%X\n", ret_buffer[0], ret_buffer[0]);

    *x = (((uint16_t)((ret_buffer[1] & 0x0F)<<8))+(uint16_t)ret_buffer[2]);
    *y = (((uint16_t)((ret_buffer[3] & 0x0F)<<8))+(uint16_t)ret_buffer[4]);


    printf("%d %d\n", *x, *y);
}


esp_err_t ft3168_set_mode(i2c_port_t i2c_num, TickType_t ticks_to_wait, uint8_t mode)
{
    uint8_t buffer[2] = {_ADDR_REG_ID_G_PMODE, mode};
    return i2c_master_write_to_device(i2c_num, _ADDR_SLAVE, buffer, 2, ticks_to_wait);
}


esp_err_t ft3168_set_g_state(i2c_port_t i2c_num, TickType_t ticks_to_wait, uint8_t state)
{
    uint8_t buffer[2] = {_ADDR_REG_ID_G_PMODE, state};
    return i2c_master_write_to_device(i2c_num, _ADDR_SLAVE, buffer, 2, ticks_to_wait);
}






typedef struct{
	uint16_t axisX;
	uint16_t axisY;
	uint8_t Index;
	uint8_t evt;
	uint8_t ID;
}touch_point_t;
touch_point_t Point;





void ft3168_test()
{
    ft3168_i2c_init(I2C_NUM_1, 14, 13);




    /* Reset */
    gpio_reset_pin(GPIO_NUM_16);
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_16, GPIO_PULLUP_ONLY);
    gpio_set_level(GPIO_NUM_16, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(GPIO_NUM_16, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(GPIO_NUM_16, 1);
    // vTaskDelay(pdMS_TO_TICKS(300));


    /* Set int pin */
    gpio_reset_pin(GPIO_NUM_15);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_INPUT);






    // uint8_t id = ft3168_get_id(I2C_NUM_1, portMAX_DELAY);
    // printf("ID %d 0x%X\n", id, id);
    // vTaskDelay(pdMS_TO_TICKS(100));



    uint8_t buffer[7] = {0xFF};

    // // 00正常模式04工厂模式
    // buffer[0] = 0x00;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 配置芯片功耗模式
    // buffer[0] = 0xA5;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 配置工作模式01正常
    // buffer[0] = 0xBC;
    // buffer[1] = 0x01;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // 00禁止进入监视器模式
    buffer[0] = 0x86;
    buffer[1] = 0x00;
    i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);


    // 触摸阈值
    buffer[0] = 0x80;
    buffer[1] = 0x7D;
    i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 配置没有触摸多久进入监视器模式
    // buffer[0] = 0x87;
    // buffer[1] = 0x05;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 00禁用手势
    // buffer[0] = 0xD0;
    // buffer[1] = 0x01;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 00禁用手势
    // buffer[0] = 0xD1;
    // buffer[1] = 0x30;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

    // // 配置工作模式01正常
    // buffer[0] = 0xA5;
    // buffer[1] = 0x01;
    // i2c_master_write_to_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);



    buffer[0] = 0xA6;
    i2c_master_write_read_device(I2C_NUM_1, _ADDR_SLAVE, buffer, 1, &buffer[1], 1, portMAX_DELAY);
    if (buffer[1] == 0xFF) {
		printf("Touch I2c Init Failed[0x%02x]\n", buffer[1]);
		while (1);
	} else {
		printf("Touch I2c Init Success[0x%02x]\n", buffer[1]);
	}




    uint8_t addr = 0x00;

    

    while (1)
    {

        if (gpio_get_level(GPIO_NUM_15) == 0) {
            

            i2c_master_write_read_device(I2C_NUM_1, _ADDR_SLAVE, &addr, 1, buffer, 7, portMAX_DELAY);

            printf(" TD_STATUS [%d]\n", buffer[0x02]);
            if(buffer[0x02] == 0x01) {
                Point.ID 	= (buffer[0x05] >> 4) & 0x0f;
                Point.evt 	= (buffer[0x03] >> 6) & 0x3;
                Point.axisX = ((buffer[0x03] & 0x0f) << 8) | buffer[0x04];
                Point.axisY = ((buffer[0x05] & 0x0f) << 8) | buffer[0x06];
                printf("ID[%d] ID[0x%02x] X[%d] Y[%d]\n", Point.ID, Point.evt, Point.axisX, Point.axisY);
            }

        }







        vTaskDelay(pdMS_TO_TICKS(10));









    }





}

