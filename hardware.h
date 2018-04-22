#define LED P2
#define SCAN P0
sbit UP=P3^0;
sbit DOWN=P3^1;
sbit LEFT=P3^2;
sbit RIGHT=P3^3;

char bu,bd,bl,br;	//按鈕狀態
unsigned char LED_Matrix[18];	//LED畫面陣列
char s;	//掃描行數
int time1,time2,time3;	//計時器變數

void value_init()	//變數初始化
{	char i;
//計時器初始化
	time1=0;
	time2=0;
	time3=0;
	//點矩陣初始化
	s=0;
	for(i=0;i<18;i++)
		LED_Matrix[i]=0x00;
}

//中斷計時器

void tf0_set100us()
{
	TH0=(65536-100)/256;	//TF0週期100us
	TL0=(65536-100)%256;
}

char timer1()	//計時器1(600ms)方塊下降
{
	if(time1==5999)
	{
		time1=0;
		return 1;
	}
	else{
		time1++;
		return 0;
	}
}

char timer2()	//計時器2(100ms)GameOver動畫
{
	if(time2==999)
	{
		time2=0;
		return 1;
	}
	else{
		time2++;
		return 0;
	}
}

char timer3()	//計時器3(50ms)按鍵防彈跳
{
	if(time3==499)
	{
		time3=0;
		return 1;
	}
	else{
		time3++;
		return 0;
	}
}

//LED點矩陣
char read_point(char x, char y)	//讀取座標陣列值
{	char i;
	char temp=LED_Matrix[y];
	for(i=0;i<x;i++)
		temp/=2;
	return temp%2;
}

void write_point(char x, char y)	//寫入座標陣列值
{
	char temp=0x01;
	temp<<=x;
	LED_Matrix[y]|=temp;
}

void clear_point(char x, char y)	//清除座標陣列值
{
	char temp=0x01;
	temp<<=x;
	LED_Matrix[y]&=(~temp);
}

void led_scan()	//掃描LED畫面
{
	if(s>=16)
		s=0;
	LED=LED_Matrix[s+2];
	SCAN=s;
	s++;
}

//掃描按鈕
char check_button()
{
	//上
	if(UP==1)
	{
		bu=0;			
	}
	if(bu==0&&UP==0)
	{
		bu=1;
		return 'u';
	}
	//下
	if(DOWN==1)
	{
		bd=0;			
	}
	if(bd==0&&DOWN==0)
	{
		bd=1;
		return 'd';
	}
	//左
	if(LEFT==1)
	{
		bl=0;		
	}
	if(bl==0&&LEFT==0)
	{
		bl=1;
		return 'l';
	}
	//右
	if(RIGHT==1)
	{
		br=0;		
	}
	if(br==0&&RIGHT==0)
	{
		br=1;
		return 'r';
	}
}

//硬體初始化
void hardware_init()
{
	//中斷計時器TF0,TF1初始化
	IE=0x8a;
	TMOD=0x11;	//TF0,TF1=Mode1
	TR0=1;	//啟動Timer0
	tf0_set100us();
	//輸出輸入阜初始化
	LED=0x00;
	SCAN=0x00;
}