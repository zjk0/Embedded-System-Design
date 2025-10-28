  /**
  ******************************************************************************
  * @file    GUI_App.c
  * @author  MCD Application Team
  * @brief   Simple demo drawing "Hello world"  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright 漏 2018 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "GUI_App.h"
#include "GUI.h"

#include "DIALOG.h"
extern  WM_HWIN CreateWindow(void);  
  

void GRAPHICS_MainTask(void) {

  /* 2- Create a Window using GUIBuilder */
  CreateWindow();
 
/* USER CODE BEGIN GRAPHICS_MainTask */
 /* User can implement his graphic application here */
extern GRAPH_DATA_Handle hData;
extern void CheckTorch(void);
extern void CheckAlarmTrigger(void); // 娣诲姞闂归挓妫?鏌ュ０鏄?
extern void Update_Waveform_Display(WM_HWIN hGraph);
extern WM_HWIN CreateTimeDomainWindow(void);
extern void Start_ADC_Acquisition(void);
extern void MX_ADC1_Init(void);
extern void MX_DMA_Init(void);
extern GRAPH_DATA_Handle hData;
extern WM_HWIN hGraphTimeDomain;
extern WM_HWIN hGraphFrequencyDomain;




GUI_UC_SetEncodeUTF8();

  while(1)
{
      CheckTorch();
      CheckAlarmTrigger(); 
      
      //更新波形显示（只在时域窗口打开时更新）
      //
        Update_Waveform_Display(hGraphTimeDomain);
       // Update_Power_Spectrum_Display(hGraphFrequencyDomain);
     // }
        Process_AudioPitch();
        //Calculate_Power_Spectrum();
    //  Update_Power_Spectrum_Display(hGraphFrequencyDomain);
       
      GUI_Delay(80);
}

/* USER CODE END GRAPHICS_MainTask */
  while(1)
{
      GUI_Delay(100);
}
}

/*************************** End of file ****************************/
