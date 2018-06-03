#include <cstdio>
#include "ObjectA.h"
#include "Serializer.h"
#include "Serializable.h"

//版本2：将一个类的多个对象序列化到文件
int main(int argc, char* argv[])
{
	// 序列化到文件
	{
		ObjectA *objectA_1 = new ObjectA(1, 'a', 1.1);
		ObjectA *objectA_2 = new ObjectA(2, 'b', 2.2);

		vector<Serializable*> objects;

		objects.push_back(objectA_1);
		objects.push_back(objectA_2);

		Serializer sr;

		sr.Serialize(objects);

	}

	// 从文件反序列化
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