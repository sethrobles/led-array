/*
 * frames.h
 *
 *  Created on: Dec 6, 2025
 *      Author: sethrobles
 */

#ifndef SRC_FRAMES_H_
#define SRC_FRAMES_H_

//Sprite Types

typedef enum {
    SPRITE_HEART = 0,
    SPRITE_SNOWFLAKE = 1
} SpriteType;



void animateBorderDot(uint32_t baseDelayMs);
void animateDiagonalDot(uint32_t baseDelayMs);
void animateCornersAroundEdges(uint32_t baseDelayMs);
void animateSpriteBubbles(SpriteType sprite, uint32_t totalSteps, uint32_t baseDelayMs);
void animateFireworks(uint32_t numFireworks, uint32_t baseDelayLoops);


// Letter frames
extern const uint8_t aFrame[32][32];
extern const uint8_t iFrame[32][32];
extern const uint8_t oFrame[32][32];
extern const uint8_t uFrame[32][32];
extern const uint8_t vFrame[32][32];
extern const uint8_t yFrame[32][32];

extern const uint8_t heartFrame[32][32];
extern const uint8_t a_s_heartFrame[32][32];




extern const uint8_t blank32x32[32][32];
extern const uint8_t corners32x32[32][32];
extern const uint8_t diagonal32x32[32][32];
extern const uint8_t partialDiagonal32x32[32][32];
extern const uint8_t border32x32[32][32];
extern const uint8_t leftColumn32x32[32][32];
extern const uint8_t centerColumn32x32[32][32];
extern const uint8_t fourRandomColumns32x32[32][32];
extern const uint8_t bottomRightDiagonal8_32x32[32][32];
extern const uint8_t fourRandomRows32x32[32][32];
extern const uint8_t largerleftdiagonal32x32[32][32];



#endif /* SRC_FRAMES_H_ */
