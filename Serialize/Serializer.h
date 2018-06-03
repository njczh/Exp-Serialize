#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Serializable.h"
#include "ObjectA.h"
#include "ObjectB.h"

class Serializer
{
public:
	static const char* FILEPATH;

public:
	bool Serialize(const vector<Serializable*>&, const char *pFilePath = FILEPATH);
	bool Deserialize(vector<Serializable*>&, const char *pFilePath = FILEPATH);
};
