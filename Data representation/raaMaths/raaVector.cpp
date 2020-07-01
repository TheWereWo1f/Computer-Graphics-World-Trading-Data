#include "StdAfx.h"
#include <math.h>
#include "raaMaths.h"
#include "raaVector.h"

float* vecAdd( float *pV0, float *pV1, float *pVRes )
{
	if(pV0 && pV1 && pVRes)
	{
		pVRes[0]=pV0[0]+pV1[0];
		pVRes[1]=pV0[1]+pV1[1];
		pVRes[2]=pV0[2]+pV1[2];
	}
	return pVRes;
}

float* vecInitPVec( float *pV )
{
	if(pV)
	{
		pV[0]=pV[1]=pV[2]=0.0f;
		pV[3]=1.0f;
	}
	return pV;
}

float* vecInitDVec( float *pV )
{
	if(pV) pV[0]=pV[1]=pV[2]=pV[3]=0.0f;
	return pV;
}

float* vecInit( float *pV )
{
	if(pV) pV[0]=pV[1]=pV[2]=0.0f;
	return pV;
}

float* vecScalarProduct( float *pV0, float fS, float *pVRes )
{
	if(pV0 && pVRes)
	{
		pVRes[0]=pV0[0]*fS;
		pVRes[1]=pV0[1]*fS;
		pVRes[2]=pV0[2]*fS;
		pVRes[3] = pV0[3];
	}
	return pVRes;
}

float* vecScalarProduct(const float *pV0, float fS, float *pVRes)
{
	if (pV0 && pVRes)
	{
		pVRes[0] = pV0[0] * fS;
		pVRes[1] = pV0[1] * fS;
		pVRes[2] = pV0[2] * fS;
		pVRes[3] = pV0[3];
	}
	return pVRes;
}



float* vecSub( float *pV0, float *pV1, float *pVRes )
{
	if(pV0 && pV1 && pVRes)
	{
		pVRes[0]=pV0[0]-pV1[0];
		pVRes[1]=pV0[1]-pV1[1];
		pVRes[2]=pV0[2]-pV1[2];
	}
	return pVRes;
}

float* vecVectorProduct( float *pV0, float *pV1, float *pVRes )
{
	if(pV0 && pV1 && pVRes)
	{
		pVRes[0]=pV0[0]*pV1[0];
		pVRes[1]=pV0[1]*pV1[1];
		pVRes[2]=pV0[2]*pV1[2];
	}
	return pVRes;
}

float vecDotProduct( float *pV0, float *pV1 )
{
	if(pV0 && pV1) return pV0[0]*pV1[0]+pV0[1]*pV1[1]+pV0[2]*pV1[2];
	return 0.0f;
}

float* vecCrossProduct( float *pV0, float *pV1, float *pVRes )
{
	if(pV0 && pV1 && pVRes)
	{
		float v[3];

		v[0]=pV0[1]*pV1[2]-pV0[2]*pV1[1];
		v[1]=pV0[2]*pV1[0]-pV0[0]*pV1[2];
		v[2]=pV0[0]*pV1[1]-pV0[1]*pV1[0];

		pVRes[0]=v[0];
		pVRes[1]=v[1];
		pVRes[2]=v[2];
	}
	return pVRes;
}

float vecLength( float *pV )
{
	if(pV) return sqrtf(pV[0]*pV[0]+pV[1]*pV[1]+pV[2]*pV[2]);
	return 0.0f;
}

float vecNormalise( float *pV0, float *pVRes )
{
	if(pV0 && pVRes)
	{
		float f=sqrtf(pV0[0]*pV0[0]+pV0[1]*pV0[1]+pV0[2]*pV0[2]);
		
		pVRes[0]=pV0[0]/f;
		pVRes[1]=pV0[1]/f;
		pVRes[2]=pV0[2]/f;

		return f;
	}
	return 0.0f;
}

float* vecProject( float *pVStart, float *pVDir, float fLen, float *pVRes )
{
	if(pVStart && pVDir && pVRes)
	{
		pVRes[0]=pVStart[0]+pVDir[0]*fLen;
		pVRes[1]=pVStart[1]+pVDir[1]*fLen;
		pVRes[2]=pVStart[2]+pVDir[2]*fLen;
	}
	return pVRes;
}

float* vecSet( float fX, float fY, float fZ, float *pV )
{
	if(pV)
	{
		pV[0]=fX;
		pV[1]=fY;
		pV[2]=fZ;
	}
	return pV;
}

float* vecCopy( float *pIn, float *pOut )
{
	if(pIn && pOut) for(int i=0;i<4;i++) pOut[i]=pIn[i];
	return pOut;
}

float vecDistance( float *pV1, float *pV2 )
{
	float fLen=0.0f;

	if(pV1 && pV2)
	{
		float av[4];

		vecSub(pV2, pV1, av);
		fLen=vecLength(av);
	}

	return fLen;
}

float* vecSlerp( float *pVStart, float *pVEnd, float fSlerp, float *pV )
{
	if(pVStart && pVEnd && pV)
	{
		pV[0]=pVStart[0]+(((pVEnd[0]-pVStart[0]))*fSlerp);
		pV[1]=pVStart[1]+(((pVEnd[1]-pVStart[1]))*fSlerp);
		pV[2]=pVStart[2]+(((pVEnd[2]-pVStart[2]))*fSlerp);

		pV[3]=pVStart[3]*pVEnd[3];
	}
	return pV;
}

float* vecDoubleToFloat(double* pIn, float* pOut)
{
	if(pIn && pOut)
	{
		pOut[0] = (float)pIn[0];
		pOut[1] = (float)pIn[1];
		pOut[2] = (float)pIn[2];
		pOut[3] = (float)pIn[3];
	}
	return pOut;
}

double* vecFloatToDouble(float* pIn, double* pOut)
{
	if (pIn && pOut)
	{
		pOut[0] = (double)pIn[0];
		pOut[1] = (double)pIn[1];
		pOut[2] = (double)pIn[2];
		pOut[3] = (double)pIn[3];
	}
	return pOut;
}

float* vecRand(float fMin, float fMax, float* pV)
{
	if(pV)
	{
		pV[0] = randFloat(fMin, fMax);
		pV[1] = randFloat(fMin, fMax);
		pV[2] = randFloat(fMin, fMax);
	}
	return pV;
}

float* vecInitCVec( float *pV, float fAlpha )
{
	if(pV)
	{
		pV[0]=randFloat();
		pV[1]=randFloat();
		pV[2]=randFloat();
		pV[3]=fAlpha;
	}
	return pV;
}
