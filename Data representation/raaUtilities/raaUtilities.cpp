#include "StdAfx.h"

#include <windows.h>
#include <gl/GL.h>
#include "raaMaths/raaVector.h"
#include "raaUtilities.h"

void utilitiesColourToMat(const float* pafCol, float fShininess, bool bEmisive)
{
	if (pafCol)
	{
		float afCol[4];
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vecScalarProduct(pafCol, 0.01f, afCol));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vecScalarProduct(pafCol, 0.8f, afCol));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vecScalarProduct(pafCol, 0.2f, afCol));
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShininess);
		if(bEmisive) glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vecScalarProduct(pafCol, 0.99f, afCol));
	}
}

float* utilitiesScreenProportionToViewport(float fX, float fY, int* aiViewport, float* pF) 
{
	pF[0] = fX*(float)(aiViewport[2] - 30) * 0.9f + (float)(aiViewport[0] + 15);
	pF[1] = fY*(float)(aiViewport[3] - 30) * 0.9f + (float)(aiViewport[1] + 15)*0.75f;
	pF[2] = -30.0f;
	return pF;
}

