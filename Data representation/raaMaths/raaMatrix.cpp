#include "StdAfx.h"
#include <math.h>

#include "raaMatrix.h"

// 0   1     2   3
// 4   5     6   7
// 8   9    10 11
// 12 13 14 15


void matMakeIdentity( float *pM )
{
	if(pM)
	{
		pM[0]=pM[5]=pM[10]=pM[15]=1.0f;
		pM[1]=pM[2]=pM[3]=pM[4]=pM[6]=pM[7]=pM[8]=pM[9]=pM[11]=pM[12]=pM[13]=pM[14]=0.0f;
	}
}

void matMakeTranslation( float fX, float fY, float fZ, float *pM )
{
	if(pM)
	{
		pM[0]=pM[5]=pM[10]=pM[15]=1.0f;
		pM[1]=pM[2]=pM[3]=pM[4]=pM[6]=pM[7]=pM[8]=pM[9]=pM[11]=0.0f;
		pM[12]=fX;
		pM[13]=fY;
		pM[14]=fZ;
	}
}

void matMakeScale( float fX, float fY, float fZ, float *pM )
{
	if(pM)
	{
		pM[0]=fX;
		pM[5]=fY;
		pM[10]=fZ;
		pM[15]=1.0f;
		pM[1]=pM[2]=pM[3]=pM[4]=pM[6]=pM[7]=pM[8]=pM[9]=pM[11]=pM[12]=pM[13]=pM[14]=0.0f;
	}
}

void matMakeXAxisRot( float fRadians, float *pM )
{
	if(pM)
	{
		float c=cosf(fRadians);
		float s=sinf(fRadians);

		pM[0]=pM[15]=1.0f;
		pM[5]=pM[10]=c;
		pM[6]=s;
		pM[9]=-s;
		pM[1]=pM[2]=pM[3]=pM[4]=pM[7]=pM[8]=pM[11]=pM[12]=pM[13]=pM[14]=0.0f;
	}
}

void matMakeYAxisRot( float fRadians, float *pM )
{
	if(pM)
	{
		float c=cosf(fRadians);
		float s=sinf(fRadians);

		pM[0]=pM[10]=c;
		pM[5]=pM[15]=1.0f;
		pM[1]=pM[3]=pM[4]=pM[6]=pM[7]=pM[9]=pM[11]=pM[12]=pM[13]=pM[14]=0.0f;
		pM[2]=s;
		pM[8]=-s;
	}
}

void matMakeZAxisRot( float fRadians, float *pM )
{
	if(pM)
	{
		float c=cosf(fRadians);
		float s=sinf(fRadians);

		pM[0]=pM[5]=c;
		pM[10]=pM[15]=1.0f;
		pM[1]=s;
		pM[4]=-s;
		pM[2]=pM[3]=pM[6]=pM[7]=pM[8]=pM[9]=pM[11]=pM[12]=pM[13]=pM[14]=0.0f;
	}
}

void matVecMult( float *pV, float *pM, float *pVRes )
{
	if(pV && pM && pVRes)
	{
		float v[4];

		v[0]=pV[0]*pM[0]+pV[1]*pM[4]+pV[2]*pM[8]+pV[3]*pM[12];
		v[1]=pV[0]*pM[1]+pV[1]*pM[5]+pV[2]*pM[9]+pV[3]*pM[13];
		v[2]=pV[0]*pM[2]+pV[1]*pM[6]+pV[2]*pM[10]+pV[3]*pM[14];
		v[3] = pV[0] * pM[3] + pV[1] * pM[7] + pV[2] * pM[11] + pV[3] * pM[15];

		pVRes[0]=v[0];
		pVRes[1]=v[1];
		pVRes[2]=v[2];
		pVRes[3]=v[3];
	}
}

