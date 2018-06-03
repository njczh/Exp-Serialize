#include "Serializer.h"

const char* Serializer::FILEPATH = "data";

bool Serializer::Serialize(const vector<Serializable*>& objects)
{
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, 0666); // 会减去umask
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
	//多个对象存在同一个文件中，使用同一个文件描述符，保证指针正确偏移
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
