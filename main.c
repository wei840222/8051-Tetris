#include <reg51.h>
#include <hardware.h>
#include <tetris.h>

main()
{
	//硬體初始化
	hardware_init();
	//亂數初始化
	srand();
	//遊戲初始化
	tetris_init();
	//遊戲迴圈
	while(1);
}

void sys_timer() interrupt 1	//中斷計時器
{
	//重設週期(100us)
	tf0_set100us();
	//掃描一行
	led_scan();
	//遊戲進行中
	if(gameover==0)
	{
		if(timer1())
			if(falling())	//無法再下降
			{
				check_line();	//檢查整行並消除
				produce();	//產生新方塊
			}
		if(timer3())	//50ms掃描按鍵一次
			move(check_button());
	}
	//遊戲結束且播放動畫
	if(gameover>0)
	{
		if(timer2())
		{
			LED_Matrix[18-gameover]=0xff;
			gameover++;
		}
		if(gameover==19)
		{
			tetris_init();
		}
	}
}