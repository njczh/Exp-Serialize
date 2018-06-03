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

/****************************** 序列化相关 ******************************/

// version 1.0
// description：将一个类的一个对象（一个成员变量）序列化到文件
bool ObjectB::Serialize(const char *pFilePath) const
{
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // 会减去umask
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
// description：将文件中的一个类的一个对象（一个成员变量）反序列化
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
// description：将一个类的多个对象（多个成员变量）序列化到文件
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
// description：将文件中的一个类的多个对象（多个成员变量）反序列化
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
// description：获取类型以区分不同类对象
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

