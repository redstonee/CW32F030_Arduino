
#include "interrupt.h"
#include "cw32yyxx_gpio.h"

#if !defined(EXTI_MODULE_DISABLED)

/*As we can have only one interrupt/pin id, don't need to get the port info*/
typedef struct {
  IRQn_Type irqnb;
  void (*callback)(void);
} gpio_irq_conf_str;

/* Private_Defines */
#ifdef CW32F030
#define NB_NVIC_GPIO   (4) 
#endif

#ifdef CW32F030
#define NB_INT_GPIO (16)
#endif


/* Private Variables */
static gpio_irq_conf_str gpio_irq_conf[NB_NVIC_GPIO] = {
#if defined (CW32F030)
  {.irqnb = GPIOA_IRQn,   .callback = NULL}, //GPIO_PIN_0
  {.irqnb = GPIOB_IRQn,   .callback = NULL}, //GPIO_PIN_1
  {.irqnb = GPIOC_IRQn,   .callback = NULL}, //GPIO_PIN_2
  {.irqnb = GPIOE_IRQn,   .callback = NULL}, //GPIO_PIN_3
#endif
};

uint32_t GPIOA_Pins[]={
  CW_GPIOA
};

/* Private Functions */
/**
  * @brief  This function returns the pin ID function of the HAL PIN definition
  * @param  pin : one of the gpio pin
  * @retval None
  */
static uint8_t get_pin_id(uint16_t pin)
{
  uint8_t id = 0;

  while (pin != 0x0001) {
    pin = pin >> 1;
    id++;
  }

  return id;
}

void cw32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, void (*callback)(void), uint32_t trigger_mode)
{
    GPIO_InitTypeDef GPIO_InitStruct={0};
    EXTI_InitTypeDef EXTI_InitStruct={0};
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    uint8_t id = get_pin_id(port);
    uint8_t gpio_port_souce=0;
    GPIO_InitStruct.GPIO_Pin  = pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.GPIO_Speed = trigger_mode;

    GPIO_Init(port, &GPIO_InitStruct);

    gpio_irq_conf[id].callback = callback;

    NVIC_EnableIRQ(gpio_irq_conf[port].irqnb);
}


/**
  * @brief  This function disable the interruption on the selected port/pin
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval None
  */
void ch32_interrupt_disable(GPIO_TypeDef *port, uint16_t pin)
{
  uint8_t id = get_pin_id(pin);
  gpio_irq_conf[id].callback = NULL;

  for (int i = 0; i < NB_EXTI; i++) {
    if (gpio_irq_conf[id].irqnb == gpio_irq_conf[i].irqnb
        && gpio_irq_conf[i].callback != NULL) {
      return;
    }
  }
  NVIC_DisableIRQ(gpio_irq_conf[id].irqnb);  
}

/**
  * @brief This function his called by the HAL if the IRQ is valid
  * @param  GPIO_Pin : one of the gpio pin
  * @retval None
  */
void _gpio_exti_callback(uint16_t GPIO_Pin)
{
  uint8_t irq_id = get_pin_id(GPIO_Pin);
  if (gpio_irq_conf[irq_id].callback != NULL) {
    gpio_irq_conf[irq_id].callback();
  }
}



#if defined(CH32V00x)

#ifdef __cplusplus
extern "C" {
#endif

void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI7_0_IRQHandler(void)
{
   uint32_t pin;
   for (pin = GPIO_Pin_0; pin <= GPIO_Pin_7; pin = pin << 1) 
   {
      EXTI_ClearITPendingBit(pin);   //0x1 2 4 8 10 20 40 80
      _gpio_exti_callback(pin);
   }
}
#ifdef __cplusplus
}
#endif


#elif defined(CH32X035)


#ifdef __cplusplus
extern "C" {
#endif

void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI15_8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI25_16_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void EXTI7_0_IRQHandler(void)
{
   uint32_t pin;
   for (pin = GPIO_Pin_0; pin <= GPIO_Pin_7; pin = pin << 1) 
   {
      EXTI_ClearITPendingBit(pin);   //0x1 2 4 8 10 20 40 80
      _gpio_exti_callback(pin);
   }
}

void EXTI15_8_IRQHandler(void)
{
   uint32_t pin;
   for (pin = GPIO_Pin_8; pin <= GPIO_Pin_15; pin = pin << 1) 
   {
      EXTI_ClearITPendingBit(pin);   //0x1 2 4 8 10 20 40 80
      _gpio_exti_callback(pin);
   }
}

void EXTI25_16_IRQHandler(void)
{
   uint32_t pin;
   for (pin = GPIO_Pin_16; pin <= GPIO_Pin_23; pin = pin << 1) 
   {
      EXTI_ClearITPendingBit(pin);   //0x1 2 4 8 10 20 40 80
      _gpio_exti_callback(pin);
   }
}


#ifdef __cplusplus
}
#endif


#else

#ifdef __cplusplus
extern "C" {
#endif

void GPIOA_IRQHandlerCallback(void);
void GPIOB_IRQHandlerCallback(void);
void GPIOC_IRQHandlerCallback(void);
void GPIOF_IRQHandlerCallback(void);

void GPIOA_IRQHandlerCallback(void){
  if (CW_GPIOA->ISR_f.PIN1)
  {
    CW_GPIOA->ICR_f.PIN1 = 0; // 清中断标志位
    gpio_irq_conf[0].callabck();
  }
}


#ifdef __cplusplus
}
#endif

#endif  /* CH32V00x */

#endif /* EXTI_MODULE_ENABLED */