void matMatMult( float *pM0, float *pM1, float *pMRes )
{
	if(pM0 && pM1 && pMRes)
	{
		float m[16];
/*
		m[0]=pM0[0]*pM1[0]+pM0[1]*pM1[4]+pM0[2]*pM1[8]+pM0[3]*pM1[12];
		m[1]=pM0[0]*pM1[1]+pM0[1]*pM1[5]+pM0[2]*pM1[9]+pM0[3]*pM1[13];
		m[2]=pM0[0]*pM1[2]+pM0[1]*pM1[6]+pM0[2]*pM1[10]+pM0[3]*pM1[14];
		m[3]=pM0[0]*pM1[3]+pM0[1]*pM1[7]+pM0[2]*pM1[11]+pM0[3]*pM1[15];

		m[4]=pM0[4]*pM1[0]+pM0[5]*pM1[4]+pM0[6]*pM1[8]+pM0[7]*pM1[12];
		m[5]=pM0[4]*pM1[1]+pM0[5]*pM1[5]+pM0[6]*pM1[9]+pM0[7]*pM1[13];
		m[6]=pM0[4]*pM1[2]+pM0[5]*pM1[6]+pM0[6]*pM1[10]+pM0[7]*pM1[14];
		m[7]=pM0[4]*pM1[3]+pM0[5]*pM1[7]+pM0[6]*pM1[11]+pM0[7]*pM1[15];

		m[8]=pM0[8]*pM1[0]+pM0[9]*pM1[4]+pM0[10]*pM1[8]+pM0[11]*pM1[12];
		m[9]=pM0[8]*pM1[1]+pM0[9]*pM1[5]+pM0[10]*pM1[9]+pM0[11]*pM1[13];
		m[10]=pM0[8]*pM1[2]+pM0[9]*pM1[6]+pM0[10]*pM1[10]+pM0[11]*pM1[14];
		m[11]=pM0[8]*pM1[3]+pM0[9]*pM1[7]+pM0[10]*pM1[11]+pM0[11]*pM1[15];

		m[12]=pM0[12]*pM1[0]+pM0[13]*pM1[4]+pM0[14]*pM1[8]+pM0[15]*pM1[12];
		m[13]=pM0[12]*pM1[1]+pM0[13]*pM1[5]+pM0[14]*pM1[9]+pM0[15]*pM1[13];
		m[14]=pM0[12]*pM1[2]+pM0[13]*pM1[6]+pM0[14]*pM1[10]+pM0[15]*pM1[14];
		m[15]=pM0[12]*pM1[3]+pM0[13]*pM1[7]+pM0[14]*pM1[11]+pM0[15]*pM1[15];
*/

		m[0] = pM0[0] * pM1[0] + pM0[4] * pM1[1] + pM0[8] * pM1[2] + pM0[12] * pM1[3];
		m[1] = pM0[1] * pM1[0] + pM0[5] * pM1[1] + pM0[9] * pM1[2] + pM0[13] * pM1[3];
		m[2] = pM0[2] * pM1[0] + pM0[6] * pM1[1] + pM0[10] * pM1[2] + pM0[14] * pM1[3];
		m[3] = pM0[3] * pM1[0] + pM0[7] * pM1[1] + pM0[11] * pM1[2] + pM0[15] * pM1[3];

		m[4] = pM0[0] * pM1[4] + pM0[4] * pM1[5] + pM0[8] * pM1[6] + pM0[12] * pM1[7];
		m[5] = pM0[1] * pM1[4] + pM0[5] * pM1[5] + pM0[9] * pM1[6] + pM0[13] * pM1[7];
		m[6] = pM0[2] * pM1[4] + pM0[6] * pM1[5] + pM0[10] * pM1[6] + pM0[14] * pM1[7];
		m[7] = pM0[3] * pM1[4] + pM0[7] * pM1[5] + pM0[11] * pM1[6] + pM0[15] * pM1[7];

		m[8] = pM0[0] * pM1[8] + pM0[4] * pM1[9] + pM0[8] * pM1[10] + pM0[12] * pM1[11];
		m[9] = pM0[1] * pM1[8] + pM0[5] * pM1[9] + pM0[9] * pM1[10] + pM0[13] * pM1[11];
		m[10] = pM0[2] * pM1[8] + pM0[6] * pM1[9] + pM0[10] * pM1[10] + pM0[14] * pM1[11];
		m[11] = pM0[3] * pM1[8] + pM0[7] * pM1[9] + pM0[11] * pM1[10] + pM0[15] * pM1[11];

		m[12] = pM0[0] * pM1[12] + pM0[4] * pM1[13] + pM0[8] * pM1[14] + pM0[12] * pM1[15];
		m[13] = pM0[1] * pM1[12] + pM0[5] * pM1[13] + pM0[9] * pM1[14] + pM0[13] * pM1[15];
		m[14] = pM0[2] * pM1[12] + pM0[6] * pM1[13] + pM0[10] * pM1[14] + pM0[14] * pM1[15];
		m[15] = pM0[3] * pM1[12] + pM0[7] * pM1[13] + pM0[11] * pM1[14] + pM0[15] * pM1[15];



		pMRes[0]=m[0];
		pMRes[1]=m[1];
		pMRes[2]=m[2];
		pMRes[3]=m[3];
		pMRes[4]=m[4];
		pMRes[5]=m[5];
		pMRes[6]=m[6];
		pMRes[7]=m[7];
		pMRes[8]=m[8];
		pMRes[9]=m[9];
		pMRes[10]=m[10];
		pMRes[11]=m[11];
		pMRes[12]=m[12];
		pMRes[13]=m[13];
		pMRes[14]=m[14];
		pMRes[15]=m[15];
	}
}

