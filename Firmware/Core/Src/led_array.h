/*
    * led_array.h
    *
    *  Created on: Dec 5, 2025
    *      Author: sethrobles
    */

   #ifndef INC_LED_ARRAY_H_
   #define INC_LED_ARRAY_H_

   #include <stdint.h>

   void ShiftReg_Write32(uint32_t pattern, uint8_t scan_group);
   void writeFrame(const uint8_t frame[32][32]);
   void repeatFrame_20(const uint8_t frame[32][32]);
   void repeatFrame(const uint8_t frame[32][32], int num_repeat);
   #endif /* INC_LED_ARRAY_H_ */
