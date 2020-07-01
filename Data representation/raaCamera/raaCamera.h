#pragma once
#ifdef _DEBUG
#pragma comment(lib,"raaCameraD")
#else
#pragma comment(lib,"raaCameraR")
#endif

enum tribool
{
	tri_null,
	tri_pos,
	tri_neg
};

typedef struct _raaCameraInput
{
	bool m_bExplore;
	bool m_bFly;
	bool m_bMouse;
	bool m_bMousePan;
	int m_aiMouseStart[2];
	int m_aiMouseLast[2];
	tribool m_tbKeyTravel;
	tribool m_tbKeyPanHori;
	tribool m_tbKeyPanVert;
	float m_fAngularSensitivity;
	float m_fLinearSensitivity;
} raaCameraInput;


typedef struct _raaCamera
{
	float m_fVP[4];
	float m_fVT[4];
	float m_fVR[4];
	float m_fVU[4];
	float m_fVD[4];
	float m_fNear;
	float m_fFar;
	float m_afMat[16];
	float m_afInvMat[16];
	float m_afRotMat[16];
	float m_afRotInvMat[16];
	bool m_bChanged;
	bool m_bInvChanged;
	bool m_bRotChanged;
	bool m_bRotInvChanged;
	float m_afProjMat[16];
	int m_aiViewport[4];
	bool m_bViewportChanged;
} raaCamera;

// input mode functions
void camInputInit(raaCameraInput &rInput);
void camInputExplore(raaCameraInput &rInput, bool bState);
void camInputFly(raaCameraInput &rInput, bool bState);
void camInputMouse(raaCameraInput &rInput, bool bState);
void camInputMousePan(raaCameraInput &rInput, bool bState);
void camInputTravel(raaCameraInput &rInput, tribool tbState);
void camInputPanHori(raaCameraInput &rInput, tribool tbState);
void camInputPanVert(raaCameraInput &rInput, tribool tbState);
void camInputSetMouseStart(raaCameraInput &rInput, int iX, int iY);
void camInputSetMouseLast(raaCameraInput &rInput, int iX, int iY);

void camProcessInput(raaCameraInput &rInput, raaCamera &rCam);
int* camViewport(raaCamera &rCam);
void camSetViewport(raaCamera &rCam, int iX, int iY, int iWidth, int iHeight);
bool camViewportChanged(raaCamera &rCam);
void camResetViewportChanged(raaCamera &rCam);

// basic functions
void camInit(raaCamera &rCam);
void camReset(raaCamera &rCam);
void camCopy(raaCamera &rIn, raaCamera &rOut);
void camApply(raaCamera &rCam);
float* camObjMat(raaCamera &rCam);
float* camObjMatInv(raaCamera &rCam);
float* camRotMat(raaCamera &rCam);
float* camRotMatInv(raaCamera &rCam);

// explore mode functions
void camExploreRotate(raaCamera &rCam, float fUp, float fRight);
void camExploreTravel(raaCamera &rCam, float fDisp);
void camExplorePan(raaCamera &rCam, float fHori, float fVert);
void camExploreUpdateTarget(raaCamera &rCam, float *pfTarget);
void camExploreUpdateTargetAndDistance(raaCamera &rCam, float fDist, float *pfTarget);

// fly mode functions
void camFlyRotate(raaCamera &rCam, float fUp, float fRight);
void camFlyTravel(raaCamera &rCam, float fForward, float fHori, float fVert);

// slerp
void camSLERP(raaCamera &rCamStart, raaCamera &rCamEnd, float fSlerp, raaCamera &rCam);

// internal use
void camResolveUp(raaCamera &rCam);
void camPrint(raaCamera &rCam);

bool renderProject(float fX, float fY, float fZ, float* pfMV, float* pfPV, int* piViewport, float* pfOutput);
bool renderUnProject(float fX, float fY, float fZ, float* pfMV, float* pfPV, int* piViewport, float* pfOutput);

void MultiplyMatrices4by4OpenGL_FLOAT(float* result, float* matrix1, float* matrix2);

void MultiplyMatrixByVector4by4OpenGL_FLOAT(float* resultvector, const float* matrix, const float* pvector);


//This code comes directly from GLU except that it is for float
bool glhInvertMatrixf2(float* m, float* out);
