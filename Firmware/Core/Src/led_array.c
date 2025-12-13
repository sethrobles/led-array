/*
 * led_array.c
 *
 *  Created on: Dec 5, 2025
 *      Author: sethrobles
 */
#include "main.h"
#include "led_array.h"

static GPIO_TypeDef* SER_GPIO_Ports[4] = {
    SER0_GPIO_Port,
    SER1_GPIO_Port,
    SER2_GPIO_Port,
    SER3_GPIO_Port
};

static uint16_t SER_Pins[4] = {
    SER0_Pin,
    SER1_Pin,
    SER2_Pin,
    SER3_Pin
};


static GPIO_TypeDef* M_GPIO_Ports[8] = {
    M0_GPIO_Port,
    M1_GPIO_Port,
    M2_GPIO_Port,
    M3_GPIO_Port,
    M4_GPIO_Port,
    M5_GPIO_Port,
    M6_GPIO_Port,
    M7_GPIO_Port,
};


// Array of M0-M7 pins for row selection
static uint16_t M_Pins[8] = {
    M0_Pin, M1_Pin, M2_Pin, M3_Pin,
    M4_Pin, M5_Pin, M6_Pin, M7_Pin
};


void ShiftReg_Write32(uint32_t pattern, uint8_t scan_group)
{
    GPIO_TypeDef* data_port = SER_GPIO_Ports[scan_group];
    uint16_t      data_pin  = SER_Pins[scan_group];

    // Send MSB first instead of LSB first
    for (int i = 31; i >= 0; --i)
    {
        uint8_t bit = (pattern >> i) & 0x01;

        HAL_GPIO_WritePin(data_port, data_pin,
                          bit ? GPIO_PIN_SET : GPIO_PIN_RESET);

        HAL_GPIO_WritePin(SRCLK_GPIO_Port, SRCLK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SRCLK_GPIO_Port, SRCLK_Pin, GPIO_PIN_RESET);
    }
}


void disableAllRows(void)
{
    // All rows OFF → write 0
    HAL_GPIO_WritePin(GPIOB,
        M0_Pin|M1_Pin|M2_Pin|M3_Pin|
        M4_Pin|M5_Pin|M6_Pin|M7_Pin,
        GPIO_PIN_RESET);
}

void enableRow(uint8_t m_index)
{
    if (m_index < 8) {
        // JUST turn one ON; don't disable here
        HAL_GPIO_WritePin(M_GPIO_Ports[m_index], M_Pins[m_index], GPIO_PIN_SET);
    }
}


void writeFrame(const uint8_t frame[32][32])
{
    for (int row = 0; row < 32; row++)
    {
        int scan_index = row / 8;
        int mos_index  = row % 8;

        // 1) Turn *all* rows off before touching the shift registers
        disableAllRows();

        // 2) Build the 32-bit pattern for this row
        uint32_t pattern = 0;
        for (int col = 0; col < 32; col++)
        {
            if (frame[row][col]) {
                pattern |= (1u << col);
            }
        }

        // 3) Clear all scan groups to 0 so no stale bits remain
        for (int g = 0; g < 4; ++g)
        {
            ShiftReg_Write32(0x00000000, g);
        }

        // 4) Load only this row’s scan group with the pattern
        ShiftReg_Write32(pattern, scan_index);

        // 5) Latch the new data to the outputs
        HAL_GPIO_WritePin(RCLK_GPIO_Port, RCLK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RCLK_GPIO_Port, RCLK_Pin, GPIO_PIN_RESET);

        // 6) Now enable *just this* row
        enableRow(mos_index);

        // Optional: tiny dwell time for POV / brightness
         for (volatile int d = 0; d < 500; ++d) { }
//         HAL_Delay();
    }

    // After scanning all rows, blank everything
    disableAllRows();
}

void repeatFrame_20(const uint8_t frame[32][32])
{
	repeatFrame(frame, 20);
}


void repeatFrame(const uint8_t frame[32][32], int num_repeat)
{
	for (int i = 0; i < num_repeat; i++)
	{
		writeFrame(frame);
		HAL_Delay(1);
	}
}
