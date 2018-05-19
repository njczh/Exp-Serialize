#pragma once

#include "MyObject.h"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;

class ObjectA :
	public MyObject
{
private:
	int a;
public:
	ObjectA();
	ObjectA(int);
	~ObjectA();
	bool Serialize(const char*);
	bool Deserialize(const char*);
	void Print();
};

