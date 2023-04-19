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
        // .sda_pullup_en = GPIO_PULLUP_ENABLE,
        // .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
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



void ft3168_test()
{
    ft3168_i2c_init(I2C_NUM_0, 13, 14);





    gpio_reset_pin(GPIO_NUM_1);
    gpio_set_direction(GPIO_NUM_1, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_1, GPIO_PULLUP_ONLY);
    gpio_set_level(GPIO_NUM_1, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(GPIO_NUM_1, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(GPIO_NUM_1, 1);
    vTaskDelay(pdMS_TO_TICKS(300));



    gpio_reset_pin(GPIO_NUM_15);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_PULLDOWN);






    uint8_t id = ft3168_get_id(I2C_NUM_0, portMAX_DELAY);
    printf("ID %d 0x%X\n", id, id);
    vTaskDelay(pdMS_TO_TICKS(100));





    uint8_t buffer[5];

    // buffer[0] = 0x00;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);


    // ft3168_set_g_state(I2C_NUM_0, portMAX_DELAY, 0x00);
    // ft3168_set_mode(I2C_NUM_0, portMAX_DELAY, 0x00);


    // // uint8_t buffer[5];
    // buffer[0] = 0x86;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);
    // vTaskDelay(pdMS_TO_TICKS(100));


    // buffer[0] = 0xA4;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);
    // vTaskDelay(pdMS_TO_TICKS(100));


    // buffer[0] = 0xAE;
    // buffer[1] = 0x00;
    // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);
    // vTaskDelay(pdMS_TO_TICKS(100));


    // buffer[0] = 0xA5;
    // buffer[1] = 0x03;
    // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);
    // vTaskDelay(pdMS_TO_TICKS(100));



    uint8_t ret = 0;
    int x, y;
    while (1) {

        // ret = ft3168_is_touched(I2C_NUM_0, portMAX_DELAY);

        // printf("%d 0x%X\n", ret, ret);


        // buffer[0] = 0x00;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);
        ft3168_read_coor(I2C_NUM_0, portMAX_DELAY, &x, &y);


        // printf("gpio: %d\n", gpio_get_level(GPIO_NUM_15));
        // if (gpio_get_level(GPIO_NUM_15) == 0) {
        //     // gpio_set_level(GPIO_NUM_15, 1);
        //     ft3168_read_coor(I2C_NUM_0, portMAX_DELAY, &x, &y);
        // }


        // buffer[0] = 0x02;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

        // buffer[0] = 0x03;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

        // buffer[0] = 0x04;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

        // buffer[0] = 0x05;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

        // buffer[0] = 0x06;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);


        // buffer[0] = 0x00;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);

        // buffer[0] = 0x00;
        // buffer[1] = 0x00;
        // i2c_master_write_to_device(I2C_NUM_0, _ADDR_SLAVE, buffer, 2, portMAX_DELAY);



        vTaskDelay(pdMS_TO_TICKS(100));

    }



}

