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

/****************************** 序列化相关 ******************************/

// version 1.0
// description：将一个类的一个对象（一个成员变量）序列化到文件
bool ObjectC::Serialize(const char *pFilePath) const
{
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0666); // 会减去umask
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
// description：将文件中的一个类的一个对象（一个成员变量）反序列化
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
// description：将一个类的多个对象（多个成员变量）序列化到文件
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
// description：将文件中的一个类的多个对象（多个成员变量）反序列化
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
// description：获取类型以区分不同类对象
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

