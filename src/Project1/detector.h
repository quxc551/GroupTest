#pragma once
#include "FinderPatternFinder.h"

class Detector
{
public:
	Detector(Mat image);
	int Detect();
	unsigned short** GetBinaryData(int width, int height);
private:
	Mat image;
	FinderPatternInfo finderPatternInfo;
	double dx;
	double dy;
	int ProcessFinderPatternInfo(FinderPatternInfo info); //����ֵ����ʱ��
	Point2d CalcPosition(int width, int height, int x, int y);
	//~Detector();
};