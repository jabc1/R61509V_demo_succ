#include "lcd.h"
void TFT_GPIO()
{
	;
}
void TFT_Init(void)
{
	uint i;
	
	TFT_CS=1;   //关闭片选
	TFT_RD=1;        //IO初始化                                
	TFT_WR=1;        //IO初始化
	
	TFT_RST = 1;
	for(i=500; i>0; i--);
	TFT_RST = 0;
	for(i=500; i>0; i--);
	TFT_RST = 1;
	for(i=5000; i>0; i--);        
	
	TFT_CS =0;  //打开片选使能
	for(i=0; i<500; i++);

    TFT_WriteCmdData(0x0400,0x3102);
    TFT_WriteCmdData(0x0007,0x0021);
    for(i=0; i<5000; i++);
    TFT_WriteCmdData(0x0110,0x0001);
    for(i=0; i<5000; i++);  
    TFT_WriteCmdData(0x0100,0x17B0);
    TFT_WriteCmdData(0x0112,0x0060);
    TFT_WriteCmdData(0x0010,0x001F);
    TFT_WriteCmdData(0x0101,0x0014);
    TFT_WriteCmdData(0x0102,0x019E);
    TFT_WriteCmdData(0x0103,0x3200);
    TFT_WriteCmdData(0x0107,0x0000);
    for(i=0; i<5000; i++);
    TFT_WriteCmdData(0x0102,0x01BE);
    for(i=0; i<5000; i++);  

    TFT_WriteCmdData(0x0001,0x0100);
    TFT_WriteCmdData(0x0002,0x0000);
    TFT_WriteCmdData(0x0003,0x1230);
    TFT_WriteCmdData(0x0008,0x0808); 
    TFT_WriteCmdData(0x0009,0x0000);
    TFT_WriteCmdData(0x000B,0x0010);
    TFT_WriteCmdData(0x000C,0x0000);
    TFT_WriteCmdData(0x0090,0x0000);
    TFT_WriteCmdData(0x0300,0x0706);
    TFT_WriteCmdData(0x0301,0x0206);
    TFT_WriteCmdData(0x0302,0x0002);
    TFT_WriteCmdData(0x0303,0x0201);
    TFT_WriteCmdData(0x0304,0x0300);
    TFT_WriteCmdData(0x0305,0x0207);
    TFT_WriteCmdData(0x0306,0x1416);
    TFT_WriteCmdData(0x0307,0x0706);

    TFT_WriteCmdData(0x0308,0x0206);
    TFT_WriteCmdData(0x0309,0x0002);
    TFT_WriteCmdData(0x030A,0x0201);
    TFT_WriteCmdData(0x030B,0x0300);   
    TFT_WriteCmdData(0x030C,0x0207);
    TFT_WriteCmdData(0x030D,0x090B);
    //gamma
    TFT_WriteCmdData(0x0210,0x0000);
    TFT_WriteCmdData(0x0211,0x00EF);
    TFT_WriteCmdData(0x0212,0x0000);
    TFT_WriteCmdData(0x0213,0x018F);
    TFT_WriteCmdData(0x0401,0x0000);
    TFT_WriteCmdData(0x0404,0x0000);
    TFT_WriteCmdData(0x0010,0x0010);
    TFT_WriteCmdData(0x0011,0x0002);
    TFT_WriteCmdData(0x0012,0x0100);
    TFT_WriteCmdData(0x0101,0x0017);
    TFT_WriteCmdData(0x0200,0x0000);
    TFT_WriteCmdData(0x0201,0x0000);
    TFT_WriteCmd(0x0202);   
    //display on
    TFT_WriteCmdData(0x0007,0x0021);
    for(i=0; i<5000; i++);
    TFT_WriteCmdData(0x0007,0x0061);
    for(i=0; i<5000; i++); 
    TFT_WriteCmdData(0x0007,0x0173);
    for(i=0; i<5000; i++);  
    TFT_WriteCmd(0x0202);   
}