void matInvert(float* pMIn, float* pMOut)
{
	float a1, b1, c1;
	float a2, b2, c2;
	float a3, b3, c3;
	float i0, i1, i2;
	float t;
	float tx, ty, tz;

	a1 = pMIn[0];
	b1 = pMIn[1];
	c1 = pMIn[2];

	a2 = pMIn[4];
	b2 = pMIn[5];
	c2 = pMIn[6];

	a3 = pMIn[8];
	b3 = pMIn[9];
	c3 = pMIn[10];

	tx = pMIn[12];
	ty = pMIn[13];
	tz = pMIn[14];

	i0 = ((b2 * c3) - (b3 * c2));
	i1 = -((a2 * c3) - (a3 * c2));
	i2 = ((a2 * b3) - (a3 * b2));

	t = 1.0f / ((a1 * i0) + (b1 * i1) + (c1 * i2));

	pMOut[0] = i0 = i0 * t;
	pMOut[4] = i1 = i1 * t;
	pMOut[8] = i2 = i2 * t;
	pMOut[12] = -((tx * i0) + (ty * i1) + (tz * i2));
	pMOut[1] = i0 = -t * ((b1 * c3) - (b3 * c1));
	pMOut[5] = i1 = t * ((a1 * c3) - (a3 * c1));
	pMOut[9] = i2 = -t * ((a1 * b3) - (a3 * b1));
	pMOut[13] = -((tx * i0) + (ty * i1) + (tz * i2));
	pMOut[2] = i0 = t * ((b1 * c2) - (b2 * c1));
	pMOut[6] = i1 = -t * ((a1 * c2) - (a2 * c1));
	pMOut[10] = i2 = t * ((a1 * b2) - (a2 * b1));
	pMOut[14] = -((tx * i0) + (ty * i1) + (tz * i2));
	pMOut[3] = 0.0f;
	pMOut[7] = 0.0f;
	pMOut[11] = 0.0f;
	pMOut[15] = 1.0f;

}

#define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a) = (b); (b) = _tmp; }
#define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a) = (b); (b) = _tmp; }
#define MAT(m, r, c) (m)[(c) * 4 + (r)]

