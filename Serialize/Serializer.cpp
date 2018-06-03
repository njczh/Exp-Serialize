#include "Serializer.h"

const char* Serializer::FILEPATH = "data";

bool Serializer::Serialize(const vector<Serializable*>& objects, const char *pFilePath)
{
	bool result = true;;
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_TRUNC, 0666); // ���ȥumask
	if (fd == -1)
		return false;

	for (int i = 0; i < objects.size(); i++) 
	{
		int type;
		objects[i]->getType(type);
		if (write(fd, &type, sizeof(int)) == -1) 
		{
			result = false;
			break;
		}

		if (objects[i]->Serialize(fd) == false)
		{
			result = false; 
			break;
		}
	}

	if (close(fd) == -1) result = false;

	return result;
}

bool Serializer::Deserialize(vector<Serializable*>& objects, const char *pFilePath)
{
	bool result = true;
	//����������ͬһ���ļ��У�ʹ��ͬһ���ļ�����������ָ֤����ȷƫ��
	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	while (result)
	{
		int type;
		if (read(fd, &type, sizeof(int)) == -1)
			result = false;

		Serializable * pObject;
		switch (type)
		{
		case 1:
			pObject = new ObjectA();
			break;
		case 2:
			pObject = new ObjectB();
			break;
		default:
			result = false;
			break;
		}
		if (pObject->Deserialize(fd))
			objects.push_back(pObject);
		else
			break;
	}

	if (close(fd) == -1) result = false;

	return result;

}
