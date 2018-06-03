#include "ObjectC.h"

ObjectC::ObjectC()
{
	i_c1 = 0;
}

ObjectC::ObjectC(int i_c1, int i_c2, char c_c1, char c_c2, double d_c1, double d_c2)
{
	this->i_c1 = i_c1;
	this->i_c2 = i_c2;
	this->c_c1 = c_c1;
	this->c_c2 = c_c2;
	this->d_c1 = d_c1;
	this->d_c2 = d_c2;
}

ObjectC::~ObjectC()
{
}

void ObjectC::Print() const
{
	std::cout << "i_c1 = " << i_c1
		<< ",\ti_c2 = " << i_c2
		<< ",\tc_c1 = " << c_c1
		<< ",\tc_c2 = " << c_c2
		<< ",\td_c1 = " << d_c1
		<< ",\td_c2 = " << d_c2 << std::endl;
}

/****************************** ���л���� ******************************/

// version 1.0
// description����һ�����һ������һ����Ա���������л����ļ�
bool ObjectC::Serialize(const char *pFilePath) const
{
	// O_RDWR	�ɶ���д��
	// O_CREAT	�����ļ��������򴴽�����ʹ�ô�ѡ��ʱ��Ҫ�ṩ����������mode����ʾ���ļ��ķ���Ȩ�ޡ�
	//			�ļ�Ȩ����open��mode�����͵�ǰ���̵�umask���빲ͬ����
	// O_TRUNC	����ļ��Ѵ��ڣ�������ֻд��ɶ���д��ʽ�򿪣����䳤�Ƚضϣ�Truncate��Ϊ0�ֽڡ�
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // ���ȥumask
	if (fd == -1)
		return false;

	if (write(fd, &i_c1, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 1.0
// description�����ļ��е�һ�����һ������һ����Ա�����������л�
bool ObjectC::Deserialize(const char *pFilePath)
{

	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	if (read(fd, &i_c1, sizeof(int)) == -1) {
		close(fd);
		return false;
	}

	if (close(fd) == -1)
		return false;

	return true;
}

// version 2.0
// description����һ����Ķ�����󣨶����Ա���������л����ļ�
bool ObjectC::Serialize(const int fd) const
{
	if (fd == -1)
		return false;

	if (write(fd, &i_c1, sizeof(int)) == -1)
		return false;
	if (write(fd, &i_c2, sizeof(int)) == -1)
		return false;

	if (write(fd, &c_c1, sizeof(char)) == -1)
		return false;
	if (write(fd, &c_c2, sizeof(char)) == -1)
		return false;

	if (write(fd, &d_c1, sizeof(double)) == -1)
		return false;
	if (write(fd, &d_c2, sizeof(double)) == -1)
		return false;

	return true;
}

// version 2.0
// description�����ļ��е�һ����Ķ�����󣨶����Ա�����������л�
bool ObjectC::Deserialize(const int fd)
{
	if (-1 == fd)
		return false;

	int r;

	r = read(fd, &i_c1, sizeof(int));
	if ((0 == r) || (-1 == r))
		return false;
	r = read(fd, &i_c2, sizeof(int));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &c_c1, sizeof(char));
	if ((0 == r) || (-1 == r))
		return false;
	r = read(fd, &c_c2, sizeof(char));
	if ((0 == r) || (-1 == r))
		return false;

	r = read(fd, &d_c1, sizeof(double));
	if ((0 == r) || (-1 == r))
		return false;
	r = read(fd, &d_c2, sizeof(double));
	if ((0 == r) || (-1 == r))
		return false;
	return true;
}

// version 3.0
// description����ȡ���������ֲ�ͬ�����
int ObjectC::getType()
{
	return 3;
}

// version 4.0
Serializable * ObjectC::DeserializeT(const int fd)
{
	ObjectC * object = new ObjectC();
	
	if (object->Deserialize(fd))
		return object;
	else
		return nullptr;
}

