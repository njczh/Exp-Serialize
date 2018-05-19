#pragma once

class MyObject
{
public:
	MyObject();
	~MyObject();
	virtual bool Serialize(const char*) = 0;
	virtual bool Deserialize(const char*) = 0;
	virtual void Print() = 0;
};

