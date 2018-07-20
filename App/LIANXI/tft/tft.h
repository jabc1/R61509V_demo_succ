#ifndef __TFT_H_
#define __TFT_H_	 		    
#include "sys.h"
#include "base.h"
#define uchar unsigned char 
#define uint unsigned int
/*
#define LCD_RST_PIN PAout(11)//   GPIO_Pin_11	 //RST ��Ӧ��Ƭ�����Ŷ��� P3^3 / ��ӦSTM32�� PA11

#define LCD_RD_PIN PBout(1)   // GPIO_Pin_1	 //RD  ��Ӧ��Ƭ�����Ŷ��� P2^6 / ��ӦSTM32�� PB1

#define LCD_WR_PIN PBout(2)   // GPIO_Pin_2	 //WR  ��Ӧ��Ƭ�����Ŷ��� P2^5 / ��ӦSTM32�� PB2

#define LCD_RS_PIN PAout(8)  //  GPIO_Pin_8   //RS  ��Ӧ��Ƭ�����Ŷ��� P3^2 / ��ӦSTM32�� PA8
							 
#define LCD_CS_PIN PBout(0)   // GPIO_Pin_0	 //CS  ��Ӧ��Ƭ�����Ŷ��� P2^7 / ��ӦSTM32�� PB0


#define LCD_RST(x) x ? GPIOA->BSRR=0x0800 : GPIOA->BRR=0x0800 //�Լ�����λ��������
#define LCD_RD(x) x ? GPIOB->BSRR=0x0002 : GPIOB->BRR=0x0002
#define LCD_WR(x) x ? GPIOB->BSRR=0x0004 : GPIOB->BRR=0x0004
#define LCD_RS(x) x ? GPIOA->BSRR=0x0001 : GPIOA->BRR=0x0001
#define LCD_CS(x)  x ? GPIOB->BSRR=0x0001 : GPIOB->BRR=0x0001*/	  



#define  TYPE_LCD_DATA		1
#define  TYPE_LCD_COMMAND	0
#define  LCD_SIZE_X		240		 
#define  LCD_SIZE_Y		400		   

extern  u16 colors[];

void delay_ms(int count);
void LCD_Init(void);
void LCD_ShowString(u16 x,u16 y,u16 For_color,u16 Bk_color,char *p);
void LCD_ShowChar(u16 x,u16 y,u16 For_color,u16 Bk_color, char ch);
void ChineseChar(u16 x,u16 y,u16 size,u16 For_color,u16 Bk_color ,char c);
void Delay(vu32 nCount);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void  LCD_clear(u8 color);


#endif


