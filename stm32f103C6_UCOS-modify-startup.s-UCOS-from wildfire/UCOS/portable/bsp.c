#include "os.h"
#include "stm32f10x.h"

CPU_INT32U  BSP_CPU_ClkFreq_MHz;

#define  DWT_CR      *(CPU_REG32 *)0xE0001000
#define  DWT_CYCCNT  *(CPU_REG32 *)0xE0001004
#define  DEM_CR      *(CPU_REG32 *)0xE000EDFC
#define  DBGMCU_CR   *(CPU_REG32 *)0xE0042004

#define  DBGMCU_CR_TRACE_IOEN_MASK       0x10
#define  DBGMCU_CR_TRACE_MODE_ASYNC      0x00
#define  DBGMCU_CR_TRACE_MODE_SYNC_01    0x40
#define  DBGMCU_CR_TRACE_MODE_SYNC_02    0x80
#define  DBGMCU_CR_TRACE_MODE_SYNC_04    0xC0
#define  DBGMCU_CR_TRACE_MODE_MASK       0xC0

#define  DEM_CR_TRCENA                   (1 << 24)

#define  DWT_CR_CYCCNTENA                (1 <<  0)


CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;


    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}

#if 0
void  BSP_LED_Toggle (CPU_INT08U led)
{
    CPU_INT32U  pins;


    switch (led) {
        case 0:
             pins =  GPIO_ReadOutputData(GPIOD);
             pins ^= BSP_GPIOD_LEDS;
             GPIO_SetBits(  GPIOD,   pins  & BSP_GPIOD_LEDS);
             GPIO_ResetBits(GPIOD, (~pins) & BSP_GPIOD_LEDS);
             break;

        case 1:
        case 2:
        case 3:
            pins = GPIO_ReadOutputData(GPIOD);
            if ((pins & (1 << (led + BSP_LED_START_BIT))) == 0) {
                 GPIO_SetBits(  GPIOD, (1 << (led + BSP_LED_START_BIT)));
             } else {
                 GPIO_ResetBits(GPIOD, (1 << (led + BSP_LED_START_BIT)));
             }
            break;

        default:
             break;
    }
}

#endif

CPU_BOOLEAN  BSP_StatusRd (CPU_INT08U  id)
{
    CPU_BOOLEAN  bit_val;


    switch (id) {
        case 1:
             bit_val = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
             return (bit_val);

        default:
             return ((CPU_BOOLEAN)DEF_OFF);
    }
}

#if ((APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN          == 1))
void  OSProbe_TmrInit (void)
{
}
#endif


#if ((APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN          == 1))
CPU_INT32U  OSProbe_TmrRd (void)
{
    return ((CPU_INT32U)DWT_CYCCNT);
}
#endif

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{
    CPU_INT32U  cpu_clk_freq_hz;


    DEM_CR         |= (CPU_INT32U)DEM_CR_TRCENA;                /* Enable Cortex-M3's DWT CYCCNT reg.                   */
    DWT_CYCCNT      = (CPU_INT32U)0u;
    DWT_CR         |= (CPU_INT32U)DWT_CR_CYCCNTENA;

    cpu_clk_freq_hz = BSP_CPU_ClkFreq();
    CPU_TS_TmrFreqSet(cpu_clk_freq_hz);
}
#endif

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    return ((CPU_TS_TMR)DWT_CYCCNT);
}
#endif



