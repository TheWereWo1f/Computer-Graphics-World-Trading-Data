#include "stdafx.h"
#include "raaLinkedList.h"

void initList(raaLinkedList* pList, unsigned int uiType)
{
	if(pList)
	{
		pList->m_pHead = 0;
		pList->m_pTail = 0;
		pList->m_uiType = uiType;
	}
}

void destroyList(raaLinkedList* pList, raaListDeletor* pDeletor)
{
	if(pList)
	{
		if(pDeletor) for(raaLinkedListElement *pE=pList->m_pHead;pE;pE=pE->m_pNext) pDeletor(pE);
		while(pList->m_pHead) delete popTail(pList);
	}
}

raaLinkedListElement* initElement(raaLinkedListElement* pElement, void* pData, unsigned uiType)
{
	if(pElement)
	{
		pElement->m_pNext = 0;
		pElement->m_pLast = 0;
		pElement->m_pData = pData;
		pElement->m_uiType = uiType;
	}
	return pElement;
}

raaLinkedListElement* destroyElement(raaLinkedListElement* pElement, raaListDeletor* pDeletor)
{
	if(pElement && !(pElement->m_pNext||pElement->m_pLast))
	{
		if (pDeletor) pDeletor(pElement);
		delete pElement;
		return 0;
	}
	return pElement;
}

void pushHead(raaLinkedList* pList, raaLinkedListElement* pElement)
{
	if (pList && pElement && !(pElement->m_pNext || pElement->m_pLast))
	{
		pElement->m_pNext = pList->m_pHead;
		if (!pList->m_pTail) pList->m_pTail = pElement;
		if (pList->m_pHead) pList->m_pHead->m_pLast = pElement;
		pList->m_pHead = pElement;
	}
}

void pushTail(raaLinkedList* pList, raaLinkedListElement* pElement)
{
	if (pList && pElement && !(pElement->m_pNext || pElement->m_pLast))
	{
		pElement->m_pLast = pList->m_pTail;
		if (!pList->m_pHead) pList->m_pHead = pElement;
		if (pList->m_pTail) pList->m_pTail->m_pNext = pElement;
		pList->m_pTail = pElement;
	}
}

raaLinkedListElement* head(raaLinkedList* pList)
{
	return pList ? pList->m_pHead : 0;
}

raaLinkedListElement* tail(raaLinkedList* pList)
{
	return pList ? pList->m_pTail : 0;
}

unsigned count(raaLinkedList* pList)
{
	unsigned int uiCount = 0;
	if(pList) for (raaLinkedListElement *pE = pList->m_pHead; pE; pE = pE->m_pNext, uiCount++);
	return uiCount;
}

raaLinkedListElement* item(raaLinkedList* pList, unsigned uiIndex)
{
	if (pList)
	{
		raaLinkedListElement *pE = pList->m_pHead;
		if(pE) for (; pE&&uiIndex; pE = pE->m_pNext);
		return pE;
	}
	return 0;
}

void visit(raaLinkedList* pList, raaListActor* pActor)
{
	if(pList && pActor) for (raaLinkedListElement *pE = pList->m_pHead; pE; pE = pE->m_pNext) pActor(pE);
}

raaLinkedListElement* popHead(raaLinkedList* pList)
{
	raaLinkedListElement *pE = 0;
	if(pList && pList->m_pHead)
	{
		pE = pList->m_pHead;
		if (pList->m_pHead == pList->m_pTail) pList->m_pHead = pList->m_pTail = 0;
		else
		{
			pList->m_pHead = pE->m_pNext;
			pList->m_pHead->m_pLast = 0;
			pE->m_pNext = 0;
		}
	}
	return pE;
}

raaLinkedListElement* popTail(raaLinkedList* pList)
{
	raaLinkedListElement *pE = 0;
	if (pList && pList->m_pTail)
	{
		pE = pList->m_pTail;
		if (pList->m_pHead == pList->m_pTail) pList->m_pHead = pList->m_pTail = 0;
		else
		{
			pList->m_pTail = pE->m_pLast;
			pList->m_pTail->m_pNext = 0;
			pE->m_pLast = 0;
		}
	}
	return pE;
}

bool insertBefore(raaLinkedList* pList, raaLinkedListElement *pCurrentElement, raaLinkedListElement *pNewElement)
{
	if(pList && pCurrentElement && pNewElement)
	{
		if (pCurrentElement == pList->m_pHead) pushHead(pList, pNewElement);
		else
		{
			pNewElement->m_pLast = pCurrentElement->m_pLast;
			pNewElement->m_pNext = pCurrentElement;
			pNewElement->m_pLast->m_pNext = pNewElement;
			pCurrentElement->m_pLast = pNewElement;
		}
		return true;
	}
	return false;
}

bool insertAfter(raaLinkedList* pList, raaLinkedListElement *pCurrentElement, raaLinkedListElement *pNewElement)
{
	if (pList && pCurrentElement && pNewElement)
	{
		if (pCurrentElement == pList->m_pTail) pushTail(pList, pNewElement);
		else
		{
			pNewElement->m_pNext = pCurrentElement->m_pNext;
			pNewElement->m_pLast = pCurrentElement;
			pNewElement->m_pNext->m_pLast = pNewElement;
			pCurrentElement->m_pNext = pNewElement;
		}
		return true;
	}
	return false;
}

bool remove(raaLinkedList* pList, raaLinkedListElement* pElement)
{
	if(pList && pElement)
	{
		if (pElement == pList->m_pHead) return popHead(pList) ? true: false;
		if (pElement == pList->m_pTail) return popTail(pList) ? true: false;
		
		pElement->m_pNext->m_pLast = pElement->m_pLast;
		pElement->m_pLast->m_pNext = pElement->m_pNext;
		pElement->m_pNext = 0;
		pElement->m_pLast = 0;
		return true;
	}
	return false;
}

bool isMember(raaLinkedList* pList, raaLinkedListElement* pElement)
{
	if (pList && pElement) for (raaLinkedListElement *pE = pList->m_pHead; pE; pE = pE->m_pNext) if (pE == pElement) return true;
	return false;
}

