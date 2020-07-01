#pragma once

#ifdef _DEBUG
#pragma comment(lib,"raaUtilitiesD")
#else
#pragma comment(lib,"raaUtilitiesR")
#endif

void utilitiesColourToMat(const float* pafCol, float fShininess, bool bEmisive=false);
float* utilitiesScreenProportionToViewport(float fX, float fY, int* aiViewport, float* pF);
