

#include "stm32f1xx.h"
#include "tft.h"
#include "chinese.h"
#include "char.h"
#include "base.h"

 void delay_ms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<100;j++);
}
/*******************************************************************************
*                              ��ʱ����
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


u16 colors[]=
{
  0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff  //��ɫ����		  �졢�̡������ơ��ڡ���������
};


/**********************************************************

 д�����������Ӻ���

**********************************************************/
void LCD_Write(u8 type, u16 value)

 {
   GPIOB->BRR=0x0001;//  LCD_CS(0);			   //lcdƬѡ�ź�   �͵�ƽ��Ч
   if(type==1)
   		GPIOA->BSRR=0x0100;
	if(type==0)
		GPIOA->BRR=0x0100;
     //LCD_RS(type);		   //ָ����ݼĴ���ѡ�� 
   							//RS=1������
							//RS=0д����
   GPIOB->BRR=0x0004;     //LCD_WR(0);			   //

    GPIOB->BSRR = value & 0xff00;   	  //����
    GPIOB->BRR  = (~value) & 0xff00;	  //�߰�λ����
   GPIOB->BSRR=0x0004;       //LCD_WR(1);			  //��TFTlcdд����
   Delay(100);
   GPIOB->BRR=0x0004;    //LCD_WR(0);
  	GPIOB->BSRR = (value)<<8 & 0xff00;    //����
    GPIOB->BRR  = ((~value)<<8) & 0xff00;//�Ͱ�λ����
   GPIOB->BSRR=0x0004;       //LCD_WR(1);
   Delay(100);
   GPIOB->BSRR=0x0001;//LCD_CS(1);			 //lcdƬѡ�ź�	 �ر�Ƭѡ
  
 }
/**********************************************************

 д16λ�����Ӻ���

**********************************************************/
void LCD_Write_Data16(u16 value)
{	 
    GPIOB->BRR=0x0001;//  LCD_CS(0);						 //lcdƬѡ�ź�
	GPIOA->BSRR=0x0100;//LCD_RS(1);						 //ָ����ݼĴ���ѡ��   //RS=1��д����  
	GPIOB->BRR=0x0004;     //LCD_WR(0);
    GPIOB->BSRR = value & 0xff00;   
    GPIOB->BRR  = (~value) & 0xff00;
    GPIOB->BSRR=0x0004;       //LCD_WR(1);						 //��TFTlcdд����
	Delay(5);
    GPIOB->BRR=0x0004;     //LCD_WR(0);
	GPIOB->BSRR = (value)<<8 & 0xff00;   
    GPIOB->BRR  = ((~value)<<8) & 0xff00;
    GPIOB->BSRR=0x0004;       //LCD_WR(1);						 //��TFTlcdд����
	Delay(5);
    GPIOB->BSRR=0x0001;//LCD_CS(1);						//lcdƬѡ�ź�

}
/*********************************************************

 д�Ĵ����Ӻ���

**********************************************************/
void Reg_Write(u16 reg,u16 value)
{
 LCD_Write(TYPE_LCD_COMMAND,reg);     //�����TYPE_LCD_COMMAND=0��ָ���Ƿ����������Һ����������
 LCD_Write_Data16(value);
 
}
/**********************************************************

������ʾ�����Ӻ���

**********************************************************/
void LCD_SetRamAddr(uint xStart, uint xEnd, uint yStart, uint yEnd) 
{

	Reg_Write(0x200, xStart);  //ˮƽ��ַ
    Reg_Write(0x201, yStart);  //��ֱ��ַ
	//���ڵ�ַ����
    Reg_Write(0x0210, xStart);//����ˮƽRAM��ַ��ʼ��R210h����
    Reg_Write(0x0212,yStart); //����ˮƽRAM��ַ������R211h��
    
    Reg_Write(0x211,xEnd);	  //���ڵĴ�ֱRAM��ַ��ʼ��R212h����
    Reg_Write(0x213,yEnd);	  //���ڵĴ�ֱRAM��ַ������R213h��

	LCD_Write(TYPE_LCD_COMMAND,0x0202);
}




