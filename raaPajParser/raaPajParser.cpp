#include "stdafx.h"
#include <stdio.h>
#include "raaPajParser.h"
#include <string.h>

const static unsigned int csg_uiParseNetwork = 1;
const static unsigned int csg_uiParseArcs = 2;
const static unsigned int csg_uiEdges = 3;
const static unsigned int csg_uiParsePartition = 4;
const static unsigned int csg_uiParseVector = 5;

void parse(const char* acFile, parseSectionFunction *pSectionFunction, parseNetworkFunction* pNetworkFunction, parseArcFunction *pArcFunction, parsePartitionFunction *pPartitionFunction, parseVectorFunction *pVectorFunction)
{
	unsigned int uiMode = 0;
	if (acFile)
	{
		FILE *pFile;
		fopen_s(&pFile, acFile, "r");

		if(pFile)
		{

			while(!feof(pFile))
			{
				char acLine[64];
				char *pcN = 0;
				fpos_t pos;


				fgetpos(pFile, &pos);
				fgets(acLine, 64, pFile);

				if (strlen(acLine)>1)
				{
					if (strchr(acLine, '*'))
					{
						char *acNext = 0;

						char acSection[32];
						char acDescription[32];
						char acType[32];
						char acCount[32];
						char *pC = 0;
						acSection[0] = acDescription[0] = acType[0] = acCount[0] = '\0';

						sprintf_s(acSection, "%s", strtok_s(acLine, " \n\t", &acNext));
						pC = strtok_s(0, " \n\t", &acNext);
						sprintf_s(acDescription, "%s", pC?pC:"\0");

						if (!strcmp(acSection, "*Network")) uiMode = csg_uiParseNetwork;
						else if (!strcmp(acSection, "*Arcs")) uiMode = csg_uiParseArcs;
						else if (!strcmp(acSection, "*Edges")) uiMode = csg_uiEdges;
						else if (!strcmp(acSection, "*Partition")) uiMode = csg_uiParsePartition;
						else if (!strcmp(acSection, "*Vector")) uiMode = csg_uiParseVector;
						else uiMode = 0;

						while (1)
						{
							fgetpos(pFile, &pos);
							fgets(acLine, 64, pFile);
							if(strlen(acLine))
							{
								if (strchr(acLine, '*'))
								{
									sprintf_s(acType, "%s", strtok_s(acLine, " \n\t", &acNext));
									sprintf_s(acCount, "%s", strtok_s(0, " \n\t", &acNext));
									break;
								}
								else
								{
									fsetpos(pFile, &pos);
									break;
								}
							}
						}

						if (pSectionFunction) pSectionFunction(acLine, acSection, acDescription, acType, acCount);

//						printf("Section %s -> %s :: %s, %s;\n", acSection, acDescription, acType, acCount);
					}
					else
					{
						if (strchr(acLine, '*')) fsetpos(pFile, &pos);
						else
						{
							switch(uiMode)
							{
								case csg_uiParseNetwork:
								{
									char acId[5];
									char acName[32];
									char acY[8];
									char acZ[8];
									char *acNext = 0;
									acId[0] = acName[0] = acY[0] = acZ[0] = '\0';

									sprintf_s(acId, "%s", strtok_s(acLine, " \t\"\n", &acNext));
									sprintf_s(acName, "%s", strtok_s(0, "\"\n", &acNext));
									sprintf_s(acY, "%s", strtok_s(0, " \t\"\n", &acNext));
									sprintf_s(acZ, "%s", strtok_s(0, " \t\"\n", &acNext));

									if (pNetworkFunction) pNetworkFunction(acLine, acId, acName, acY, acZ);

									//printf("Network -> %s::%s->%s, %s\n", acId, acName, acY, acZ);
								}
								break;
								case csg_uiParseArcs:
								{
									char acId0[5];
									char acId1[5];
									char acStrength[8];
									char *acNext = 0;
									acId0[0] = acId1[0] = acStrength[0] = '\0';

									sprintf_s(acId0, "%s", strtok_s(acLine, " \t\n", &acNext));
									sprintf_s(acId1, "%s", strtok_s(0, " \t\n", &acNext));
									sprintf_s(acStrength, "%s", strtok_s(0, " \t\"\n", &acNext));

									if (pArcFunction) pArcFunction(acLine, acId0, acId1, acStrength);

//									printf("Arc -> %s->%s::%s\n", acId0, acId1, acStrength);
								}
								break;
								case csg_uiEdges:
									break;
								case csg_uiParsePartition:
								{
									char acValue[32];
									char *acNext = 0;
									acValue[0] = '\0';

									sprintf_s(acValue, "%s", strtok_s(acLine, " \t\n", &acNext));

									if (pPartitionFunction) pPartitionFunction(acLine, acValue);

//									printf("Patition -> %s\n", acValue);
								}
								break;
								case csg_uiParseVector:
								{
									char acValue[32];
									char *acNext = 0;
									acValue[0] = '\0';

									sprintf_s(acValue, "%s", strtok_s(acLine, " \t\n", &acNext));

									if (pVectorFunction) pVectorFunction(acLine, acValue);

//									printf("Vector -> %s\n", acValue);
								}
								break;
								default:
									break;
							}
						}
					}
				}
			}
			fclose(pFile);
		}
	}
}
