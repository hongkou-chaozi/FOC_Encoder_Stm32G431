#include "foc.h"

float regCCR[3];
float check0,check1,check2;

void SVPWM_Calc(const ABC_obj * abc, FOC_obj * focHanlder, SVM_obj * SVMhandler, float * regCCR)
{
  float maxV;
  float minV;
  float zeroSeqComp;
	
	float cmpTmp[3] = {abc->a, abc->b, abc->c};
	
	maxV = cmpTmp[0];
  minV = cmpTmp[0];
		
	  /* 找出三个电流值中的最大值和最小值 */
  for (uint8_t k = 1; k < 3; k++) 
	{
    maxV = fmaxf(maxV, cmpTmp[k]);
    minV = fminf(minV, cmpTmp[k]);
  }
	
	 /* 计算零序分量 */
  zeroSeqComp = (maxV + minV) * -0.5F;
	
	
	regCCR[0] = (-(zeroSeqComp + cmpTmp[0]) / focHanlder->Vbus + 0.5F) * SVMhandler->PWMtimerCounts;
  regCCR[1] = (-(zeroSeqComp + cmpTmp[1]) / focHanlder->Vbus + 0.5F) * SVMhandler->PWMtimerCounts;
  regCCR[2] = (-(zeroSeqComp + cmpTmp[2]) / focHanlder->Vbus + 0.5F) * SVMhandler->PWMtimerCounts;
	
//	if((check0 - regCCR[0]) > 2000)
//	{
//		regCCR[0] = check0;
//	}
//	if((check1 - regCCR[1]) > 2000)
//	{
//		regCCR[1] = check1;
//	}
//	if((check2 - regCCR[2]) > 2000)
//	{
//		regCCR[2] = check2;
//	}
//		
//	float check0 = regCCR[0];
//	float check1 = regCCR[1];
//	float check2 = regCCR[2];
}


float thetaGenerate(float frequency)
{
  static float out;
  out += frequency * 0.0001F;
	if(out > 1)
	{
		out = 0;
	}
  return out;
}


void VFStart(ABC_obj * abc, DQ_obj * dq, alphaBeta_obj * alphaBeta, float frequency, SC_obj * scLookup)
{
	scLookup->Angle = thetaGenerate(frequency) * ANGLE_2PI;
	sinCosLookup(scLookup);
	invParkTransform(alphaBeta, dq, scLookup);
	invClarkeTrasform(abc, alphaBeta);
}