void LCD_Init(void)							 //TFT������ʼ������
{

    GPIOA->BSRR=0x0800; //LCD_RST(1);
    delay_ms(5);	
	GPIOA->BRR=0x0800;  //LCD_RST(0);
	delay_ms(5);
	GPIOA->BSRR=0x0800; //LCD_RST(1);
	delay_ms(5);
	GPIOB->BRR=0x0001;//  LCD_CS(0);  //��Ƭѡʹ��

    Reg_Write(0x000,0x0000);delay_ms(5);
	Reg_Write(0x000,0x0000);delay_ms(5);
	Reg_Write(0x000,0x0000);delay_ms(5);
	Reg_Write(0x000,0x0000);delay_ms(5);
	delay_ms(100);
    LCD_Write_Data16(0x0000);delay_ms(5);
    LCD_Write_Data16(0x0000);delay_ms(5);	
    LCD_Write_Data16(0x0000);delay_ms(5);	
    LCD_Write_Data16(0x0000);delay_ms(5);
  	delay_ms(100);

    Reg_Write(0x400,0x6200);delay_ms(5);
 	Reg_Write(0x008,0x0808);delay_ms(5);

	Reg_Write(0x300,0x0c0c);delay_ms(5);//GAMMA
	Reg_Write(0x301,0xff13);delay_ms(5);
	Reg_Write(0x302,0x0f0f);delay_ms(5);
	Reg_Write(0x303,0x150b);delay_ms(5);

	Reg_Write(0x304,0x1020);delay_ms(5);

	Reg_Write(0x305,0x0a0b);delay_ms(5);
	Reg_Write(0x306,0x0003);delay_ms(5);	
	Reg_Write(0x307,0x0d06);delay_ms(5);
	Reg_Write(0x308,0x0504);delay_ms(5); 
	Reg_Write(0x309,0x1030);delay_ms(5);

	Reg_Write(0x010,0x001b);delay_ms(5);   //60Hz
 	Reg_Write(0x011,0x0101);delay_ms(5);
	Reg_Write(0x012,0x0000);delay_ms(5);
	Reg_Write(0x013,0x0001);delay_ms(5);

	Reg_Write(0x100,0x0330);delay_ms(5);//BT,AP 0x0330
	Reg_Write(0x101,0x0247);delay_ms(5);//DC0,DC1,VC
	Reg_Write(0x103,0x1000);delay_ms(5);//VDV	//0x0f00
	Reg_Write(0x280,0xbf00);delay_ms(5);//VCM
	Reg_Write(0x102,0xd1b0);delay_ms(5);//VRH,VCMR,PSON,PON

	delay_ms(1000);

	Reg_Write(0x001,0x0100);delay_ms(5);
	Reg_Write(0x002,0x0100);delay_ms(5);
	Reg_Write(0x003,0x1030);delay_ms(5);
	Reg_Write(0x009,0x0001);delay_ms(5);
	Reg_Write(0x0C,0x0000);delay_ms(5);	//MCU interface
	Reg_Write(0x090,0x8000);delay_ms(5);
	Reg_Write(0x00f,0x0000);delay_ms(5);


   	Reg_Write(0x210,0x0000);delay_ms(5);
	Reg_Write(0x211,0x00ef);delay_ms(5);
	Reg_Write(0x212,0x0000);delay_ms(5);
	Reg_Write(0x213,0x018f);delay_ms(5);

	Reg_Write(0x500,0x0000);delay_ms(5);
	Reg_Write(0x501,0x0000);delay_ms(5);
	Reg_Write(0x502,0x005f);delay_ms(5);
	Reg_Write(0x401,0x0001);delay_ms(5);
	Reg_Write(0x404,0x0000);delay_ms(5);
	delay_ms(500);

   	Reg_Write(0x0007,0x0100);delay_ms(5);
	delay_ms(1000);

   	Reg_Write(0x200,0x0000);delay_ms(5);
	Reg_Write(0x201,0x0000);delay_ms(5);
    delay_ms(500);
   
  	LCD_Write(TYPE_LCD_COMMAND,0x0202);delay_ms(5);
    delay_ms(500);


}  

