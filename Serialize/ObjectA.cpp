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
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_TRUNC, 0666); // 会减去
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
