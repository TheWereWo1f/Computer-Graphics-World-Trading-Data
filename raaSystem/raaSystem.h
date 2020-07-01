#pragma once
#ifdef _DEBUG
#pragma comment(lib,"raaSystemD")
#else
#pragma comment(lib,"raaSystemR")
#endif

#include <raaLinkedList/raaLinkedList.h>
#include <raaMaths/raaVector.h>

typedef struct _raaSystem
{
	raaLinkedList m_llNodes;
	raaLinkedList m_llArcs;
} raaSystem;

typedef struct _raaNode
{
	unsigned int m_uiId;
	float m_afPosition[4];
	float m_fMass;
	unsigned int m_uiContinent;
	unsigned int m_uiWorldSystem;
	char m_acName[64];
	//My data structure
	float m_fResultantForce[4];
	float m_fVelocity[4];
	float m_fVec[4];

} raaNode;

typedef struct _raaArc
{
	raaNode *m_pNode0;
	raaNode *m_pNode1;
	float m_fSpringCoef;
	float m_fIdealLen;
} raaArc;

const static unsigned int csg_uiNode = 1;
const static unsigned int csg_uiArc = 2;

typedef void (nodeFunction)(raaNode *pNode);
typedef void (arcFunction)(raaArc *pArc);

void initSystem(raaSystem *pSystem);
raaNode* initNode(raaNode *pNode, unsigned int uiId, float *pfPosition, float fMass, const char *acName);
raaArc* initArc(raaArc *pArc, raaNode *pNode0, raaNode *pNode1, float fSpringCoef, float fIdealLen);

void addNode(raaSystem *pSystem, raaNode *pNode);
void addArc(raaSystem *pSystem, raaArc *pArc);

raaNode* nodeById(raaSystem *pSystem, unsigned int uiId);

void visitNodes(raaSystem *pSystem, nodeFunction* pNodeFunction);
void visitArcs(raaSystem *pSystem, arcFunction* pArcFunction);


