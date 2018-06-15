#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Serializable.h"

class Serializer
{
public:
	static const char* FILEPATH;

public:
	bool Serialize(const vector<Serializable*>&, const int fd);
	bool Deserialize(vector<Serializable*>&, const int fd);
	bool Serialize(const vector<Serializable*>&, const char *pFilePath = FILEPATH);
	bool Deserialize(vector<Serializable*>&, const char *pFilePath = FILEPATH);

public:
	void RegisterType(Serializable*);

private:
	vector<Serializable*> typeTable;
};
