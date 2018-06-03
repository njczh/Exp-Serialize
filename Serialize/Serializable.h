#pragma once
#include <fcntl.h>
#include <unistd.h>

class Serializable
{
public:
	// ���������л����ļ�����������ʾ���ļ�
	virtual bool Serialize(const int fd) const = 0;
	// ���ļ���������ʾ���ļ������л�
	virtual bool Deserialize(const int fd) = 0;
	// ��ȡ���������ֲ�ͬ�����
	virtual int getType() = 0;
	// ���ļ���������ʾ���ļ������л��������ظö���ָ��
	virtual Serializable* DeserializeT(const int fd) = 0;
};

