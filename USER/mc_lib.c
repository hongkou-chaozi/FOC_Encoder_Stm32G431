#include "mc_Lib.h"

SVM_obj                         SVM_handler;
controlRef_obj                  controlRef_handler;
FOC_obj                         FOC_handler;
alphaBeta_obj                   alphaBeta_handler;
DQ_obj                          DQ_handler;
ABC_obj                         ABC_handler;
SC_obj                          SC_handler;
PIController_obj                current_PI_handler;
PIController_obj                speed_PI_handler;
SMO_obj                         SMO_handler;

extern const float sinTable[TABLE_SIZE];
extern const float cosTable[TABLE_SIZE];

void clarkeTrasform(ABC_obj * abc, alphaBeta_obj * alphaBeta)
{
	alphaBeta->alpha = abc->a;
	alphaBeta->beta = (abc->a * ONE_BY_SQRT3) + (abc->b * 2.0F * ONE_BY_SQRT3);
}

void parkTrasform(alphaBeta_obj * alphaBeta, DQ_obj * dqframe, SC_obj * scLookup)
{
	dqframe->d = alphaBeta->alpha * scLookup->Cos + alphaBeta->beta * scLookup->Sin;
	dqframe->q = -alphaBeta->alpha * scLookup->Sin + alphaBeta->beta * scLookup->Cos;
}

void invClarkeTrasform(ABC_obj * abc, alphaBeta_obj * alphaBeta)
{
	abc->a = alphaBeta->alpha;
	abc->b = -0.5F * alphaBeta->alpha + SQRT3_BY2 * alphaBeta->beta;
}

void invParkTransform(alphaBeta_obj * alphaBeta, DQ_obj * dqframe, SC_obj * scLookup)
{
    alphaBeta->alpha =  dqframe->d * scLookup->Cos - dqframe->q * scLookup->Sin;
    alphaBeta->beta  =  dqframe->d * scLookup->Sin + dqframe->q * scLookup->Cos; 
}

void InitPIcontroller( PIController_obj * PI)
{
	PI->intergratorSum = 0;
	PI->out = 0;
}

void calcPI( PIController_obj * PI)
{
    float Err;
    float U;
    float Exc;
 
		Err = PI->inputRef - PI->inputFbk;
		PI->error = Err;
		U = PI->intergratorSum + PI->Kp * Err;
   
    if( U > PI->outMax )
    {
        PI->out = PI->outMax;
    }    
    else if( U < PI->outMin )
    {
        PI->out = PI->outMin;
    }
    else        
    {
        PI->out = U;  
    }
     
    Exc = U - PI->out;
    PI->intergratorSum += PI->Ki * Err - PI->Kc * Exc;

}


void sinCosLookup(SC_obj * sc)
{
   
    // Since we are using "float", it is not possible to get an index of array
    // directly. Almost every time, we will need to do interpolation, as per
    // following equation: -
    // y = y0 + (y1 - y0)*((x - x0)/(x1 - x0))
    float angle = sc->Angle;
    uint32_t y0_Index;
    uint32_t y0_IndexNext;
    float x0, x1, y0, y1, temp;
    
    // Software check to ensure  0 <= Angle < 2*PI
    if(angle <  0) 
        angle += ANGLE_2PI; 
    if(angle >= ANGLE_2PI)
        angle -= ANGLE_2PI; 
    
    y0_Index = (uint32_t)(angle/ANGLE_STEP);
    
	  //Added this condition which detects if y0_Index is >=1024.
    //Earlier the only check was for y0_IndexNext. 
    //We observed y0_Index > = 1024 when the code to reverse the direction of the motor was added
    if(y0_Index>=TABLE_SIZE)
    {
        y0_Index = 0;
        y0_IndexNext = 1;
        x0 = ANGLE_2PI;
        x1 = ANGLE_STEP;
        temp = 0;
    }
    else
    {
        y0_IndexNext = y0_Index + 1;
        if(y0_IndexNext >= TABLE_SIZE )
        {
            y0_IndexNext = 0;
            x1 = ANGLE_2PI;
        }
        else
        {
            x1 = ((y0_IndexNext) * ANGLE_STEP);
        }

        x0 = (y0_Index * ANGLE_STEP);  
    
    
    // Since below calculation is same for sin & cosine, we can do it once and reuse
    
	  temp = ((sc->Angle - x0)/(x1 - x0));
    }
    
	  // Find Sine now
    y0 = sinTable[y0_Index];
    y1 = sinTable[y0_IndexNext];     
    sc->Sin = y0 + ((y1 - y0)*temp);
	
    // Find Cosine now
    y0 = cosTable[y0_Index];
    y1 = cosTable[y0_IndexNext];
    sc->Cos = y0 + ((y1 - y0)*temp);
}






















