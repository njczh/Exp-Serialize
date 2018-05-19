#include <cstdio>
#include "ObjectA.h"

int main()
{

	{
		ObjectA objectA(10);
		objectA.Serialize("data");
	}

	{
		ObjectA objectA;
		objectA.Deserialize("data");
		objectA.Print();
	}

	return 0;

}