/*
 * camera.h
 *
 *  Created on: 20 mars 2026
 *      Author: foura
 */

#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "main.h"

#define CAM_WIDTH   320
#define CAM_HEIGHT  240

extern uint16_t frame_buffer[CAM_WIDTH * CAM_HEIGHT];

void Camera_Capture(void);
uint8_t Camera_IsFrameReady(void);
void Camera_Init(void);
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi);
#endif /* INC_CAMERA_H_ */
