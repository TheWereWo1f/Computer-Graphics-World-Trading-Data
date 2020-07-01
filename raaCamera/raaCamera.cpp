#include "StdAfx.h"
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <raaMaths/raaVector.h>
#include <raaMaths/raaMatrix.h>
#include <raaMaths/raaMaths.h>
#include "raaCamera.h"
#include <iostream>


void camInit( raaCamera &rCam )
{
	camReset(rCam);
}

void camReset( raaCamera &rCam )
{
	vecInitPVec(rCam.m_fVP);
	vecInitPVec(rCam.m_fVT);
	vecInitDVec(rCam.m_fVR);
	vecInitDVec(rCam.m_fVD);
	vecInitDVec(rCam.m_fVU);
	vecSet(492.0f, 500.0f, 500.0f, rCam.m_fVP);
	vecSet(0.0f, 0.0f, -1.0f, rCam.m_fVD);
	vecSet(1.0f, 0.0f, 0.0f, rCam.m_fVR);
	vecSet(0.0f, 1.0f, 0.0f, rCam.m_fVU);
	vecSet(0.0f, 0.0f, 0.0f, rCam.m_fVT);
	rCam.m_fNear=0.2f;
	rCam.m_fFar=300000.0f;
	rCam.m_bChanged = true;
	rCam.m_bInvChanged = true;
	rCam.m_bRotChanged = true;
	rCam.m_bRotInvChanged = true;
}

void camCopy(raaCamera &rIn, raaCamera &rOut)
{
	vecCopy(rIn.m_fVP, rOut.m_fVP);
	vecCopy(rIn.m_fVT, rOut.m_fVT);
	vecCopy(rIn.m_fVR, rOut.m_fVR);
	vecCopy(rIn.m_fVU, rOut.m_fVU);
	vecCopy(rIn.m_fVD, rOut.m_fVD);
	rOut.m_fFar=rIn.m_fFar;
	rOut.m_fNear=rIn.m_fNear;
	rOut.m_bChanged = true;
	rOut.m_bInvChanged = true;
	rOut.m_bRotChanged = true;
	rOut.m_bRotInvChanged = true;
}

void camApply( raaCamera &rCam )
{
	gluLookAt(rCam.m_fVP[0], rCam.m_fVP[1], rCam.m_fVP[2], rCam.m_fVT[0], rCam.m_fVT[1], rCam.m_fVT[2], rCam.m_fVU[0], rCam.m_fVU[1], rCam.m_fVU[2]); 
}

float* camObjMat(raaCamera &rCam)
{
	if (rCam.m_bChanged)
	{
		rCam.m_bChanged = false;
		float mR[16], mT[16];
		matMakeIdentity(mR);
		matMakeIdentity(mT);
		mR[0] = rCam.m_fVR[0], mR[1] = rCam.m_fVU[0], mR[2] = -rCam.m_fVD[0],mR[4] = rCam.m_fVR[1],mR[5] = rCam.m_fVU[1],mR[6] = -rCam.m_fVD[1],mR[8] = rCam.m_fVR[2],mR[9] = rCam.m_fVU[2],mR[10] = -rCam.m_fVD[2];
		mT[12] = -rCam.m_fVP[0],mT[13] = -rCam.m_fVP[1],mT[14] = -rCam.m_fVP[2];
		matMatMult(mR, mT, rCam.m_afMat);
	}
	return rCam.m_afMat;
}

float* camObjMatInv(raaCamera &rCam)
{
	if (rCam.m_bInvChanged)
	{
		rCam.m_bInvChanged = false;

		float mR[16], mT[16];
		matMakeIdentity(mR);
		matMakeIdentity(mT);
		mR[0] = rCam.m_fVR[0],mR[1] = rCam.m_fVR[1],mR[2] = rCam.m_fVR[2],mR[4] = rCam.m_fVU[0],mR[5] = rCam.m_fVU[1],mR[6] = rCam.m_fVU[2],mR[8] = -rCam.m_fVD[0],mR[9] = -rCam.m_fVD[1],mR[10] = -rCam.m_fVD[2];
		mT[12] = rCam.m_fVP[0],mT[13] = rCam.m_fVP[1],mT[14] = rCam.m_fVP[2];
		matMatMult(mT, mR, rCam.m_afInvMat);
	}

	return rCam.m_afInvMat;
}

