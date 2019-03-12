#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <AudioSocket.h>

#define CHANNEL_DEFAULT        1             //默认声道数
#define SAMPLEBITS_DEFAULT     8             //默认采样位数
#define SAMPLERATE_DEFAULT     16000         //默认采样率

#define PREBITS_DEFAULT        40            //默认头
#define POSTBITS_DEFAULT       20            //默认尾    

#define BAND_DEFAULT           400           //默认波特率
#define FREQLOW                4000          //默认低频  表示 0
#define FREQHIGH               5500          //默认高频  表示 1

int freqhigh = 6000;
int freqlow = 4000;
int samplerate = 16000;

int prebits = 40;
int posbits = 20;
int spb = 40;	

static int buf_cur;
static short *buf;
	
static long push_data(unsigned freq, unsigned sample_counts)
{
    int i;
    short value;
    
    for (i = 0; i < sample_counts; i++)
    {
        value = 32767 * sin((2 * PI * freq * i) / samplerate);
        *(buf + (buf_cur++)) = value;  
    }

    return 0;
}

int AudioEncode(unsigned char *src, unsigned src_len, unsigned char *dst, unsigned *dst_len)
{
	int i,j;
	
	buf = (short *)dst;
	
	push_data(freqhigh, prebits*spb);

    push_data(freqlow, spb);
    for (i = 0; i < src_len; i++)
    {
		for (j = 0; j < 8; j++)
		{
			push_data((src[i]&(1<<j))?(freqhigh):(freqlow), spb);
			if (src[i]&(1<<j))
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		
		printf("\n");
    }
    
    push_data(freqhigh, posbits*spb);
	*dst_len = buf_cur;
	
	return 0;
}
