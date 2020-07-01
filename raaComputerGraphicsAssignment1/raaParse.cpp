#include <string.h>
#include <stdlib.h>

#include <raaSystem/raaSystem.h>
#include <raaMaths/raaMaths.h>

#include "raaConstants.h"
#include "raaParse.h"


extern raaSystem g_System;

unsigned int g_uiParseMode = 0;
unsigned int g_uiParseField = 0;
unsigned int g_uiParseCount = 0;

void parseSection(const char* acRaw, const char* acSection, const char* acDescription, const char* acType, const char* acData) 
{
	if (!strcmp(acSection, "*Network")) g_uiParseMode = csg_uiParseNetwork;
	else if (!strcmp(acSection, "*Vector"))
	{
		g_uiParseMode = csg_uiParseVector;
		g_uiParseCount = 1;

		if (!strcmp(acDescription, "x_coordinates")) g_uiParseField = csg_uiParseXCoord;
		else if (!strcmp(acDescription, "GDP_1995.vec")) g_uiParseField = csg_uiParseGDP;
	}
	else if (!strcmp(acSection, "*Partition"))
	{
		g_uiParseMode = csg_uiParsePartition;
		g_uiParseCount = 1;

		if (!strcmp(acDescription, "Continent")) g_uiParseField = csg_uiParseContinent;
		else if (!strcmp(acDescription, "World_system")) g_uiParseField = csg_uiParseWorldSystem;
	}
	else g_uiParseMode = 0;
}

void parseNetwork(const char* acRaw, const char* acId, const char* acName, const char* acY, const char* acZ) 
{
	float afPos[] = { 0.0f, (float)atof(acY)*csg_afParseLayoutScale[csg_uiY], (float)atof(acZ)*csg_afParseLayoutScale[csg_uiZ], 1.0f };
	addNode(&g_System, initNode(new raaNode, atoi(acId), afPos, csg_fParseDefaultMass, acName));
}

void parseArc(const char* acRaw, const char* acId0, const char* acId1, const char* acStrength) 
{
	raaNode *pN0 = nodeById(&g_System, atoi(acId0));
	raaNode *pN1 = nodeById(&g_System, atoi(acId1));

	if (pN0 && pN1) addArc(&g_System, initArc(new raaArc, pN0, pN1, (float)atof(acStrength), csg_fParseDefaultSize));
}

void parsePartition(const char* acRaw, const char* acValue) 
{
	int iValue = atoi(acValue);

	if (g_uiParseField == csg_uiParseContinent)
	{
		raaNode *pNode = nodeById(&g_System, g_uiParseCount++);
		if (pNode) pNode->m_uiContinent = iValue;
	}
	else if (g_uiParseField == csg_uiParseWorldSystem)
	{
		raaNode *pNode = nodeById(&g_System, g_uiParseCount++);
		if (pNode) pNode->m_uiWorldSystem = iValue;
	}
}

void parseVector(const char* acRaw, const char* acValue) 
{
	float fValue = (float)atof(acValue);

	if (g_uiParseField == csg_uiParseXCoord)
	{
		raaNode *pNode = nodeById(&g_System, g_uiParseCount++);

		if (pNode) pNode->m_afPosition[csg_uiX] = fValue*800.0f;
	}
	else if (g_uiParseField == csg_uiParseGDP)
	{
		raaNode *pNode = nodeById(&g_System, g_uiParseCount++);

		if (pNode) pNode->m_fMass = fValue;
	}
}
