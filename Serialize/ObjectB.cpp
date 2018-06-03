#include "ObjectB.h"

ObjectB::ObjectB()
{
	i_b = 0;
}

ObjectB::ObjectB(int i_b, char c_b, double d_b)
{
	this->i_b = i_b;
	this->c_b = c_b;
	this->d_b = d_b;
}

ObjectB::~ObjectB()
{
}

void ObjectB::Print() const
{
	std::cout << "i_b = " << i_b
		<< ",\tc_b = " << c_b
		<< ",\td_b = " << d_b << std::endl;
}

/****************************** ���л���� ******************************/

// version 1.0
// description����һ�����һ������һ����Ա���������л����ļ�
bool ObjectB::Serialize(const char *pFilePath) const
{
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // ���ȥumask
	if (fd == -1)
		return false;

	if (write(fd, &i_b, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 1.0
// description�����ļ��е�һ�����һ������һ����Ա�����������л�
bool ObjectB::Deserialize(const char *pFilePath)
{

	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	if (read(fd, &i_b, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 2.0
// description����һ����Ķ�����󣨶����Ա���������л����ļ�
bool ObjectB::Serialize(const int fd) const
{
	if (fd == -1)
		return false;

	if (write(fd, &i_b, sizeof(int)) == -1)
		return false;

	if (write(fd, &c_b, sizeof(char)) == -1)
		return false;

	if (write(fd, &d_b, sizeof(double)) == -1)
		return false;

	return true;
}

// version 2.0
// description�����ļ��е�һ����Ķ�����󣨶����Ա�����������л�
bool ObjectB::Deserialize(const int fd)
{
	if (-1 == fd)
		return false;

	int r;

	r = read(fd, &i_b, sizeof(int));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &c_b, sizeof(char));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &d_b, sizeof(double));
	if ((0 == r) || (-1 == r))
		return false;

	return true;
}

// version 3.0
// description����ȡ���������ֲ�ͬ�����
int ObjectB::getType()
{
	return 2;
}

// version 4.0
Serializable * ObjectB::DeserializeT(const int fd)
{
	ObjectB * object = new ObjectB();

	if (object->Deserialize(fd))
		return object;
	else
		return nullptr;
}

