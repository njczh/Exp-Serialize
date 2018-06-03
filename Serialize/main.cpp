#include <cstdio>
#include "ObjectA.h"
#include "Serializer.h"
#include "Serializable.h"

//�汾2����һ����Ķ���������л����ļ�
int main(int argc, char* argv[])
{
	// ���л����ļ�
	{
		ObjectA *objectA_1 = new ObjectA(1, 'a', 1.1);
		ObjectA *objectA_2 = new ObjectA(2, 'b', 2.2);

		vector<Serializable*> objects;

		objects.push_back(objectA_1);
		objects.push_back(objectA_2);

		Serializer sr;

		sr.Serialize(objects);

	}

	// ���ļ������л�
	{
		vector<Serializable*> objects;
		
		Serializer sr;

		sr.Deserialize(objects);

		ObjectA *objectA_1 = new ObjectA();
		ObjectA *objectA_2 = new ObjectA();

		objectA_1 = dynamic_cast<ObjectA*>(objects[0]);
		if (objectA_1 != NULL)
			objectA_1->Print();

		objectA_2 = dynamic_cast<ObjectA*>(objects[1]);
		if (objectA_2 != NULL)
			objectA_2->Print();
	}

	return 0;

}