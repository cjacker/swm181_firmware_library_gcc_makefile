/****************************************************************************************************************************************** 
* 文件名称: SWM181_timr.c
* 功能说明:	SWM181单片机的计数器/定时器功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期:	V1.0.0		2016年1月30日
* 升级记录: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology 
*******************************************************************************************************************************************/
#include "SWM181.h"
#include "SWM181_timr.h"


/****************************************************************************************************************************************** 
* 函数名称: TIMR_Init()
* 功能说明:	TIMR定时器/计数器初始化
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，有效值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t mode			TIMR_MODE_TIMER 定时器模式    TIMR_MODE_COUNTER 计数器模式
*			uint32_t period			定时/计数周期
*			uint32_t int_en			中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint32_t period, uint32_t int_en)
{
	SYS->CLKEN |= (0x01 << SYS_CLKEN_TIMR_Pos);
	
	TIMR_Stop(TIMRx);	//一些关键寄存器只能在定时器停止时设置
	
	TIMRx->CTRL &= ~TIMR_CTRL_CLKSRC_Msk;
	TIMRx->CTRL |= mode << TIMR_CTRL_CLKSRC_Pos;
	
	TIMRx->LDVAL = period;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMR_INTClr(TIMR0);
		TIMRG->IE &= ~TIMRG_IE_TIMR0_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMR_INTClr(TIMR1);
		TIMRG->IE &= ~TIMRG_IE_TIMR1_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMR_INTClr(TIMR2);
		TIMRG->IE &= ~TIMRG_IE_TIMR2_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMR_INTClr(TIMR3);
		TIMRG->IE &= ~TIMRG_IE_TIMR3_Msk;
		TIMRG->IE |= (int_en << TIMRG_IE_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Start()
* 功能说明:	启动定时器，从初始值开始计时/计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Start(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL |= (1 << TIMR_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Stop()
* 功能说明:	停止定时器
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Stop(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL &= ~(1 << TIMR_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Halt()
* 功能说明:	暂停定时器，计数值保持不变
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Halt(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Resume()
* 功能说明:	恢复定时器，从暂停处继续计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Resume(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_SetPeriod()
* 功能说明:	设置定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t period			定时/计数周期
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_SetPeriod(TIMR_TypeDef * TIMRx, uint32_t period)
{
	TIMRx->LDVAL = period;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_GetPeriod()
* 功能说明:	获取定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				当前定时/计数周期
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetPeriod(TIMR_TypeDef * TIMRx)
{
	return TIMRx->LDVAL; 
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_GetCurValue()
* 功能说明:	获取当前计数值
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx)
{
	return TIMRx->CVAL;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTEn()
* 功能说明:	使能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IE |= (0x01 << TIMRG_IE_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTDis()
* 功能说明:	禁能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IE &= ~(0x01 << TIMRG_IE_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTClr()
* 功能说明:	清除中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF = (0x01 << TIMRG_IF_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTStat()
* 功能说明:	获取中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 TIMRx未产生中断    1 TIMRx产生了中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		return (TIMRG->IF & TIMRG_IF_TIMR0_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR1):
		return (TIMRG->IF & TIMRG_IF_TIMR1_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR2):
		return (TIMRG->IF & TIMRG_IF_TIMR2_Msk) ? 1 : 0;
	
	case ((uint32_t)TIMR3):
		return (TIMRG->IF & TIMRG_IF_TIMR3_Msk) ? 1 : 0;
	}
	
	return 0;
}
