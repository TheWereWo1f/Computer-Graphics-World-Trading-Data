#include "raaConstants.h"

std::string constantContinentIndexToName(int i) 
{
	switch (i)
	{
		case 1: return "Africa";
		case 2: return "Asia";
		case 3: return "Europe";
		case 4: return "North America";
		case 5: return "Oceania";
		case 6: return "South America";
		default: return "Unknown";
	}
}
