#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <AudioSocket.h>

int main(int argc, char **args)
{       
	int i;
	short value; 
	FILE *fp = NULL;
	
	fp = fopen(args[1], "rb");
	calc_coeffs();
	
    while (1)
    {
		fread(&value, 1, 2, fp);
		if (feof(fp))
		{
			break;
		}
		
		goertzel(value);
    }
    
	fclose(fp);
    return 0;
}