bool matFullInvert(float* pMIn, float* pMOut) 
{
	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT(pMIn, 0, 0), r0[1] = MAT(pMIn, 0, 1), r0[2] = MAT(pMIn, 0, 2), r0[3] = MAT(pMIn, 0, 3), r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0, r1[0] = MAT(pMIn, 1, 0), r1[1] = MAT(pMIn, 1, 1), r1[2] = MAT(pMIn, 1, 2), r1[3] = MAT(pMIn, 1, 3), r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0, r2[0] = MAT(pMIn, 2, 0), r2[1] = MAT(pMIn, 2, 1), r2[2] = MAT(pMIn, 2, 2), r2[3] = MAT(pMIn, 2, 3), r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0, r3[0] = MAT(pMIn, 3, 0), r3[1] = MAT(pMIn, 3, 1), r3[2] = MAT(pMIn, 3, 2), r3[3] = MAT(pMIn, 3, 3), r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	if (fabsf(r3[0]) > fabsf(r2[0])) SWAP_ROWS_FLOAT(r3, r2);
	if (fabsf(r2[0]) > fabsf(r1[0])) SWAP_ROWS_FLOAT(r2, r1);
	if (fabsf(r1[0]) > fabsf(r0[0])) SWAP_ROWS_FLOAT(r1, r0);

	if (0.0 == r0[0]) return false;

	m1 = r1[0] / r0[0], m2 = r2[0] / r0[0], m3 = r3[0] / r0[0];

	s = r0[1]; r1[1] -= m1 * s, r2[1] -= m2 * s, r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s, r2[2] -= m2 * s, r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s, r2[3] -= m2 * s, r3[3] -= m3 * s;
	s = r0[4]; if (s != 0.0) r1[4] -= m1 * s, r2[4] -= m2 * s, r3[4] -= m3 * s;
	s = r0[5]; if (s != 0.0) r1[5] -= m1 * s, r2[5] -= m2 * s, r3[5] -= m3 * s;
	s = r0[6]; if (s != 0.0) r1[6] -= m1 * s, r2[6] -= m2 * s, r3[6] -= m3 * s;
	s = r0[7]; if (s != 0.0) r1[7] -= m1 * s, r2[7] -= m2 * s, r3[7] -= m3 * s;

	if (fabsf(r3[1]) > fabsf(r2[1])) SWAP_ROWS_FLOAT(r3, r2);
	if (fabsf(r2[1]) > fabsf(r1[1])) SWAP_ROWS_FLOAT(r2, r1);
	if (0.0 == r1[1]) return false;

	m2 = r2[1] / r1[1];
	m3 = r3[1] / r1[1];

	r2[2] -= m2 * r1[2], r3[2] -= m3 * r1[2], r2[3] -= m2 * r1[3], r3[3] -= m3 * r1[3];

	s = r1[4]; if (0.0 != s) r2[4] -= m2 * s, r3[4] -= m3 * s;
	s = r1[5]; if (0.0 != s) r2[5] -= m2 * s, r3[5] -= m3 * s;
	s = r1[6]; if (0.0 != s) r2[6] -= m2 * s, r3[6] -= m3 * s;
	s = r1[7]; if (0.0 != s) r2[7] -= m2 * s, r3[7] -= m3 * s;

	if (fabsf(r3[2]) > fabsf(r2[2])) SWAP_ROWS_FLOAT(r3, r2);
	if (0.0 == r2[2]) return false;

	m3 = r3[2] / r2[2]; r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4], r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];

	if (0.0 == r3[3]) return 0;

	s = 1.0f / r3[3];	r3[4] *= s, r3[5] *= s, r3[6] *= s, r3[7] *= s;

	m2 = r2[3]; s = 1.0f / r2[2]; r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2), r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3]; r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1, r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3]; r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0, r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
	m1 = r1[2]; s = 1.0f / r1[1]; r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1), r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2]; r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0, r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
	m0 = r0[1]; s = 1.0f / r0[0]; r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0), r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(pMOut, 0, 0) = r0[4], MAT(pMOut, 0, 1) = r0[5], MAT(pMOut, 0, 2) = r0[6], MAT(pMOut, 0, 3) = r0[7], MAT(pMOut, 1, 0) = r1[4], MAT(pMOut, 1, 1) = r1[5], MAT(pMOut, 1, 2) = r1[6], MAT(pMOut, 1, 3) = r1[7], MAT(pMOut, 2, 0) = r2[4], MAT(pMOut, 2, 1) = r2[5], MAT(pMOut, 2, 2) = r2[6], MAT(pMOut, 2, 3) = r2[7], MAT(pMOut, 3, 0) = r3[4], MAT(pMOut, 3, 1) = r3[5], MAT(pMOut, 3, 2) = r3[6], MAT(pMOut, 3, 3) = r3[7];
	return true;
}

void matTranslate( float fX, float fY, float fZ, float *pM )
{
	float m[16];
	matMakeTranslation(fX, fY, fZ, m);
	matMatMult(pM, m, pM);
}

void matScale( float fX, float fY, float fZ, float *pM )
{
	float m[16];
	matMakeScale(fX, fY, fZ, m);
	matMatMult(pM, m, pM);
}

void matXAxisRot( float fRadians, float *pM )
{
	float m[16];
	matMakeXAxisRot(fRadians, m);
	matMatMult(pM, m, pM);
}

void matYAxisRot( float fRadians, float *pM )
{
	float m[16];
	matMakeYAxisRot(fRadians, m);
	matMatMult(pM, m, pM);
}

void matZAxisRot( float fRadians, float *pM )
{
	float m[16];
	matMakeZAxisRot(fRadians, m);
	matMatMult(pM, m, pM);
}