float* camRotMat(raaCamera& rCam)
{
	if (rCam.m_bRotChanged)
	{
		rCam.m_bRotChanged = false;
		matMakeIdentity(rCam.m_afMat);
		rCam.m_afMat[0] = rCam.m_fVR[0], rCam.m_afMat[1] = rCam.m_fVU[0], rCam.m_afMat[2] = -rCam.m_fVD[0], rCam.m_afMat[4] = rCam.m_fVR[1], rCam.m_afMat[5] = rCam.m_fVU[1], rCam.m_afMat[6] = -rCam.m_fVD[1], rCam.m_afMat[8] = rCam.m_fVR[2], rCam.m_afMat[9] = rCam.m_fVU[2], rCam.m_afMat[10] = -rCam.m_fVD[2];
	}
	return rCam.m_afMat;
}

float* camRotMatInv(raaCamera& rCam)
{
	if (rCam.m_bRotInvChanged)
	{
		rCam.m_bRotInvChanged = false;

		
		
		
		(rCam.m_afInvMat);
		rCam.m_afInvMat[0] = rCam.m_fVR[0], rCam.m_afInvMat[1] = rCam.m_fVR[1], rCam.m_afInvMat[2] = rCam.m_fVR[2], rCam.m_afInvMat[4] = rCam.m_fVU[0], rCam.m_afInvMat[5] = rCam.m_fVU[1], rCam.m_afInvMat[6] = rCam.m_fVU[2], rCam.m_afInvMat[8] = -rCam.m_fVD[0], rCam.m_afInvMat[9] = -rCam.m_fVD[1], rCam.m_afInvMat[10] = -rCam.m_fVD[2];
	}
	return rCam.m_afInvMat;
}

void camExploreRotate( raaCamera &rCam, float fUp, float fRight )
{
	float af[]={0.0f, 0.0f, 0.0f, 0.0f};
	vecSub(rCam.m_fVT, rCam.m_fVP, af);
	float fLen=vecLength(af);

	vecProject(rCam.m_fVP, rCam.m_fVR, fRight, rCam.m_fVP);
	vecSub(rCam.m_fVT, rCam.m_fVP, rCam.m_fVD);
	vecNormalise(rCam.m_fVD, rCam.m_fVD);

	vecCrossProduct(rCam.m_fVD, rCam.m_fVU, rCam.m_fVR);
	vecNormalise(rCam.m_fVR, rCam.m_fVR);

	vecProject(rCam.m_fVP, rCam.m_fVU, fUp, rCam.m_fVP);
	vecSub(rCam.m_fVT, rCam.m_fVP, rCam.m_fVD);
	vecNormalise(rCam.m_fVD, rCam.m_fVD);

	vecCrossProduct(rCam.m_fVR, rCam.m_fVD, rCam.m_fVU);
	vecNormalise(rCam.m_fVU, rCam.m_fVU);

	vecProject(rCam.m_fVT, rCam.m_fVD, -fLen, rCam.m_fVP);

	camResolveUp(rCam);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged=rCam.m_bInvChanged=rCam.m_bChanged = true;
}

