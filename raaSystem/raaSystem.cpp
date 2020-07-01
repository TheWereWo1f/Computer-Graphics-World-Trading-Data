#include "stdafx.h"
#include <math.h>
#include "raaSystem.h"
#include <streambuf>

void initSystem(raaSystem* pSystem)
{
	if(pSystem)
	{
		initList(&(pSystem->m_llArcs), csg_uiArc);
		initList(&(pSystem->m_llNodes), csg_uiNode);
	}
}

raaNode* initNode(raaNode* pNode, unsigned int uiId, float* pfPosition, float fMass, const char* acName)
{
	if(pNode)
	{
		vecInitPVec(pNode->m_afPosition);
		vecCopy(pfPosition, pNode->m_afPosition);
		pNode->m_fMass = fMass;
		sprintf_s(pNode->m_acName, "%s", acName);
		pNode->m_uiId = uiId;
		pNode->m_uiContinent = 0;
		pNode->m_uiWorldSystem = 0;
		pNode->m_fResultantForce;
		vecInitDVec(pNode->m_fVelocity);
		pNode->m_fVec;

	}

	return pNode;
}

raaArc* initArc(raaArc* pArc, raaNode* pNode0, raaNode* pNode1, float fSpringCoef, float fIdealLen)
{
	if(pArc)
	{
		pArc->m_pNode0 = pNode0;
		pArc->m_pNode1 = pNode1;
		pArc->m_fSpringCoef = fSpringCoef;
		pArc->m_fIdealLen = 100.0f;
	}
	return pArc;
}

void addNode(raaSystem* pSystem, raaNode* pNode)
{
	if(pSystem && pNode) pushTail(&(pSystem->m_llNodes), initElement(new raaLinkedListElement, pNode, csg_uiNode));
}

void visitArcs(raaSystem* pSystem, arcFunction* pArcFunction)
{
	if (pSystem && pArcFunction)
	{
		for (raaLinkedListElement *pE = pSystem->m_llArcs.m_pHead; pE; pE = pE->m_pNext)
		{
			if (pE->m_uiType == csg_uiArc && pE->m_pData)
			{
				pArcFunction((raaArc*)pE->m_pData);
			}
		}
	}
}

void visitNodes(raaSystem* pSystem, nodeFunction* pNodeFunction)
{
	if(pSystem && pNodeFunction)
	{
		for(raaLinkedListElement *pE=pSystem->m_llNodes.m_pHead;pE;pE=pE->m_pNext)
		{
			if(pE->m_uiType==csg_uiNode && pE->m_pData)
			{
				pNodeFunction((raaNode*)pE->m_pData);
			}
		}
	}
}

raaNode* nodeById(raaSystem *pSystem, unsigned int uiId)
{
	if(pSystem && uiId)
		for(raaLinkedListElement *pE=pSystem->m_llNodes.m_pHead;pE;pE=pE->m_pNext)
			if (pE->m_uiType == csg_uiNode && pE->m_pData && ((raaNode*)pE->m_pData)->m_uiId == uiId) return (raaNode*)pE->m_pData;
	return 0;
}

void addArc(raaSystem* pSystem, raaArc* pArc)
{
	if (pSystem && pArc) pushTail(&(pSystem->m_llArcs), initElement(new raaLinkedListElement, pArc, csg_uiArc));
}
