#include "StdAfx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raaMaths.h"

float degToRad( float f )
{
	return (f/180.0f)*cs_fPi;
}

float redToDeg( float f )
{
	return (f/cs_fPi)*180.0f;
}

void initMaths()
{
	if(!s_bMathsInit)
	{
		srand((unsigned int)time(0));
		s_bMathsInit=true;
	}
}

float randFloat( float fMin, float fMax)
{
	initMaths();
	return (((float)rand() / (float)RAND_MAX)*(fMax - fMin)) + fMin;
}

float mathsRadiusOfSphereFromVolume(float fVolume)
{
	return powf((fVolume*3.0f) / (4.0f*cs_fPi), 0.33f);
}

float mathsDimensionOfCubeFromVolume(float fVolume)
{
	return powf(fVolume, 0.33f);
}

float mathsRadiusOfConeFromVolume(float fVolume)
{
	return powf((fVolume*3.0f) / (2.0f*cs_fPi), 0.33f);
}
