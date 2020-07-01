#pragma once
#include "raaConstants.h"

typedef struct _raaControl
{
	bool m_abFlags[csg_uiControlNumFlags];
	bool m_abFlagsChanged[csg_uiControlNumFlags];
	char m_acLayout[csg_uiDefaultStringLength];
} raaControl;

void controlInit(raaControl& rControl);
bool controlActive(raaControl& rControl, unsigned int uiIndex);
void controlSet(raaControl& rControl, unsigned int uiIndex, bool bValue);
bool controlChanged(raaControl& rControl, unsigned int uiIndex);
void controlChangeResetAll(raaControl& rControl);
void controlToggle(raaControl &rControl, unsigned int uiIndex);
