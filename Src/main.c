/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "timers.h"
#include "buttons.h"
#include "appldefined.h"

t_maschine maschine;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_NVIC_Init(void);                                    
                                

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_NVIC_Init();
  
  maschine.mode = MODE_OFF;
    
  HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_SET); 
  pwm_on();
  set_pwm_tim2_ch4_duty (0); 
    
  //while(false == delay_ms(3000)){};  
while (1)
  {
      static bool sts_but_mode = false;
      static bool sts_but_stop = false;


      if (BUT_MODE == get_button())
      {          
          sts_but_mode = true;
      }
      
      if (BUT_STOP == get_button())
      {          
          sts_but_stop = true;
      }
      
//      if (
//            (false != delay_ms(15000))
//         )
//      {
//          if (maschine.mode == MODE_OFF)
//          {
//              HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_RESET);
//          }              
//          
//      }
 //========================================== кнопка MODE ================================================     

      if (sts_but_mode == true && false != delay_ms(BUT_DEBOUNCE))
      {   
          if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(But_Mode_GPIO_Port, But_Mode_Pin))
          {
              sts_but_mode = false; 
          
              switch (maschine.mode)
              {
                  case MODE_OFF:
                     HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_SET);
                     maschine.mode  = MODE_L;
                     maschine.state = STATE_MASCHINE_ON;
                     
                     HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET  );
                     HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET  );
                     HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET);
                  
                     pwm_on();
                     set_pwm_tim2_ch4_duty (35);
                         
                     break;
                  
                  case MODE_L:
                      HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_SET);
                      maschine.mode  = MODE_M;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (50); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET  );
                      break;
                  
                  case MODE_M:
                      HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_SET);
                      maschine.mode  = MODE_H;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (70);
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET  );                      
                      break;
                  
                  case MODE_H:
                      HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_SET);
                      maschine.mode  = MODE_F;
                      maschine.state = STATE_MASCHINE_ON;
                      pwm_on();
                      set_pwm_tim2_ch4_duty (100); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET  );
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET  ); 
                      break;
                  
                  case MODE_F:
                  
                      maschine.mode  = MODE_OFF;
                      maschine.state = STATE_MASCHINE_OFF;
                      //pwm_off();
                      set_pwm_tim2_ch4_duty (0); 
                      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET);
                      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET);
                      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET);
                      HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_RESET); 
                      break;
                           
                  default:
                      break;
              }   
          }
          else
          {
              sts_but_mode = false;
          }
      }
      
 //============================================== кнопка STOP =============================================     
      
      if (sts_but_stop == true && false != delay_ms(BUT_DEBOUNCE))
      {  
          if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(But_Stop_GPIO_Port, But_Stop_Pin))
          {
              sts_but_stop = false; 
              maschine.mode  = MODE_OFF;
              maschine.state = STATE_MASCHINE_OFF;
              //pwm_off();
              set_pwm_tim2_ch4_duty (0); 
              HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(PWR_REMOUTE_GPIO_Port, PWR_REMOUTE_Pin, GPIO_PIN_RESET);
          }  
          else
          {
              sts_but_stop = false; 
          }
      }
      
 //========================================================================================================
      
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

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Led_R_Pin|Led_G_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Led_B_Pin, GPIO_PIN_SET);

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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
