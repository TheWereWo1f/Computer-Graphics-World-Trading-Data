#pragma once
#ifdef _DEBUG
#pragma comment(lib,"raaPajParserD")
#else
#pragma comment(lib,"raaPajParserR")
#endif

typedef void (parseSectionFunction)(const char *acRaw, const char* acSection, const char* acDescription, const char *acType, const char* acData);
typedef void (parseNetworkFunction)(const char *acRaw, const char* acId, const char* acName, const char *acY, const char* acZ);
typedef void (parseArcFunction)(const char *acRaw, const char* acId0, const char* acId1, const char *acStrength);
typedef void (parsePartitionFunction)(const char *acRaw, const char* acValue);
typedef void (parseVectorFunction)(const char *acRaw, const char* acValue);

void parse(const char* acFile, parseSectionFunction *pSectionFunction, parseNetworkFunction* pNetworkFunction, parseArcFunction *pArcFunction, parsePartitionFunction *pPartitionFunction=0, parseVectorFunction *pVectorFunction=0);

