#include "Serializer.h"

const char* Serializer::FILEPATH = "data";

bool Serializer::Serialize(const vector<Serializable*>& objects)
{
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, 0666); // ���ȥumask
	if (fd == -1)
		return false;

	for (int i = 0; i < objects.size(); i++) 
	{
		if (!objects[i]->Serialize(fd))
			return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

bool Serializer::Deserialize(vector<Serializable*>& objects)
{
	//����������ͬһ���ļ��У�ʹ��ͬһ���ļ�����������ָ֤����ȷƫ��
	int fd = open(FILEPATH, O_RDWR);
	if (fd == -1)
		return false;

	while(true) 
	{
		Serializable *pObject = new ObjectA();
		if (pObject->Deserialize(fd)) 		
			objects.push_back(pObject);
		else
			break;
	}

	if (close(fd) == -1)
		return false;

	return true;
}
