/*
 * camera.c
 *
 *  Created on: 20 mars 2026
 *      Author: foura
 */

#include  "main.h"
#include "camera.h"
#include <string.h>
#include <stdio.h>

// VERY IMPORTANT
extern DCMI_HandleTypeDef hdcmi;

// Frame buffer
uint16_t frame_buffer[CAM_WIDTH * CAM_HEIGHT];

static volatile uint8_t frame_ready = 0;

// ==========================
// INIT
// ==========================
void Camera_Init(void)
{
    frame_ready = 0;

    /* Power ON the camera module */
    HAL_GPIO_WritePin(DCMI_PWR_EN_GPIO_Port, DCMI_PWR_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(20);

    /* Hard reset the OV5640 */
    HAL_GPIO_WritePin(EXT_RST_GPIO_Port, EXT_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(EXT_RST_GPIO_Port, EXT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(20);
}

// ==========================
// START CAPTURE
// ==========================
void Camera_Capture(void)
{
    frame_ready = 0;

    __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME);
    __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_ERR | DCMI_IT_OVR);

    HAL_DCMI_Start_DMA(&hdcmi,
                       DCMI_MODE_SNAPSHOT,
                       (uint32_t)frame_buffer,
                       CAM_WIDTH * CAM_HEIGHT / 2);
}

// ==========================
// CHECK FRAME
// ==========================
uint8_t Camera_IsFrameReady(void)
{
    return frame_ready;
}

// ==========================
// CALLBACK
// ==========================

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    frame_ready = 1;  // tell your main loop the frame is ready

}
