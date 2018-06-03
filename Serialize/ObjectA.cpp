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

/****************************** 序列化相关 ******************************/

// version 1.0
// description：将一个类的一个对象（一个成员变量）序列化到文件
bool ObjectA::Serialize(const char *pFilePath) const
{
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // 会减去umask
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
// description：将文件中的一个类的一个对象（一个成员变量）反序列化
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
// description：将一个类的多个对象（多个成员变量）序列化到文件
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
// description：将文件中的一个类的多个对象（多个成员变量）反序列化
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

