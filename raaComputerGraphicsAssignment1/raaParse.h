#pragma once

void parseSection(const char* acRaw, const char* acSection, const char* acDescription, const char* acType, const char* acData);
void parseNetwork(const char* acRaw, const char* acId, const char* acName, const char* acY, const char* acZ);
void parseArc(const char* acRaw, const char* acId0, const char* acId1, const char* acStrength);
void parsePartition(const char* acRaw, const char* acValue);
void parseVector(const char* acRaw, const char* acValue);


