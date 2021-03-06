#pragma once
#include <fcntl.h>
#include <unistd.h>

class Serializable
{
public:
	// 将对象序列化到文件描述符所表示的文件
	virtual bool Serialize(const int fd) const = 0;
	// 由文件描述符表示的文件反序列化
	virtual bool Deserialize(const int fd) = 0;
	// 获取类型以区分不同类对象
	virtual int getType() = 0;
	// 由文件描述符表示的文件反序列化，并返回该对象指针
	virtual Serializable* DeserializeT(const int fd) = 0;
};

