/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hgr_model.h"
#include "hgr_model_data_params.h"
#include "hgr_model_data.h"
#include "test_image.h"       // your test image
#include "lcd_utils.h"        // the function Display_Color_From_Class
#include <stdint.h>
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
AI_ALIGNED(4) static ai_u8 activations[AI_HGR_MODEL_DATA_ACTIVATIONS_SIZE];
// Separate IO buffers (safe + standard practice)
AI_ALIGNED(4) static ai_i8 input_buffer[4096];   // 64x64x1 int8
AI_ALIGNED(4) static ai_i8 output_buffer[10];    // 10 classes logits

// Forward declaration of your task function
void StartHGRTask(void *argument)
{
    Display_Color_From_Class(9);  // initial orange while booting

    // 1. Create model
    ai_handle hgr_model = AI_HANDLE_NULL;
    ai_error err = ai_hgr_model_create(&hgr_model, AI_HGR_MODEL_DATA_CONFIG);  // NULL is fine
    if (err.code != AI_ERROR_NONE) {
        while(1); // creation failed
    }

    // 2. Prepare params (THIS WAS MISSING → your init error)
    ai_network_params params = {
        AI_HGR_MODEL_DATA_WEIGHTS(ai_hgr_model_data_weights_get()),
        AI_HGR_MODEL_DATA_ACTIVATIONS(activations)
    };

    // 3. Initialize model
    if (!ai_hgr_model_init(hgr_model, &params)) {
        err = ai_hgr_model_get_error(hgr_model);
        // printf or just halt (printf may not work without UART)
        while(1);
    }

    // 4. Get input/output descriptors (only once)
    ai_buffer* ai_input  = ai_hgr_model_inputs_get(hgr_model, NULL);
    ai_buffer* ai_output = ai_hgr_model_outputs_get(hgr_model, NULL);

    uint8_t predicted_class;

    for(;;)
    {
        // === Fill input buffer (your test image) ===
        for (int i = 0; i < 4096; i++) {
            input_buffer[i] = C_09[i] - 128;   // uint8 → int8 quantization
        }

        // === CRITICAL: point the descriptors to your buffers ===
        ai_input[0].data  = (ai_handle)input_buffer;
        ai_output[0].data = (ai_handle)output_buffer;

        // === Run inference ===
        ai_hgr_model_run(hgr_model, ai_input, ai_output);

        // === Argmax on 10 classes (indices 0-9) ===
        int8_t* out = output_buffer;
        predicted_class = 0;
        int8_t max_val = out[0];
        for (int i = 1; i < 10; i++) {
            if (out[i] > max_val) {
                max_val = out[i];
                predicted_class = i;
            }
        }

        // === Display color (adjust +1 if you want classes 1-10) ===
        Display_Color_From_Class(predicted_class + 1);   // change to just predicted_class if you prefer 0-9

        osDelay(1000);  // 1 second so you can see the color change
    }
}
/* USER CODE END Application */

