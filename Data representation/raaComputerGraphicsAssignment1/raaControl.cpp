#include <stdio.h>
#include "raaControl.h"


void controlInit(raaControl& rControl) 
{
	rControl.m_abFlags[csg_uiControlDrawGrid] = true;

	rControl.m_abFlagsChanged[csg_uiControlDrawGrid] = true;
}

bool controlActive(raaControl& rControl, unsigned uiIndex) 
{
	return rControl.m_abFlags[uiIndex];
}

void controlSet(raaControl& rControl, unsigned uiIndex, bool bValue) 
{
	rControl.m_abFlags[uiIndex] = bValue;
	rControl.m_abFlagsChanged[uiIndex] = true;
}

bool controlChanged(raaControl& rControl, unsigned uiIndex) 
{
	return rControl.m_abFlagsChanged[uiIndex];
}

void controlToggle(raaControl& rControl, unsigned uiIndex)
{
	rControl.m_abFlags[uiIndex] = !rControl.m_abFlags[uiIndex];
	rControl.m_abFlagsChanged[uiIndex] = true;
}

void controlChangeResetAll(raaControl& rControl)
{
	rControl.m_abFlagsChanged[csg_uiControlDrawGrid] = false;
}
