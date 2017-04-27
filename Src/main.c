/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "timers.h"
#include "buttons.h"
#include "appldefined.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
t_maschine maschine;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_NVIC_Init(void);                                    
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  
    
  /* Initialize interrupts */
  MX_NVIC_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
    maschine.mode = MODE_L;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      static bool sts_but = false;
      
      if (true == get_button())
      {          
          //sts_but = true;
      }
      
      if (
              GPIO_PIN_RESET == HAL_GPIO_ReadPin(But_Mode_GPIO_Port, But_Mode_Pin)
           && sts_but == false               
         )
      {
          HAL_Delay(BUT_DEBOUNCE);
   
          if (
                 GPIO_PIN_RESET == HAL_GPIO_ReadPin(But_Mode_GPIO_Port, But_Mode_Pin)              
             )
          {
              sts_but = true; 
              ;
          
              switch (maschine.mode)
              {
                  case MODE_OFF:
                     
                     maschine.mode  = MODE_L;
                     maschine.state = STATE_MASCHINE_ON;
                     pwm_on();
                     set_pwm_tim2_ch4_duty (25);
                     HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
                     HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
                     HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET  );
                     break;
                  
                  case MODE_L:
                  
                      maschine.mode  = MODE_M;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (50); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET);
                      break;
                  
                  case MODE_M:
                 
                      maschine.mode  = MODE_H;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (75);
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET);                      
                      break;
                  
                  case MODE_H:
                  
                      maschine.mode  = MODE_F;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (100); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET); 
                      break;
                  
                  case MODE_F:
                  
                      maschine.mode  = MODE_OFF;
                      maschine.state = STATE_MASCHINE_OFF;
                      pwm_off();
                      set_pwm_tim2_ch4_duty (0); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET); 
                      break;
                           
                  default:
                      break;
              }   


          }  
        }
      if (
              GPIO_PIN_SET == HAL_GPIO_ReadPin(But_Mode_GPIO_Port, But_Mode_Pin)
           && sts_but == true
         )
      {
          HAL_Delay(BUT_DEBOUNCE);
          
          if (GPIO_PIN_SET == HAL_GPIO_ReadPin(But_Mode_GPIO_Port, But_Mode_Pin))
          {
             sts_but = false;
          }
      }
      
      
   }
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time 
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_NVIC_Init(void)
{
  /* EXTI3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/** NVIC Configuration
*/

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Led_R_Pin|Led_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Led_B_Pin|PWR_REMOUTE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : But_Stop_Pin But_Mode_Pin */
  GPIO_InitStruct.Pin = But_Stop_Pin|But_Mode_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_R_Pin Led_G_Pin */
  GPIO_InitStruct.Pin = Led_R_Pin|Led_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_B_Pin PWR_REMOUTE_Pin */
  GPIO_InitStruct.Pin = Led_B_Pin|PWR_REMOUTE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
