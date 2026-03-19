/**
  ******************************************************************************
  * @file    hgr_model_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-03-11T01:07:30+0100
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef HGR_MODEL_DATA_PARAMS_H
#define HGR_MODEL_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_HGR_MODEL_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_hgr_model_data_weights_params[1]))
*/

#define AI_HGR_MODEL_DATA_CONFIG               (NULL)


#define AI_HGR_MODEL_DATA_ACTIVATIONS_SIZES \
  { 19552, }
#define AI_HGR_MODEL_DATA_ACTIVATIONS_SIZE     (19552)
#define AI_HGR_MODEL_DATA_ACTIVATIONS_COUNT    (1)
#define AI_HGR_MODEL_DATA_ACTIVATION_1_SIZE    (19552)



#define AI_HGR_MODEL_DATA_WEIGHTS_SIZES \
  { 7568, }
#define AI_HGR_MODEL_DATA_WEIGHTS_SIZE         (7568)
#define AI_HGR_MODEL_DATA_WEIGHTS_COUNT        (1)
#define AI_HGR_MODEL_DATA_WEIGHT_1_SIZE        (7568)



#define AI_HGR_MODEL_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_hgr_model_activations_table[1])

extern ai_handle g_hgr_model_activations_table[1 + 2];



#define AI_HGR_MODEL_DATA_WEIGHTS_TABLE_GET() \
  (&g_hgr_model_weights_table[1])

extern ai_handle g_hgr_model_weights_table[1 + 2];


#endif    /* HGR_MODEL_DATA_PARAMS_H */
