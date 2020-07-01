#pragma once

#ifdef _DEBUG
#pragma comment(lib,"raaLinkedListD")
#else
#pragma comment(lib,"raaLinkedListR")
#endif
typedef struct _raaLinkedListElement
{
	_raaLinkedListElement *m_pNext;
	_raaLinkedListElement *m_pLast;
	void *m_pData;
	unsigned int m_uiType;
} raaLinkedListElement;

typedef struct _raaLinkedList
{
	raaLinkedListElement *m_pHead;
	raaLinkedListElement *m_pTail;
	unsigned int m_uiType;
} raaLinkedList;

typedef void (raaListDeletor)(raaLinkedListElement *pElement);
typedef void (raaListActor)(raaLinkedListElement *pElement);

void initList(raaLinkedList *pList, unsigned int uiType=0);
void destroyList(raaLinkedList *pList, raaListDeletor *pDeletor=0);

raaLinkedListElement* initElement(raaLinkedListElement *pElement, void* pData = 0, unsigned int uiType = 0);
raaLinkedListElement* destroyElement(raaLinkedListElement *pElement, raaListDeletor *pDeletor=0);

void pushHead(raaLinkedList *pList, raaLinkedListElement *pElement);
void pushTail(raaLinkedList *pList, raaLinkedListElement *pElement);
raaLinkedListElement* head(raaLinkedList *pList);
raaLinkedListElement* tail(raaLinkedList *pList);
unsigned int count(raaLinkedList *pList);
raaLinkedListElement* item(raaLinkedList *pList, unsigned int uiIndex);
void visit(raaLinkedList *pList, raaListActor *pActor = 0);
raaLinkedListElement* popHead(raaLinkedList *pList);
raaLinkedListElement* popTail(raaLinkedList *pList);
bool insertBefore(raaLinkedList *pList, raaLinkedListElement *pCurrentElement, raaLinkedListElement *pNewElement);
bool insertAfter(raaLinkedList *pList, raaLinkedListElement *pCurrentElement, raaLinkedListElement *pNewElement);
bool remove(raaLinkedList *pList, raaLinkedListElement *pElement);
bool isMember(raaLinkedList *pList, raaLinkedListElement *pElement);

