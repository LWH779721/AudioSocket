#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#define SAMPLING_RATE       16000
#define MAX_BINS            2
#define GOERTZEL_N          40

int         sample_count;
double      q1[ MAX_BINS ];
double      q2[ MAX_BINS ];
double      r[ MAX_BINS ];

/*
 * coef = 2.0 * cos( (2.0 * PI * k) / (float)GOERTZEL_N)) ;
 * Where k = (int) (0.5 + ((float)GOERTZEL_N * target_freq) / SAMPLING_RATE));
 *
 * More simply: coef = 2.0 * cos( (2.0 * PI * target_freq) / SAMPLING_RATE );
 */
double      freqs[ MAX_BINS] = 
{
	4000,
	6000
};

double      coefs[ MAX_BINS ] ;


/*----------------------------------------------------------------------------
 *  calc_coeffs
 *----------------------------------------------------------------------------
 * This is where we calculate the correct co-efficients.
 */
void calc_coeffs()
{
  int n;

  for(n = 0; n < MAX_BINS; n++)
  {
    coefs[n] = 2.0 * cos(2.0 * 3.141592654 * freqs[n] / SAMPLING_RATE);
  }
}

void get_result(int bit)
{
	static int start;
	static int prebits;
	static char a;
	static int cur;
	
	if (bit == 1)
	{
		if (start == 0)
		{
			prebits++;
		}
		else
		{
			printf("1");
			a |= (1 << cur);
			cur++;	
			if (cur == 8)
			{
				cur = 0;
				printf("%c\n", a);
				a = 0;
			}
		}
	}
	else
	{	
		if (start == 1)
		{
			printf("0");
			cur ++;
			if (cur == 8)
			{
				cur = 0;
				printf("%c\n", a);
				a = 0;
			}
		}
		else
		{
			if (prebits >= 40)
			{
				start = 1;
			}
			
			prebits = 0;
		}
	}
}

void goertzel( int sample )
{
  double      q0;
  int        i;

  sample_count++;
  for ( i=0; i<MAX_BINS; i++ )
  {
    q0 = coefs[i] * q1[i] - q2[i] + sample;
    q2[i] = q1[i];
    q1[i] = q0;
  }

  if (sample_count == GOERTZEL_N)
  {
    for ( i=0; i<MAX_BINS; i++ )
    {
      r[i] = (q1[i] * q1[i]) + (q2[i] * q2[i]) - (coefs[i] * q1[i] * q2[i]);
      q1[i] = 0.0;
      q2[i] = 0.0;
    }
    #if 0
	printf("r[0]: %lf, r[1]: %lf\n", r[0], r[1]);
	#else
	if (r[0] > r[1])
	{
		get_result(0);
		//printf("0");
	}
	else
	{
		get_result(1);
		//printf("1");		
	}
	#endif
    sample_count = 0;
  }
}
