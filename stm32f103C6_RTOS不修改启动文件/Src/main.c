/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

#define START_TASK_PRIO     1
#define START_STK_SIZE      64  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define LED0_TASK_PRIO      2
#define LED0_STK_SIZE       30  
TaskHandle_t LED0Task_Handler;
void led0_task(void *pvParameters);

#define LED1_TASK_PRIO      2
#define LED1_STK_SIZE       30
TaskHandle_t LED1Task_Handler;
void led1_task(void *pvParameters);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  /* Configure PB0 to PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	xTaskCreate((TaskFunction_t )start_task,
							(const char*    )"start_task",
							(uint16_t       )START_STK_SIZE, 
							(void*          )NULL,
							(UBaseType_t    )START_TASK_PRIO,
							(TaskHandle_t*  )&StartTask_Handler);            
	vTaskStartScheduler(); 
	
  while (1)
  {
		;
  }
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();

    xTaskCreate((TaskFunction_t )led0_task,         
                (const char*    )"led0_task",       
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,              
                (UBaseType_t    )LED0_TASK_PRIO,    
                (TaskHandle_t*  )&LED0Task_Handler);   

    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);        
   
    vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();
}

void led0_task(void *pvParameters)
{
    while(1)
    {
		    GPIO_ResetBits(GPIOB , GPIO_Pin_0);
	      GPIO_ResetBits(GPIOB , GPIO_Pin_1);
	      GPIO_ResetBits(GPIOB , GPIO_Pin_2);
        vTaskDelay(10/portTICK_RATE_MS );
				//vTaskDelay(20);
			
				GPIO_SetBits(GPIOB , GPIO_Pin_0);
        GPIO_SetBits(GPIOB , GPIO_Pin_1);
        GPIO_SetBits(GPIOB , GPIO_Pin_2);	
			  vTaskDelay(10/portTICK_RATE_MS );
			  //vTaskDelay(20);
    }
}   

void led1_task(void *pvParameters)
{
    while(1)
    {			
		    GPIO_ResetBits(GPIOB , GPIO_Pin_3);
	      GPIO_ResetBits(GPIOB , GPIO_Pin_4);
	      GPIO_ResetBits(GPIOB , GPIO_Pin_5);
			  GPIO_ResetBits(GPIOB , GPIO_Pin_6);
        vTaskDelay(10);
			
				GPIO_SetBits(GPIOB , GPIO_Pin_3);
        GPIO_SetBits(GPIOB , GPIO_Pin_4);
        GPIO_SetBits(GPIOB , GPIO_Pin_5);	
			  GPIO_SetBits(GPIOB , GPIO_Pin_6);	
			  vTaskDelay(20);
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
