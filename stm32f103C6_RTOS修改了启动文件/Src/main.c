
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

void delay(void)
{
	int i,j;
	for(i=0;i<500;i++)
	{
		for(j=0;j<100;j++)
		{;}
	}
}

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

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_Configuration();
/*	
	//test
	GPIO_SetBits(GPIOB , GPIO_Pin_7);
  GPIO_SetBits(GPIOB , GPIO_Pin_8);
  GPIO_SetBits(GPIOB , GPIO_Pin_9);	
	GPIO_SetBits(GPIOB , GPIO_Pin_10);	
	GPIO_SetBits(GPIOB , GPIO_Pin_11);
  GPIO_SetBits(GPIOB , GPIO_Pin_12);
  GPIO_SetBits(GPIOB , GPIO_Pin_13);	
	GPIO_SetBits(GPIOB , GPIO_Pin_14);	
	GPIO_SetBits(GPIOB , GPIO_Pin_15);	
	
	GPIO_SetBits(GPIOA , GPIO_Pin_All);	
*/	
	
	
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
        //vTaskDelay(10/portTICK_RATE_MS );
				vTaskDelay(20);
			
				GPIO_SetBits(GPIOB , GPIO_Pin_0);
        GPIO_SetBits(GPIOB , GPIO_Pin_1);
        GPIO_SetBits(GPIOB , GPIO_Pin_2);	
			 //vTaskDelay(10/portTICK_RATE_MS );
			  vTaskDelay(20);
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
			  vTaskDelay(30);
    }
}

void GPIO_Configuration(void)
{
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOA , &GPIO_InitStructure);
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
