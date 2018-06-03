#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Serializable.h"
#include "ObjectA.h"

class Serializer
{
public:
	static const char* FILEPATH;

public:
	bool Serialize(const vector<Serializable*>&);
	bool Deserialize(vector<Serializable*>&);
};
