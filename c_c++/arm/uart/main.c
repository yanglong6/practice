#define GPX1CON 	(*(volatile unsigned int *)0x11400020)
#define ULCON2  	(*(volatile unsigned int *)0x13820000)
#define UCON2   	(*(volatile unsigned int *)0x13820004)
#define UBRDIV2 	(*(volatile unsigned int *)0x13820028)
#define UFRACVAL2 	(*(volatile unsigned int *)0x1382002C)
#define UTXH2	 	(*(volatile unsigned int *)0x13820020)
#define UTRSTAT2	(*(volatile unsigned int *)0x13820010)
#define URXH2		(*(volatile unsigned int *)0x13820024)

void uart_init()
{
	//1. 外: 配置通用GPIO口
	GPX1CON = 0x22; //set gpx1_1 uart mode

	//2. 内: 配置对应的功能模块
	ULCON2 = 0x3; //数据位:8  停止位:1  奇偶校验：无
	UCON2 = 0x5; //设置输入输出polling mode
	/*
		DIV_VAL = (100000000/(115200 * 16)) – 1
		= 54.25 – 1
		= 53.25
		UBRDIVn = 53 (integer part of DIV_VAL)
		UFRACVALn/16 = 0.25
		Therefore, UFRACVALn = 4
	*/
	UBRDIV2 = 53;
	UFRACVAL2 = 4;   //set 波特率
}

char get()
{
//	if((UTRSTAT2&1)=!1)
		return URXH2;
		
}

void putc(char c)
{
	while (1)
	{
		if (UTRSTAT2 & 0x2)  //判断发送缓冲区是否为空
			break;
	}
	UTXH2 = c;   //把c写入发送buf
}

int main()
{
	uart_init();
	while(1)
	{
		char a=get();
		delayls();
		putc(a);
		delayls();
	}
	return 0;
}
