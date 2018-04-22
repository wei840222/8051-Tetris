#include <stdlib.h>

char x[4],y[4];	//當前方塊點位置(第一點為旋轉中點)
char xm[4],ym[4];	//變動方塊點位置
char rt;	//方塊旋轉形式
char gameover;	//是否遊戲結束


void clear_box()	//清除當前方塊
{	char i;
	for(i=0;i<4;i++)
		clear_point(x[i],y[i]);
}

void write_box()	//寫入當前方塊
{	char i;
	for(i=0;i<4;i++)
		write_point(x[i],y[i]);
}

void clear_change()	//清除變動後方塊
{	char i;
	for(i=0;i<4;i++)
	{
		xm[i]=0;
		ym[i]=0;
	}
}

void write_change()	//寫入變動後方塊
{	char i;
	for(i=0;i<4;i++)
	{
		x[i]=xm[i];
		y[i]=ym[i];
	}
}

void check_line()	//檢查整行並消除
{	char i,j;
	for(i=2;i<18;i++)
	{
		if(LED_Matrix[i]==0xff)
		{
			for(j=i;j>0;j--)
				LED_Matrix[j]=LED_Matrix[j-1];
			LED_Matrix[0]=0x00;
		}
	}
}

char check_error()	//檢查錯誤
{	char i;
	for(i=0;i<4;i++)
	{
		//確認重疊
		if(read_point(xm[i],ym[i]))
		{
			return 1;
			break;
		}
		//確認邊界
		if(xm[i]<0||xm[i]>7)
		{
			return 1;
			break;
		}
		if(ym[i]<0||ym[i]>17)
		{
			return 1;
			break;
		}
	}
	return 0;
}

void produce()	//亂數產生方塊
{
	switch(rand()%7)	//time1為7的倍數
	{
		case 0:	//田
			xm[0]=3;ym[0]=1;
			xm[1]=4;ym[1]=1;
			xm[2]=3;ym[2]=2;
			xm[3]=4;ym[3]=2;
			rt=0;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 1:	//一
			xm[0]=3;ym[0]=2;
			xm[1]=2;ym[1]=2;
			xm[2]=4;ym[2]=2;
			xm[3]=5;ym[3]=2;
			rt=1;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 2:	//L
			xm[0]=3;ym[0]=1;
			xm[1]=3;ym[1]=0;
			xm[2]=3;ym[2]=2;
			xm[3]=4;ym[3]=2;
			rt=3;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 3:	//反L
			xm[0]=4;ym[0]=1;
			xm[1]=4;ym[1]=0;
			xm[2]=4;ym[2]=2;
			xm[3]=3;ym[3]=2;
			rt=3;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 4:	//Z
			xm[0]=3;ym[0]=1;
			xm[1]=2;ym[1]=1;
			xm[2]=3;ym[2]=2;
			xm[3]=4;ym[3]=2;
			rt=1;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 5:	//ㄣ
			xm[0]=3;ym[0]=1;
			xm[1]=3;ym[1]=0;
			xm[2]=4;ym[2]=1;
			xm[3]=4;ym[3]=2;
			rt=1;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
		case 6:	//T
			xm[0]=3;ym[0]=2;
			xm[1]=2;ym[1]=2;
			xm[2]=3;ym[2]=1;
			xm[3]=4;ym[3]=2;
			rt=3;
			if(check_error())	//方塊已滿GameOver
			{
				gameover=1;
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
	}
}

void rotate()	//旋轉方塊
{	char i;
	switch(rt)
	{
		case 0:	//不旋轉
			break;
		case 1:	//順時針
			xm[0]=x[0];
			ym[0]=y[0];
			for(i=1;i<4;i++)
			{
				xm[i]=xm[0]+ym[0]-y[i];
				ym[i]=x[i]-xm[0]+ym[0];
			}
			clear_box();
			if(check_error())
			{
				write_box();
				clear_change();
			}
			else
			{
				write_change();
				write_box();
				clear_change();
				rt=2;
			}			
			break;
		case 2:	//逆時針
			xm[0]=x[0];
			ym[0]=y[0];
			for(i=1;i<4;i++)
			{
				xm[i]=y[i]+xm[0]-ym[0];
				ym[i]=xm[0]+ym[0]-x[i];
			}
			clear_box();
			if(check_error())
			{
				write_box();
				clear_change();
			}
			else
			{
				write_change();
				write_box();
				clear_change();
				rt=1;
			}
			break;
		case 3:	//順時針
			xm[0]=x[0];
			ym[0]=y[0];
			for(i=1;i<4;i++)
			{
				xm[i]=xm[0]+ym[0]-y[i];
				ym[i]=x[i]-xm[0]+ym[0];
			}
			clear_box();
			if(check_error())
			{
				write_box();
				clear_change();
			}
			else
			{
				write_change();
				write_box();
				clear_change();
			}
			break;
	}
}

char falling()	//方塊飄落一行
{	char i;
	clear_box();
	for(i=0;i<4;i++)
	{
		xm[i]=x[i];
		ym[i]=y[i]+1;
	}
	if(check_error())	//無法移動取消動作
	{
		write_box();
		clear_change();
		return 1;
	}
	else
	{
		write_change();
		write_box();
		clear_change();
		return 0;
	}
}

void down()	//方塊下降至底部
{
	while(1)
	{
		if(falling())
			break;
	}
	check_line();
	produce();
}

void left()	//方塊左移
{	char i;
	clear_box();
	for(i=0;i<4;i++){
		xm[i]=x[i]-1;
		ym[i]=y[i];
	}
	if(check_error())	//無法移動取消動作
	{
		write_box();
		clear_change();
	}
	else
	{
		write_change();
		write_box();
		clear_change();
	}
}

void right()	//方塊右移
{	char i;
	clear_box();
	for(i=0;i<4;i++){
		xm[i]=x[i]+1;
		ym[i]=y[i];
	}
	if(check_error())	//無法移動取消動作
	{
		write_box();
		clear_change();
	}
	else
	{
		write_change();
		write_box();
		clear_change();
	}
}

void move(char m)	//移動方塊
{
	switch(m)
	{
		case 'u':	//旋轉
			rotate();
			break;
		case 'd':	//下降至底部
			down();	
			break;
		case 'l':	//左移
			left();
			break;
		case 'r':	//右移
			right();
			break;
	}
}

void tetris_init()	//遊戲初始化
{	char i;
	value_init();
	gameover=0;
	for(i=0;i<4;i++)
	{
		x[i]=0;
		y[i]=0;
		xm[i]=0;
		ym[i]=0;
	}
	rt=0;
	produce();
}