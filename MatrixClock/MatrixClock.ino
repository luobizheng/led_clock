#include <Adafruit_NeoPixel.h>

#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include "matrix_show.h"
#include "at_cmd.h"
#include "serial.h"
#include <string.h>
#include <stdio.h>

//unsigned long last_time = 0;
unsigned long time=0;

int shi,shi_h,shi_l,fen,fen_h,fen_l;

char ary_dis[6];

char *p_miao_pic=\
"ZKY VERY GOoD HAHA ZKY HAO HAO XUE XI TIAN TIAN XIANG SHANG\
ZKY astray ZKY Horses for courses";





int index_miao_pic=0;



char*		p_kaiji_pic1=" ZKY ";
char*		p_kaiji_pic2="(o_o)";
char*		p_kaiji_pic3="(^_^)";

void setup()
{
    initMatrix();
    initSerial();

		show('R', 100, 30, p_kaiji_pic1);
		delay(1000);


		for(int i=0;i<6;i++)
		{
			show('R', 100, 30, p_kaiji_pic2);
			delay(500);

			show('R', 100, 30, p_kaiji_pic3);
			delay(500);
		}

		show('R', 100, 30, p_kaiji_pic1);
		delay(1000);
		show('R', 100, 30, p_kaiji_pic3);
		delay(4000);

    
}

void loop()
{

	time=millis()/1000;
	time=time+43500;
	
	shi=time/3600%24;
	fen=time/60%60;

	shi_h=shi/10;
	shi_l=shi%10;

	fen_h=fen/10;
	fen_l=fen%10;


	ary_dis[0]='0'+shi_h;
	
	ary_dis[1]='0'+shi_l;
	


	ary_dis[3]='0'+fen_h;

	ary_dis[4]='0'+fen_l;




	ary_dis[2]=p_miao_pic[index_miao_pic];

	index_miao_pic++;
	if(index_miao_pic>=strlen(p_miao_pic))
	{
		index_miao_pic=0;
	}
	


	show('R', 100, 30, ary_dis);


	delay(1000);

	#if 0
    parseInfo();
    if (info.is_show)
    {
        show(info.color, info.delay_ms, info.brightness, info.str);
        info.is_show = false;
        last_time = millis();
    }
    else if (info.is_clear)
    {
        off_show();
        info.is_clear = false;
    }

    // 5min 没有通讯则关闭显示
    if (millis() - last_time > 5 /*min*/ * 60 /*s*/ * 1000 /*ms*/)
    {
        off_show();
        delay(1000);
    }

	#endif

		//delay(1000);

    
}