void camExploreTravel( raaCamera &rCam, float fDisp)
{
	float fLen;
	float aVec[4];
	vecInitDVec(aVec);
	vecSub(rCam.m_fVP, rCam.m_fVT, aVec);
	fLen=vecNormalise(aVec, aVec)+fDisp;
	if(fLen<rCam.m_fNear) fLen=rCam.m_fNear;
	if(fLen>rCam.m_fFar) fLen=rCam.m_fFar;
	vecProject(rCam.m_fVT, aVec, fLen, rCam.m_fVP);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camExplorePan(raaCamera& rCam, float fHori, float fVert)
{
	float aHVec[4];
	float aVVec[4];
	float aVec[4];
	vecInitDVec(aHVec);
	vecInitDVec(aVVec);
	vecInitDVec(aVec);
	vecScalarProduct(rCam.m_fVU, -fVert, aVVec);
	vecScalarProduct(rCam.m_fVR, -fHori, aHVec);
	vecAdd(aVVec, aHVec, aVVec);
	vecAdd(rCam.m_fVP, aVVec, rCam.m_fVP);
	vecAdd(rCam.m_fVT, aVVec, rCam.m_fVT);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camExploreUpdateTarget( raaCamera &rCam, float *pfTarget )
{
	if(pfTarget)
	{
		float fLen=vecDistance(rCam.m_fVP, rCam.m_fVT);
		vecCopy(pfTarget, rCam.m_fVT);
		vecProject(rCam.m_fVT, rCam.m_fVD, -fLen, rCam.m_fVP);
		rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
	}
}

void camExploreUpdateTargetAndDistance(raaCamera& rCam, float fDist, float* pfTarget)
{
	if (pfTarget)
	{
		vecCopy(pfTarget, rCam.m_fVT);
		vecProject(rCam.m_fVT, rCam.m_fVD, -fDist, rCam.m_fVP);
		rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
	}
}

void camFlyRotate( raaCamera &rCam, float fUp, float fRight )
{
	float af[]={0.0f, 0.0f, 0.0f, 0.0f};
	vecProject(af, rCam.m_fVR, fRight, af);
	vecAdd(rCam.m_fVD, af,rCam.m_fVD);
	vecNormalise(rCam.m_fVD, rCam.m_fVD);
	vecProject(rCam.m_fVP, rCam.m_fVD, 1.0f, rCam.m_fVT);
	vecCrossProduct(rCam.m_fVD, rCam.m_fVU, rCam.m_fVR);
	vecNormalise(rCam.m_fVR, rCam.m_fVR);
	vecProject(af, rCam.m_fVU, fUp, af);
	vecAdd(rCam.m_fVD, af, rCam.m_fVD);
	vecNormalise(rCam.m_fVD, rCam.m_fVD);
	vecProject(rCam.m_fVP, rCam.m_fVD, 1.0f, rCam.m_fVT);
	vecCrossProduct(rCam.m_fVR, rCam.m_fVD, rCam.m_fVU);
	vecNormalise(rCam.m_fVU, rCam.m_fVU);
	camResolveUp(rCam);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camFlyTravel( raaCamera &rCam, float fForward, float fHori, float fVert )
{
	float fLen=vecDistance(rCam.m_fVP, rCam.m_fVT);
	vecProject(rCam.m_fVP, rCam.m_fVD, fForward, rCam.m_fVP);
	vecProject(rCam.m_fVP, rCam.m_fVR, fHori, rCam.m_fVP);
	vecProject(rCam.m_fVP, rCam.m_fVU, fVert, rCam.m_fVP);
	vecProject(rCam.m_fVP, rCam.m_fVD, fLen, rCam.m_fVT);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camSLERP( raaCamera &rCamStart, raaCamera &rCamEnd, float fSlerp, raaCamera &rCam )
{
	vecSlerp(rCamStart.m_fVD, rCamEnd.m_fVD, fSlerp, rCam.m_fVD);
	vecNormalise(rCam.m_fVD, rCam.m_fVD);
	vecSlerp(rCamStart.m_fVU, rCamEnd.m_fVU, fSlerp, rCam.m_fVU);
	vecNormalise(rCam.m_fVU, rCam.m_fVU);
	vecSlerp(rCamStart.m_fVR, rCamEnd.m_fVR, fSlerp, rCam.m_fVR);
	vecNormalise(rCam.m_fVR, rCam.m_fVR);
	vecSlerp(rCamStart.m_fVP, rCamEnd.m_fVP, fSlerp, rCam.m_fVP);
	vecSlerp(rCamStart.m_fVT, rCamEnd.m_fVT, fSlerp, rCam.m_fVT);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camResolveUp( raaCamera &rCam )
{
	float av[]={0.0f, 1.0f, 0.0f, 0.0f};

	vecCrossProduct(rCam.m_fVD, av, rCam.m_fVR);
	vecNormalise(rCam.m_fVR, rCam.m_fVR);
	
	vecCrossProduct(rCam.m_fVR, rCam.m_fVD, rCam.m_fVU);
	vecNormalise(rCam.m_fVU, rCam.m_fVU);
	rCam.m_bRotInvChanged = rCam.m_bRotChanged = rCam.m_bInvChanged = rCam.m_bChanged = true;
}

void camPrint(raaCamera& rCam)
{
	printf("Camera --------------------------------\n");

	printf("VP %4.2f, %4.2f, %4.2f\n", rCam.m_fVP[0], rCam.m_fVP[1], rCam.m_fVP[2]);
	printf("VT %4.2f, %4.2f, %4.2f\n", rCam.m_fVT[0], rCam.m_fVT[1], rCam.m_fVT[2]);
	printf("VU %4.2f, %4.2f, %4.2f\n", rCam.m_fVU[0], rCam.m_fVU[1], rCam.m_fVU[2]);
	printf("VR %4.2f, %4.2f, %4.2f\n", rCam.m_fVR[0], rCam.m_fVR[1], rCam.m_fVR[2]);
	printf("VD %4.2f, %4.2f, %4.2f\n", rCam.m_fVD[0], rCam.m_fVD[1], rCam.m_fVD[2]);

	printf("End Camera ----------------------------\n");
}

bool renderProject(float fX, float fY, float fZ, float* pfMV, float* pfPV, int* piViewport, float* pfOutput) 
{
	float afTemp[8];

	afTemp[0] = pfMV[0] * fX + pfMV[4] * fY + pfMV[8] * fZ + pfMV[12]; 
	afTemp[1] = pfMV[1] * fX + pfMV[5] * fY + pfMV[9] * fZ + pfMV[13];
	afTemp[2] = pfMV[2] * fX + pfMV[6] * fY + pfMV[10] * fZ + pfMV[14];
	afTemp[3] = pfMV[3] * fX + pfMV[7] * fY + pfMV[11] * fZ + pfMV[15];

	afTemp[4] = pfPV[0] * afTemp[0] + pfPV[4] * afTemp[1] + pfPV[8] * afTemp[2] + pfPV[12] * afTemp[3];
	afTemp[5] = pfPV[1] * afTemp[0] + pfPV[5] * afTemp[1] + pfPV[9] * afTemp[2] + pfPV[13] * afTemp[3];
	afTemp[6] = pfPV[2] * afTemp[0] + pfPV[6] * afTemp[1] + pfPV[10] * afTemp[2] + pfPV[14] * afTemp[3];
	afTemp[7] = -afTemp[2];

	if (afTemp[7] == 0.0)	return false;

	afTemp[7] = 1.0f / afTemp[7];
	afTemp[4] *= afTemp[7];
	afTemp[5] *= afTemp[7];
	afTemp[6] *= afTemp[7];

	pfOutput[0] = (afTemp[4] * 0.5f + 0.5f)*piViewport[2] + piViewport[0];
	pfOutput[1] = (afTemp[5] * 0.5f + 0.5f)*piViewport[3] + piViewport[1];

	pfOutput[2] = (1.0f + afTemp[6])*0.5f;
	return true;
}

bool renderUnProject(float fX, float fY, float fZ, float* pfMV, float* pfPV, int* piViewport, float* pfOutput) 
{
	float m[16], A[16];
	float in[4], out[4];

	matMatMult(pfPV, pfMV, A);
	if (!matFullInvert(A, m)) return false;

	in[0] = (fX - (float)piViewport[0]) / (float)piViewport[2] * 2.0f - 1.0f;
	in[1] = (fY - (float)piViewport[1]) / (float)piViewport[3] * 2.0f - 1.0f;
	in[2] = 2.0f *fZ - 1.0f;
	in[3] = 1.0f;

	matVecMult(in, m, out);

	if (out[3] == 0.0f) return false;

	out[3] = 1.0f / out[3];
	pfOutput[0] = out[0] * out[3];
	pfOutput[1] = out[1] * out[3];
	pfOutput[2] = out[2] * out[3];
	return true;
}

void camInputInit( raaCameraInput &rInput )
{
	rInput.m_bExplore=false;
	rInput.m_bFly=false;
	rInput.m_bMouse=false;
	rInput.m_bMousePan = false;
	rInput.m_aiMouseStart[0]=0;
	rInput.m_aiMouseStart[1]=0;
	rInput.m_aiMouseLast[0]=0;
	rInput.m_aiMouseLast[1]=0;
	rInput.m_tbKeyTravel=tri_null;
	rInput.m_tbKeyPanHori=tri_null;
	rInput.m_tbKeyPanVert=tri_null;
	rInput.m_fAngularSensitivity=0.0002f;
	rInput.m_fLinearSensitivity=0.1f;
}

void camInputExplore( raaCameraInput &rInput, bool bState )
{
	rInput.m_bExplore=bState;
}

void camInputFly( raaCameraInput &rInput, bool bState )
{
	rInput.m_bFly=bState;
}

void camInputMouse( raaCameraInput &rInput, bool bState )
{
	rInput.m_bMouse=bState;
}

void camInputMousePan(raaCameraInput& rInput, bool bState)
{
	rInput.m_bMousePan = bState;
}

void camInputTravel( raaCameraInput &rInput, tribool tbState )
{
	rInput.m_tbKeyTravel=tbState;
}

void camInputPanHori( raaCameraInput &rInput, tribool tbState )
{
	rInput.m_tbKeyPanHori=tbState;
}

void camInputPanVert( raaCameraInput &rInput, tribool tbState )
{
	rInput.m_tbKeyPanVert=tbState;
}

void camInputSetMouseStart( raaCameraInput &rInput, int iX, int iY )
{
	rInput.m_aiMouseLast[0]=rInput.m_aiMouseStart[0]=iX;
	rInput.m_aiMouseLast[1]=rInput.m_aiMouseStart[1]=iY;
}

void camInputSetMouseLast( raaCameraInput &rInput, int iX, int iY )
{
	rInput.m_aiMouseLast[0]=iX;
	rInput.m_aiMouseLast[1]=iY;
}

int* camViewport(raaCamera& rCam)
{
	return rCam.m_aiViewport;
}

void camSetViewport(raaCamera& rCam, int iX, int iY, int iWidth, int iHeight)
{
	rCam.m_aiViewport[0] = iX;
	rCam.m_aiViewport[1] = iY;
	rCam.m_aiViewport[2] = iWidth;
	rCam.m_aiViewport[3] = iHeight;
	rCam.m_bViewportChanged = true;
}

bool camViewportChanged(raaCamera& rCam)
{
	return rCam.m_bViewportChanged;
}

void camResetViewportChanged(raaCamera& rCam)
{
	rCam.m_bViewportChanged = false;
}

void camProcessInput( raaCameraInput &rInput, raaCamera &rCam )
{
	float fDeltaX=0.0f;
	float fDeltaY=0.0f;

	float fTravel=(rInput.m_tbKeyTravel==tri_null) ? 0.0f : (rInput.m_tbKeyTravel==tri_pos) ? 1.0f : -1.0f;
	float fHori=(rInput.m_tbKeyPanHori==tri_null) ? 0.0f : (rInput.m_tbKeyPanHori==tri_pos) ? 1.0f : -1.0f;
	float fVert=(rInput.m_tbKeyPanVert==tri_null) ? 0.0f : (rInput.m_tbKeyPanVert==tri_pos) ? 1.0f : -1.0f;

	if(rInput.m_bFly)
	{
		fDeltaX = ((float)(rInput.m_aiMouseLast[0] - rInput.m_aiMouseStart[0]))*rInput.m_fAngularSensitivity;
		fDeltaY = ((float)(rInput.m_aiMouseLast[1] - rInput.m_aiMouseStart[1]))*rInput.m_fAngularSensitivity;
		camFlyRotate(rCam, fDeltaY, fDeltaX);
		camFlyTravel(rCam, fTravel*rInput.m_fLinearSensitivity, fHori*rInput.m_fLinearSensitivity, fVert*rInput.m_fLinearSensitivity);
	}
	else if(rInput.m_bExplore)
	{
		float vV[4];
		vecInitPVec(vV);
		vecSub(rCam.m_fVT, rCam.m_fVP, vV);
		float fLen = vecLength(vV);
		camExploreTravel(rCam, (fLen / 30.0f)*-fTravel*rInput.m_fLinearSensitivity);

		if (rInput.m_bMouse || rInput.m_bMousePan)
		{
			fDeltaX = ((float)(rInput.m_aiMouseLast[0] - rInput.m_aiMouseStart[0]));
			fDeltaY = ((float)(rInput.m_aiMouseLast[1] - rInput.m_aiMouseStart[1]));

			float fAngY = rInput.m_fAngularSensitivity*fDeltaY;
			if (fAngY>0.0f) fAngY = (fAngY > cs_fHalfPi) ? cs_fHalfPi : fAngY;
			else fAngY = (fAngY < -cs_fHalfPi) ? -cs_fHalfPi : fAngY;

			float fAngX = rInput.m_fAngularSensitivity*fDeltaX;
			if(fAngX>0.0f) fAngX = (fAngX > cs_fHalfPi) ? cs_fHalfPi : fAngX;
			else fAngX = (fAngX < -cs_fHalfPi) ? -cs_fHalfPi : fAngX;

			if (rInput.m_bMouse) camExploreRotate(rCam, fLen*tan(fAngY), fLen*tan(fAngX));
			if (rInput.m_bMousePan) camExplorePan(rCam, fDeltaX*rInput.m_fLinearSensitivity, fDeltaY*rInput.m_fLinearSensitivity);
		}
	}
	
}
