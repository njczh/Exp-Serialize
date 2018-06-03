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
		ObjectA *objectA_2 = new ObjectA(2, 'a', 1.2);

		ObjectB *objectB_1 = new ObjectB(1, 'b', 2.1);
		ObjectB *objectB_2 = new ObjectB(2, 'b', 2.2);

		vector<Serializable*> objects;


		objects.push_back(objectA_1);
		objects.push_back(objectA_2);
		objects.push_back(objectB_1);
		objects.push_back(objectB_2);

		Serializer sr;

		sr.Serialize(objects);

	}

	// 从文件反序列化
	{
		vector<Serializable*> objects;
		
		Serializer sr;

		sr.Deserialize(objects);

		for (int i = 0; i < objects.size(); i++)
		{
			int type;
			objects[i]->getType(type);
			Serializable * pObject;
			switch (type)
			{
			case 1:
				pObject = (ObjectA*)objects[i];
				if (pObject != NULL)
					((ObjectA*)pObject)->Print();
				break;
			case 2:
				pObject = (ObjectB*)objects[i];
				if (pObject != NULL)
					((ObjectB*)pObject)->Print();
				break;
			default:
				break;
			}
		}
	}

	return 0;

}