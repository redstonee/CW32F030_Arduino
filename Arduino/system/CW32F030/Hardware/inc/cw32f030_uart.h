/*******************************************************************************
*
* �������ɺ�������Ϣ
* �人оԴ�뵼�����޹�˾������ʹ�����б�̴���ʾ���ķ�ר���İ�Ȩ���ɣ��������ɴ�
* ���ɸ��������ض���Ҫ�����Ƶ����ƹ��ܡ����ݲ��ܱ��ų����κη�����֤���人оԴ��
* �������޹�˾������򿪷��̺͹�Ӧ�̶Գ������֧�֣�����У����ṩ�κ���ʾ��
* ���ı�֤�������������������ڰ������й������ԡ�������ĳ���ض���;�ͷ���Ȩ�ı�֤
* ��������
* ���ۺ������Σ��人оԴ�뵼�����޹�˾������򿪷��̻�Ӧ�̾��������и����
* ��ʹ����֪�䷢���Ŀ�����ʱ��Ҳ����ˣ����ݵĶ�ʧ���𻵣�ֱ�ӵġ��ر�ġ�������
* ���ӵ��𺦣����κκ���Ծ����𺦣�������ҵ�����롢������Ԥ�ڿɽ�ʡ����
* ��ʧ��
* ĳЩ˾��Ͻ����������ֱ�ӵġ������Ļ����Ե������κε��ų������ƣ����ĳЩ��
* ȫ�������ų������ƿ��ܲ�������������
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F030_UART_H
#define __CW32F030_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/ 
 
 /** 
  * @brief  USART Init Structure definition  
  */ 
  
typedef struct
{
  uint32_t USART_BaudRate;            /*!< ������
                                           ���㹫ʽ:
                                            - USART_Over = 00�� BaudRate = UCLK / (16 * BRRI + BRRF)
                                            - USART_Over = 01�� BaudRate = UCLK / (8 * BRRI)
                                            - USART_Over = 10�� BaudRate = UCLK / (4 * BRRI)
                                            - USART_Over = 11�� BaudRate = (256 * UCLK) / BRRI */

  uint16_t USART_Over;                /*!< ������ʽ
                                           ����ȡֵ @ref USART_Over */

  uint16_t USART_Source;              /*!< ����ʱ��ԴUCLK
                                           ����ȡֵ @ref USART_Source */

  uint32_t USART_UclkFreq;            /*!< ����ʱ��UCLKƵ�� Hz */                                 

  uint16_t USART_StartBit;            /*!< ��ʼλ�ж���ʽ
                                           ����ȡֵ @ref USART_Start_Bit */
    
  uint16_t USART_StopBits;            /*!< ֹͣλ����
                                           ����ȡֵ @ref USART_Stop_Bits */

  uint16_t USART_Parity;              /*!< У�鷽ʽ
                                           ����ȡֵ @ref USART_Parity
                                           @note ������Ϊ��У��ʱ�������ֳ�Ϊ8λ��
                                                 ������Ϊ��У��ʱ�������ֳ��Զ�����Ϊ9λ */
 
  uint16_t USART_Mode;                /*!< ����/����ʹ��
                                           ����ȡֵ @ref USART_Mode */

  uint16_t USART_HardwareFlowControl; /*!< Ӳ������
                                           ����ȡֵ @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;
 
/** 
  * @brief  USART Clock Init Structure definition  
  */ 
  
typedef struct
{
  uint16_t USART_Clock;   /*!< USARTͬ��ģʽʹ��/ʧ��
                               ����ȡֵ @ref USART_Clock */

  uint16_t USART_Source;  /*!< ����ʱ��ԴUCLK
                               ����ȡֵ @ref USART_Source */                     
} USART_ClockInitTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/

/** @defgroup USART_Over
  * @{
  */ 
  
#define USART_Over_16                        ((uint16_t)0x0000)
#define USART_Over_8                         ((uint16_t)0x0200)
#define USART_Over_4                         ((uint16_t)0x0400)
#define USART_Over_sp                        ((uint16_t)0x0600)
#define IS_USART_Over(Over) (((Over) == USART_Over_16) || \
                             ((Over) == USART_Over_8)  || \
                             ((Over) == USART_Over_4)  || \
                             ((Over) == USART_Over_sp))

/** @defgroup USART_Source
  * @{
  */ 
  
#define USART_Source_PCLK                    ((uint16_t)0x0000)
#define USART_Source_LSE                     ((uint16_t)0x0200)
#define USART_Source_LSI                     ((uint16_t)0x0300)
#define IS_USART_Source(Source) (((Source) == USART_Source_PCLK) || \
                                 ((Source) == USART_Source_LSE)  || \
                                 ((Source) == USART_Source_LSI))

/** @defgroup USART_Start_Bit 
  * @{
  */ 
  
#define USART_StartBit_FE                    ((uint16_t)0x0000) //RXD�½���
#define USART_StartBit_LL                    ((uint16_t)0x0100) //RXD�͵�ƽ
#define IS_USART_StartBit(StartBit) (((StartBit) == USART_StartBit_FE) || \
                                     ((StartBit) == USART_StartBit_LL))

/** @defgroup USART_Stop_Bits 
  * @{
  */ 
  
#define USART_StopBits_1                     ((uint16_t)0x0000)
#define USART_StopBits_2                     ((uint16_t)0x0020)
#define USART_StopBits_1_5                   ((uint16_t)0x0010)
#define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
                                     ((STOPBITS) == USART_StopBits_2) || \
                                     ((STOPBITS) == USART_StopBits_1_5))

