#include <cstdio>
#include "ObjectA.h"
#include "ObjectB.h"
#include "ObjectC.h"
#include "Serializer.h"
#include "Serializable.h"
#include "Socket.h"

void Serialize(int fd);
void Deserialize(int);

//版本5：序列化的目的地不仅可以是文件，还可以是其他，即可配置性
int main(int argc, char* argv[])
{
	char *service = "6614";		// service name or port number	
	struct sockaddr_in fsin;	// the address of a client	
	unsigned int alen;			// length of client's address	
	int	msock;					// master server socket		
	int	ssock;					// slave server socket		

	switch (fork()) {
	case 0:
		/***** child *****/
		Serialize(connectTCP("127.0.0.1", service));
		break;
	default:
		/***** parent *****/
		msock = passiveTCP(service, QLEN);
	
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if (ssock < 0) {
			if (errno == EINTR)
				break;
			errexit("accept: %s\n", strerror(errno));
		}
		switch (fork()) {
		case 0:
			/***** child *****/
			(void)close(msock);
			Deserialize(ssock);
			exit(0);
		default:
			/***** parent *****/
			(void)close(ssock);
			break;
		case -1:
			errexit("fork: %s\n", strerror(errno));
		}

		break;
	case -1:
		errexit("fork: %s\n", strerror(errno));
	}
}

void Serialize(int fd) 
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

	sr.Serialize(objects, fd);
}

void Deserialize(int fd)
{
	vector<Serializable*> objects;
	Serializer sr;

	ObjectA a;
	ObjectB b;
	ObjectC c;
	sr.RegisterType(&a);
	sr.RegisterType(&b);
	sr.RegisterType(&c);

	sr.Deserialize(objects, fd);

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