/**********************************************************

 �����Ӻ��������ñ�����

**********************************************************/
void  LCD_clear(u8 color)
{
  unsigned int com,seg;	
  LCD_SetRamAddr(0,239, 0,399);
 // delay_ms(100);	
  for(com=0;com<400;com++)
  {
       for(seg=0;seg<240;seg++)
    {
      LCD_Write_Data16(colors[color]);
    }
  }
}
/**********************************************************

  �ַ���ʾ�Ӻ���

**********************************************************/
void LCD_ShowChar(u16 x,u16 y,u16 For_color,u16 Bk_color, char ch)
{

   u8 temp;
   u8 pos,t;
   u8 CHAR_W,CHAR_H;

   CHAR_W = 8;         //8*16  ������ʾ��Ӣ���ַ���СΪ8*16

   CHAR_H = 16;

   if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))		//������С240*400   ��ַ����240*400����
   return;

   LCD_SetRamAddr(x, x+CHAR_W-1, y,y+CHAR_H-1);
   ch = ch-32;                       //����ASCII����˳��ĵ���Ӧ��ĸ�ı���

   for(pos=0;pos<CHAR_H;pos++)  
   {
      temp= Font8x16[ch][pos];
      
      for(t=0;t<CHAR_W;t++)
      {                 
	    if(temp&0x80)
	    LCD_Write_Data16(For_color);  //textcolor
	    else 
	    LCD_Write_Data16(Bk_color);  //backcolor
        temp<<=1; 
      }
	  
   }
}  

/**********************************************************
 ��ʾ�ַ����Ӻ���

 x,y:�������  
 *p:�ַ�����ʼ��ַ

**********************************************************/

void LCD_ShowString(u16  x,u16 y,u16 For_color,u16 Bk_color,char *p)
{         
   while(*p!='\0')
   {       
     LCD_ShowChar(x,y,For_color,Bk_color,*p);
     x+=8;
     p++;
   }
}



/**********************************************************

  д�����Ӻ���

**********************************************************/
void ChineseChar(u16 x,u16  y,u16  size,u16  For_color,u16  Bk_color ,char c)
{
   int e=0,i,j;
   int  ed;
   
   u16  ncols;	    //���庺�ֵ�����
   u16  nrows;		//���庺�ֵ�����
   u16  nbytes;	    //������ʾһ��������ռ���ֽ���

   u8 *pfont;
   u8 *pchar;
   u8 *fonttable[]={(u8 *)hz16,(u8 *)hz16,(u8 *)hz24};	  //����ͬ��ģ����׵�ַ
                                                                  //����һ��ָ�������ˣ��������
   
   pfont=(u8 *)fonttable[size];									  //����ѡ������壬ȥ���ò�ͬ��С����ģ����
                           										  // ��������� hz12��ַ��hz16��ַ��hz24��ַ

   if(size==0)         //sizeΪ0ʱ��ʾhz12���еĺ���
   {
     ncols =12-1;	   //-1 ԭ�����±��0��ʼ��0~11 ��12����������-1ԭ�������
     nrows =12-1;
     nbytes =24;	  //ȡģ�ֽ��� 12*12/8 һ����24���ֽ� 24���ֽ�ֻ����ʾ��ɫ��
   }
   else
   if(size==1)		  //size Ϊ1ʱ��ʾhz16�еĵ�ַ
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;  	  //16*16/8 =32���ֽڣ���ɫ��
   }
   else
   if(size==2)		   //size Ϊ2ʱ��ʾhz24�еĵ�ַ
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;   
   }
   
   pchar=pfont + (nbytes*(c-1));   //ִ�����󣬰���Ӧ�ַ����׵�ַ�͸�pchar,
                                   

   LCD_SetRamAddr(x, x+nrows, y,y+ncols); //�����ֵ���ʼ���꼰��������
   
   for(i=0;i<nbytes;i++)		  //��ʼ����������
   {
     ed=*pchar++;				  // �����͸�ed������ed�е�����׼���͵�����
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else						  
	 e=8;
     
     for(j=0;j<e;j++)
     if((ed>>j)&0x01)
     {
       LCD_Write_Data16(For_color);  //textcolor
	 }
     else
     {
       LCD_Write_Data16(Bk_color);  //backcolor
	 }
  }
}

/*********************************************************/



























