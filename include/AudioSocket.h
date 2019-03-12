#ifndef __AUDIOSOCKET_H__
#define __AUDIOSOCKET_H__

#ifdef __cplusplus
extern "C"{
#endif

#define PI                     3.141592654f   //pi

extern int AudioEncode(unsigned char *src, unsigned src_len, unsigned char *dst, unsigned *dst_len);
extern void calc_coeffs();
extern void goertzel(int sample);

#ifdef __cplusplus
}
#endif
#endif
