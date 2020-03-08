#pragma once
// #include <string>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
using namespace cv;
class FileToVedio
{
private:
	ifstream fileIn;
	vector<unsigned char> data;
	Mat img;
	VideoWriter vedio;
	int currentPosition; // ����������ͼƬʱָʾ��ǰ��ȡ��λ��
	bool currentPrity = false;
	void DrawHead(int width, int height, int modusize);
	void ReadToMemory();
	void DrawImage(int width, int height, int modusize);
	void DrawBlock(int x, int y, int modusize, char color);
	void InitialFormat(int width, int height, int modusize); // ����λ��Ͷ����
public:
	FileToVedio(const char* filePath);
	void GenerateVedio(const char* vedioPath, int width, int height, int modusize);

};