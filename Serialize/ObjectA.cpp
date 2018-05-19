#include "ObjectA.h"


ObjectA::ObjectA()
{
	a = 0;
}

ObjectA::ObjectA(int a)
{
	this->a = a;
}

ObjectA::~ObjectA()
{
}

bool ObjectA::Serialize(const char *pFilePath)
{
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_TRUNC, 0666); // ���ȥ
	if (fd == -1)
		return false;

	if (write(fd, &a, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}


bool ObjectA::Deserialize(const char *pFilePath)
{

	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	if (read(fd, &a, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

void ObjectA::Print()
{
	cout << "a = " << a << endl;
}
