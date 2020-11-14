#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys.h"

typedef struct
{
	s16 V1;
	s16 V2;
	s16 V3;
    s16 V4;
	s16 cnt1;
	s16 cnt2;
	s16 cnt3;
    s16 cnt4;
	s16 rcnt1;
	s16 rcnt2;
	s16 rcnt3;
    s16 rcnt4;
	s32 CNT1;
	s32 CNT2;
	s32 CNT3;
    s32 CNT4;

}EncoderType;

void EncodeOne_Get(void);
void EncodeTwo_Get(void);
void EncodeThr_Get(void);
void EncodeFor_Get(void);
void Encoder_Get_Config(void);

#endif
