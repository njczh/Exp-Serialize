#pragma once

#include <iostream>

#include "Serializable.h"

class ObjectB :
	public Serializable
{
private:
	int		i_b;
	char	c_b;
	double	d_b;

public:
	ObjectB();
	ObjectB(int, char, double);
	~ObjectB();

public:
	// version 1.0
	bool Serialize(const char* pFilePath) const;
	bool Deserialize(const char* pFilePath);

	// version 2.0
	bool Serialize(const int fd) const;
	bool Deserialize(const int fd);

	// version 3.0
	void getType(int &type);

public:
	void Print() const;
};

