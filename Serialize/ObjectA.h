#pragma once

#include <iostream>

#include "Serializable.h"

class ObjectA :
	public Serializable
{
private:
	int		i_a;
	char	c_a;
	double	d_a;

public:
	ObjectA();
	ObjectA(int, char, double);
	~ObjectA();

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

