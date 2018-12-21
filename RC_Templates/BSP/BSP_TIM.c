#include "BSP_TIM.h"

void BSP_TIM1PWMOutput(u16 prescaler, u16 period, u16 Pulse)
{
	//IO初始化
//	TIM1_GPIOInit();
	
	//使能定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  
	/* 配置时基结构体 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/*配置输出比较结构体*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出低电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	
	//使能定时器
	TIM_Cmd(TIM1, ENABLE);
	
	/* 高级定时器需要使能PWM输出 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}


