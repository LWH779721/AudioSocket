#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <AudioSocket.h>

int main(int argc, char **args)
{	
	FILE *fp = NULL;
	char *txt = "hello";
	int txt_len = strlen(txt);
	char *buf = NULL;
	unsigned int dst_len = 0;
	
	buf = malloc(sizeof(short) * 1024 * 1024 * 4);
	
	AudioEncode(txt, txt_len, buf, &dst_len);
	
	fp = fopen("test.pcm", "wb");
	fwrite((void *)buf, 1, sizeof(short)*dst_len, fp);
	fflush(fp);
	fclose(fp);
	free(buf);
	
	return 0;
}