/** @defgroup USART_Parity 
  * @{
  */ 
  
#define USART_Parity_No                      ((uint16_t)0x0000)
#define USART_Parity_Even                    ((uint16_t)0x0008)
#define USART_Parity_Odd                     ((uint16_t)0x000C) 
#define USART_Parity_User                    ((uint16_t)0x0004) 
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No)   || \
                                 ((PARITY) == USART_Parity_Even) || \
                                 ((PARITY) == USART_Parity_Odd)  || \
                                 ((PARITY) == USART_Parity_User))

/** @defgroup USART_Mode 
  * @{
  */ 
  
#define USART_Mode_Tx                        ((uint16_t)0x0001)
#define USART_Mode_Rx                        ((uint16_t)0x0002)
#define IS_USART_MODE(MODE) ((((MODE) & (uint16_t)0xFFFC) == 0x00) && ((MODE) != (uint16_t)0x00))

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 

#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0008)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0004)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x000C)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == USART_HardwareFlowControl_None) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS)  || \
                               ((CONTROL) == USART_HardwareFlowControl_CTS)  || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))

/** @defgroup USART_Clock 
  * @{
  */ 

#define USART_Clock_Disable                  ((uint16_t)0x0000)
#define USART_Clock_Enable                   ((uint16_t)0x0040)
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
                               ((CLOCK) == USART_Clock_Enable))                      

/** @defgroup USART_Inversion_Pins 
  * @{
  */

#define USART_InvPin_Tx                      ((uint16_t)0x0020)
#define USART_InvPin_Rx                      ((uint16_t)0x0010)
#define IS_USART_INVERSTION_PIN(INVPIN) ((((INVPIN) & (uint16_t)0xFFCF) == 0x00) && ((INVPIN) != (uint16_t)0x00)) 

/** @defgroup USART_DMA_Requests 
  * @{
  */

#define USART_DMAReq_Tx                      ((uint16_t)0x0080)
#define USART_DMAReq_Rx                      ((uint16_t)0x0040)
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFF3F) == 0x00) && ((DMAREQ) != (uint16_t)0x00))                     

/** @defgroup USART_Interrupt
  * @{
  */
  
#define USART_IT_CTS                         ((uint16_t)0x0040)
#define USART_IT_PE                          ((uint16_t)0x0010)
#define USART_IT_FE                          ((uint16_t)0x0008)
#define USART_IT_RC                          ((uint16_t)0x0004)
#define USART_IT_TC                          ((uint16_t)0x0002)
#define USART_IT_TXE                         ((uint16_t)0x0001)
#define IS_USART_IT(IT) ((((IT) & (uint16_t)0xFFA0) == 0x00) && ((IT) != (uint16_t)0x00))
#define IS_USART_CLEAR_IT(IT) ((((IT) & (uint16_t)0xFFA1) == 0x00) && ((IT) != (uint16_t)0x00))

/** @defgroup USART_Flags  
  * @{
  */

#define USART_FLAG_TXBUSY                    ((uint16_t)0x0100)
#define USART_FLAG_CTSLV                     ((uint16_t)0x0080)
#define USART_FLAG_CTS                       ((uint16_t)0x0040)
#define USART_FLAG_MATCH                     ((uint16_t)0x0020)
#define USART_FLAG_PE                        ((uint16_t)0x0010)
#define USART_FLAG_FE                        ((uint16_t)0x0008)
#define USART_FLAG_RC                        ((uint16_t)0x0004)
#define USART_FLAG_TC                        ((uint16_t)0x0002)
#define USART_FLAG_TXE                       ((uint16_t)0x0001)
#define IS_USART_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFE00) == 0x00) && ((FLAG) != (uint16_t)0x00))
#define IS_USART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFFA1) == 0x00) && ((FLAG) != (uint16_t)0x00)) 

#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) <= 0x00F42400))
#define IS_USART_UCLKFREQ(UCLKFREQ) (((UCLKFREQ) > 0) && ((UCLKFREQ) <= 0x03D09000))
#define IS_USART_DATA_16BIT(DATA) ((DATA) <= 0x1FF)
#define IS_USART_DATA_8BIT(DATA) ((DATA) <= 0xFF)
#define IS_USART_ADDRESS(ADDRESS) ((ADDRESS) <= 0xFF)
#define IS_USART_ADDRESSMSK(ADDRESSMSK) ((ADDRESSMSK) <= 0xFF)
#define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == CW_UART1) || \
                                     ((PERIPH) == CW_UART2) || \
                                     ((PERIPH) == CW_UART3))
 
 /******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
 
 /******************************************************************************
 * Global function prototypes 
 ******************************************************************************/

/* �����շ� */
void USART_SendData(USART_TypeDef* UARTx, uint16_t Data);
void USART_SendData_8bit(USART_TypeDef* UARTx, uint8_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
uint8_t USART_ReceiveData_8bit(USART_TypeDef* USARTx);

/* ��ʼ�� */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void UART1_DeInit(void);
void UART2_DeInit(void);
void UART3_DeInit(void);

/* �жϼ���־ */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);

/* ���ͺͽ��տ��� */
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint16_t USART_DirectionMode, FunctionalState NewState);
void USART_InvPinCmd(USART_TypeDef* USARTx, uint16_t USART_InvPin, FunctionalState NewState);

/* ��˫��ͨ�� */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* DMA */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);

/* ���ͨ�� */
void USART_SetMultiMode(USART_TypeDef* USARTx, uint8_t USART_Address, uint8_t USART_AddressMsK);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_UART_H */
/**
  * @}
  */ 
