#pragma once
#ifdef _DEBUG
#pragma comment(lib,"raaMathsD")
#else
#pragma comment(lib,"raaMathsR")
#endif


float* vecInitPVec(float *pV);
float* vecInitDVec(float *pV);
float* vecInitCVec(float *pV, float fAlpha=1.0f);
float* vecInit(float *pV);
float* vecAdd(float *pV0, float *pV1, float *pVRes);
float* vecSub(float *pV0, float *pV1, float *pVRes);
float* vecScalarProduct(float *pV0, float fS, float *pVRes);
float* vecScalarProduct(const float *pV0, float fS, float *pVRes);
float* vecVectorProduct(float *pV0, float *pV1, float *pVRes);
float vecDotProduct(float *pV0, float *pV1);
float* vecCrossProduct(float *pV0, float *pV1, float *pVRes);
float vecLength(float *pV);
float vecDistance(float *pV1, float *pV2);
float vecNormalise(float *pV0, float *pVRes);
float* vecProject(float *pVStart, float *pVDir, float fLen, float *pVRes);
float* vecSet(float fX, float fY, float fZ, float *pV);
float* vecCopy(float *pIn, float *pOut);
float* vecSlerp(float *pVStart, float *pVEnd, float fSlerp, float *pV);
float* vecRand(float fMin, float fMax, float *pV);
float* vecDoubleToFloat(double *pIn, float *pOut);
double* vecFloatToDouble(float *pIn, double *pOut);
