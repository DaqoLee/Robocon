#include "BSP_TIM.h"

void BSP_TIM1PWMOutput(u16 prescaler, u16 period, u16 Pulse)
{
	//IO��ʼ��
//	TIM1_GPIOInit();
	
	//ʹ�ܶ�ʱ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  
	/* ����ʱ���ṹ�� */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//���ö�ʱ��ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Period = period;
	//��������ʱ��������˲���Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//���ü���ģʽ�����ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/*��������ȽϽṹ��*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//�������ģʽ��PWM1ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//ʹ�����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//��ʹ�ܻ������
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//����PWM���ԣ���ʼ��ƽΪ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//���ÿ���ʱ�����ƽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	//���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//���û����������ʱ����͵�ƽ(����ҲҪ���ã�����������ܳ���)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);
	
	/* �߼���ʱ����Ҫʹ��PWM��� */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}


