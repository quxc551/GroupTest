#include "FileToVedio.h"

void FileToVedio::DrawHead(int width, int height, int modusize)
{
	// ������ͼƬд���ݵ�ͷ��
}

void FileToVedio::ReadToMemory()
{
	fileIn.seekg(0, ios::end);
	int fileLength = fileIn.tellg();
	fileIn.seekg(0, ios::beg);
	for(int i=0;i< (int)(fileLength/18);i++)
	{
		unsigned int accumulate = 0;
		unsigned short checksum = 0;
		for (int j=0; j < 9; j++)
		{
			fileIn.read((char*)&checksum, 2);
			accumulate += checksum;
			data.push_back(checksum);
			data.push_back(checksum >> 8);
		}
		unsigned short carry = accumulate >> 16;
		checksum = ~(accumulate + carry);
		data.push_back(checksum);
		data.push_back(checksum >> 8);
	}
	// ��ʣ�೤�Ȳ���18�ֽ�
	int i = 0;
	while (!fileIn.eof())
	{
		char temp;
		fileIn.read(&temp, 1);
		data.push_back(temp);
		++i;
	}
	while (i<18)
	{
		data.push_back(0);
		++i;
	}
}

void FileToVedio::DrawImage(int width, int height, int modusize)
{
	InitialFormat(width, height, modusize);
	DrawHead(width,height, modusize);
	// д��ͷ�������д������ֱ��ͼƬ����
}

void FileToVedio::DrawBlock(int x, int y, int modusize, char color)
{

}

void FileToVedio::InitialFormat(int width, int height, int modusize)
{
}

void FileToVedio::GenerateVedio(const char* vedioPath, int width, int height, int modusize)
{
	// Ӧ����ʼ�� vedio
	ReadToMemory();
	DrawImage(width, height, modusize);
	// �ѻ�����ͼ�����vedio
}

FileToVedio::FileToVedio(const char* filePath)
{
	fileIn.open(filePath, ios::binary);
}
