#include "ObjectA.h"

ObjectA::ObjectA()
{
	i_a = 0;
}

ObjectA::ObjectA(int i_a, char c_a, double d_a)
{
	this->i_a = i_a;
	this->c_a = c_a;
	this->d_a = d_a;
}

ObjectA::~ObjectA()
{
}

void ObjectA::Print() const
{
	std::cout << "i_a = " << i_a
		<< ",\tc_a = " << c_a
		<< ",\td_a = " << d_a << std::endl;
}

/****************************** ���л���� ******************************/

// version 1.0
// description����һ�����һ������һ����Ա���������л����ļ�
bool ObjectA::Serialize(const char *pFilePath) const
{
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // ���ȥumask
	if (fd == -1)
		return false;

	if (write(fd, &i_a, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 1.0
// description�����ļ��е�һ�����һ������һ����Ա�����������л�
bool ObjectA::Deserialize(const char *pFilePath)
{

	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	if (read(fd, &i_a, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 2.0
// description����һ����Ķ�����󣨶����Ա���������л����ļ�
bool ObjectA::Serialize(const int fd) const
{
	if (fd == -1)
		return false;

	if (write(fd, &i_a, sizeof(int)) == -1)
		return false;

	if (write(fd, &c_a, sizeof(char)) == -1)
		return false;

	if (write(fd, &d_a, sizeof(double)) == -1)
		return false;

	return true;
}

// version 2.0
// description�����ļ��е�һ����Ķ�����󣨶����Ա�����������л�
bool ObjectA::Deserialize(const int fd)
{
	if (-1 == fd)
		return false;

	int r;

	r = read(fd, &i_a, sizeof(int));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &c_a, sizeof(char));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &d_a, sizeof(double));
	if ((0 == r) || (-1 == r))
		return false;

	return true;
}

// version 3.0
// description����ȡ���������ֲ�ͬ�����
int ObjectA::getType()
{
	return 1;
}

// version 4.0
// desription�����ļ���������ʾ���ļ������л��������ظö���ָ��
Serializable * ObjectA::DeserializeT(const int fd)
{
	ObjectA * object = new ObjectA();

	if (object->Deserialize(fd))
		return object;
	else
		return nullptr;
}

