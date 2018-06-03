#pragma once

#include <iostream>

#include "Serializable.h"

class ObjectC :
	public Serializable
{
private:
  int i_c1;
  int i_c2;  

  char c_c1;
  char c_c2;
  
  double d_c1;
  double d_c2;

public:
	ObjectC();
	ObjectC(int, int, char, char, double, double);
	~ObjectC();

public:
	// version 1.0
	bool Serialize(const char* pFilePath) const;
	bool Deserialize(const char* pFilePath);

	// version 2.0
	bool Serialize(const int fd) const;
	bool Deserialize(const int fd);

	// version 3.0
	int	 getType();

	// version 4.0
	Serializable* DeserializeT(const int fd);

public:
	void Print() const;
};

