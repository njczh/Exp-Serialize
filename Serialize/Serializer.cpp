#include "Serializer.h"

const char* Serializer::FILEPATH = "data";

bool Serializer::Serialize(const vector<Serializable*>& objects, const int fd)
{
	bool result = true;;

	for (int i = 0; i < objects.size(); i++)
	{
		int type = objects[i]->getType();
		if (write(fd, &type, sizeof(int)) == -1)
		{
			result = false;
			break;
		}

		if (objects[i]->Serialize(fd) == false)
		{
			result = false;
			break;
		}
	}

	return result;
}

bool Serializer::Deserialize(vector<Serializable*>& objects, const int fd)
{
	bool result = true;

	while (result)
	{
		int type, i;
		/* 反序列化类对象类型 */
		if (read(fd, &type, sizeof(int)) == -1)
			result = false;

		for (i = 0; i < typeTable.size(); i++)
		{
			/* 根据类型，去类型表里找到相应的反序列化方法 */
			if (typeTable[i]->getType() == type)
			{
				Serializable * pObject = typeTable[i]->DeserializeT(fd);

				if (pObject != nullptr)
					objects.push_back(pObject);
				else
					result = false;

				break;
			}
		}

		/* 如果没找到，失败退出 */
		if (i == typeTable.size())
			result = false;
	}

	return result;
}

bool Serializer::Serialize(const vector<Serializable*>& objects, const char *pFilePath)
{
	// O_RDWR	可读可写打开
	// O_CREAT	若此文件不存在则创建它。使用此选项时需要提供第三个参数mode，表示该文件的访问权限。
	//			文件权限由open的mode参数和当前进程的umask掩码共同决定
	// O_TRUNC	如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为0字节。
	int fd = open(pFilePath, O_RDWR | O_CREAT | O_TRUNC, 0666); // 会减去umask
	if (fd == -1)
		return false;

	bool result = Serialize(objects, fd);

	if (close(fd) == -1)
		return false;

	return result;
}

bool Serializer::Deserialize(vector<Serializable*>& objects, const char *pFilePath)
{

	/* 多个对象存在同一个文件中，使用同一个文件描述符，保证指针正确偏移 */
	int fd = open(pFilePath, O_RDWR);
	if (fd == -1)
		return false;

	bool result = Deserialize(objects, fd);

	if (close(fd) == -1)
		return false;

	return result;
}

// version 4.0 
// description：不同类类型注册
void Serializer::RegisterType(Serializable *type)
{
	this->typeTable.push_back(type);
}
