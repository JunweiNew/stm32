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
#include "os.h"
#include <stdio.h>


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

#define START_TASK_PRIO     3
#define START_STK_SIZE      64

#define LED0_TASK_PRIO      30
#define LED0_STK_SIZE       64

#define LED1_TASK_PRIO      31
#define LED1_STK_SIZE       64

OS_TCB taskStartTCB;
CPU_STK startTaskStk[START_STK_SIZE];

OS_TCB task1TCB;
CPU_STK task1_stk[LED0_STK_SIZE];

OS_TCB task2TCB;
CPU_STK task2_stk[LED1_STK_SIZE];

OS_ERR err;

void StartTask(void *pvParameters);
void led0_task(void *pvParameters);
void led1_task(void *pvParameters);

void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<500;j++)
		{;}
	}
}

void RCC_Configuration(void);

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
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_Configuration();
//	SysTick_Config(7200);
//	OS_CPU_SysTickInit(10);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  /* Configure PB0 to PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA , GPIO_Pin_1);
	GPIO_SetBits(GPIOA , GPIO_Pin_2);
	
	GPIO_SetBits(GPIOB , GPIO_Pin_0);
	GPIO_SetBits(GPIOB , GPIO_Pin_1);
	GPIO_SetBits(GPIOB , GPIO_Pin_2);	
	GPIO_SetBits(GPIOB , GPIO_Pin_3);
	GPIO_SetBits(GPIOB , GPIO_Pin_4);
	GPIO_SetBits(GPIOB , GPIO_Pin_5);	
	GPIO_SetBits(GPIOB , GPIO_Pin_6);
	GPIO_SetBits(GPIOB , GPIO_Pin_7);
	GPIO_SetBits(GPIOB , GPIO_Pin_8);
	GPIO_SetBits(GPIOB , GPIO_Pin_9);	
	GPIO_SetBits(GPIOB , GPIO_Pin_10);
	GPIO_SetBits(GPIOB , GPIO_Pin_11);
	GPIO_SetBits(GPIOB , GPIO_Pin_12);	
	GPIO_SetBits(GPIOB , GPIO_Pin_13);	
	GPIO_SetBits(GPIOB , GPIO_Pin_14);	
	GPIO_SetBits(GPIOB , GPIO_Pin_15);	
	
	OSInit(&err);

//	OSSchedRoundRobinCfg((CPU_BOOLEAN )DEF_ENABLED, (OS_TICK )10, (OS_ERR *)&err ); 

	OSTaskCreate((OS_TCB     *)&taskStartTCB,
							 (CPU_CHAR   *)"task_start",
							 (OS_TASK_PTR )StartTask,
							 (void       *)NULL,
							 (OS_PRIO     )START_TASK_PRIO,
							 (CPU_STK    *)&startTaskStk[0],
							 (CPU_STK_SIZE)START_STK_SIZE / 10,
							 (CPU_STK_SIZE)START_STK_SIZE,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )0,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
							 (OS_ERR     *)&err);

	OSStart(&err);   
}

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;

    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}

