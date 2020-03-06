#pragma once
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <bitset>

using namespace cv;
using namespace std;

class FileToMp4 {
private:
	void Trans(FILE* readFp, FILE* writeFp);//�ļ���У���� ת������ ���ļ�
	void Draw_Template(Mat img, int col, int row, int blockSize);//����λ�� �����
	int chksum(void *dataptr, unsigned short len);//У����
	void Draw(int length, int width, int blockSize);//�����ƻ�ͼ
	void Draw_White_block(Mat img, int pt0, int pt1, int blockSize);
	void ffmpeg(int frameRate);//ͼƬת��Ƶ
public:
	void MakePictureSequence();
};