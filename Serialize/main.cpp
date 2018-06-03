#include <cstdio>
#include "ObjectA.h"
#include "ObjectB.h"
#include "ObjectC.h"
#include "Serializer.h"
#include "Serializable.h"

//版本4：将三个不同类的多个对象序列化到文件（可拓展）
int main(int argc, char* argv[])
{
	/************************************** 序列化到文件 **************************************/
	{
		ObjectA *objectA_1 = new ObjectA(1, 'a', 1.1);
		ObjectA *objectA_2 = new ObjectA(2, 'a', 1.2);

		ObjectB *objectB_1 = new ObjectB(1, 'b', 2.1);
		ObjectB *objectB_2 = new ObjectB(2, 'b', 2.2); 

		ObjectC *objectC_1 = new ObjectC(3, 4, 'c', 'd', 3.1, 3.2);
		ObjectC *objectC_2 = new ObjectC(5, 6, 'e', 'f', 3.3, 3.4);


		vector<Serializable*> objects;

		objects.push_back(objectA_1);
		objects.push_back(objectA_2);
		objects.push_back(objectB_1);
		objects.push_back(objectB_2);
		objects.push_back(objectC_1);
		objects.push_back(objectC_2);

		Serializer sr;
		sr.Serialize(objects);

	}

	/************************************ 从文件反序列化 ************************************/
	{
		vector<Serializable*> objects;
		Serializer sr;

		ObjectA a;
		ObjectB b;
		ObjectC c;
		sr.RegisterType(&a);
		sr.RegisterType(&b);
		sr.RegisterType(&c);


		sr.Deserialize(objects);

		for (int i = 0; i < objects.size(); i++)
		{	
			Serializable * pObject;

			switch (objects[i]->getType())
			{
			case 1:
				pObject = dynamic_cast<ObjectA*>(objects[i]);
				if (pObject != NULL)
					((ObjectA*)pObject)->Print();
				break;
			case 2:
				pObject = dynamic_cast<ObjectB*>(objects[i]);
				if (pObject != NULL)
					((ObjectB*)pObject)->Print();
				break;
			case 3:
				pObject = dynamic_cast<ObjectC*>(objects[i]);
				if (pObject != NULL)
					((ObjectC*)pObject)->Print();
			default:
				break;
			}
		}
	}

	return 0;

}