void StartTask(void *pvParameters)
{
	OSTaskCreate((OS_TCB     *)&task1TCB,
							 (CPU_CHAR   *)"led0_task",
							 (OS_TASK_PTR )led0_task,
							 (void       *)NULL,
							 (OS_PRIO     )LED0_TASK_PRIO,
							 (CPU_STK    *)&task1_stk[0],
							 (CPU_STK_SIZE)LED0_STK_SIZE / 10,
							 (CPU_STK_SIZE)LED0_STK_SIZE,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )1,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
							 (OS_ERR     *)&err);
	
	OSTaskCreate((OS_TCB     *)&task2TCB,
							 (CPU_CHAR   *)"led1_task",
							 (OS_TASK_PTR )led1_task,
							 (void       *)NULL,
							 (OS_PRIO     )LED1_TASK_PRIO,
							 (CPU_STK    *)&task2_stk[0],
							 (CPU_STK_SIZE)LED1_STK_SIZE / 10,
							 (CPU_STK_SIZE)LED1_STK_SIZE,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )1,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
							 (OS_ERR     *)&err);		
		
							 
    OSTaskDel((OS_TCB     *)&taskStartTCB, 
              (OS_ERR     *)&err);							 
}
#if 0
void led0_task(void *pvParameters)
{
    while(1)
    {
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
delay();
//			OSTimeDly((OS_TICK    )1000, 
//			  (OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
//			OSTimeDly(200, OS_OPT_TIME_DLY, &err);		
			//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
			
			
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			GPIO_SetBits(GPIOB , GPIO_Pin_2);	

//			OSTimeDly((OS_TICK    )1000, 
//				(OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
			delay();    
			OSSched();  
//				OSTimeDly(200, OS_OPT_TIME_DLY, &err);		
			//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
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

			
//			OSTimeDly((OS_TICK    )1000, 
//				(OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
				delay();
//			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
//			OSTimeDly(200, OS_OPT_TIME_DLY, &err);		
			GPIO_ResetBits(GPIOA , GPIO_Pin_2);

			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			GPIO_SetBits(GPIOB , GPIO_Pin_4);
			GPIO_SetBits(GPIOB , GPIO_Pin_5);	
			GPIO_SetBits(GPIOB , GPIO_Pin_6);
			
//			OSTimeDly((OS_TICK    )1000, 
//				(OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
					delay();    
//			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
//			OSTimeDly(200, OS_OPT_TIME_DLY, &err);	
OSSched();  
    }
}
#endif

void led0_task(void *pvParameters)
{
	  int value = 0;
	
    while(1)
    {
			value = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0);
			if(value == 0)
			{
				GPIO_SetBits(GPIOB , GPIO_Pin_0);
				GPIO_SetBits(GPIOB , GPIO_Pin_1);
				GPIO_SetBits(GPIOB , GPIO_Pin_2);				
			}
				
			if(value == 1)
			{
				GPIO_ResetBits(GPIOB , GPIO_Pin_0);
				GPIO_ResetBits(GPIOB , GPIO_Pin_1);
				GPIO_ResetBits(GPIOB , GPIO_Pin_2);			
			}

//			OSTimeDly((OS_TICK    )1000, 
//			  (OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
			OSTimeDly(500, OS_OPT_TIME_DLY, &err);		
			//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void led1_task(void *pvParameters)
{
	  int value = 0;
	
    while(1)
    {			
			value = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_3);
			if(value == 0)
			{
				GPIO_SetBits(GPIOB , GPIO_Pin_3);
				GPIO_SetBits(GPIOB , GPIO_Pin_4);
				GPIO_SetBits(GPIOB , GPIO_Pin_5);	
				GPIO_SetBits(GPIOB , GPIO_Pin_6);			
			}
			if(value == 1)
			{
				GPIO_ResetBits(GPIOB , GPIO_Pin_3);
				GPIO_ResetBits(GPIOB , GPIO_Pin_4);
				GPIO_ResetBits(GPIOB , GPIO_Pin_5);	
				GPIO_ResetBits(GPIOB , GPIO_Pin_6);				
			}

//			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
			OSTimeDly(500, OS_OPT_TIME_DLY, &err);		

//			OSTimeDly((OS_TICK    )1000, 
//				(OS_OPT     )OS_OPT_TIME_PERIODIC, 
//				(OS_ERR    *)&err);
    }
}


void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;

  	RCC_DeInit();

  	RCC_HSEConfig(RCC_HSE_ON);

  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
  	if(HSEStartUpStatus == SUCCESS)
  	{
    	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    	RCC_PCLK2Config(RCC_HCLK_Div1); 

    	RCC_PCLK1Config(RCC_HCLK_Div2);

    	FLASH_SetLatency(FLASH_Latency_2);

    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    	RCC_PLLCmd(ENABLE);

    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
   
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
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
