#pragma once
#include "FinderPatternFinder.h"
#include "AlignPatternFinder.h"

class Detector
{
public:
	Detector(Mat image);
	int Detect();
	unsigned short** GetBinaryData(int width, int height);
private:
	Mat image;
	FinderPatternFinder finder1;
	AlignmentPatternFinder alignmentFinder;
	FinderPatternInfo finderPatternInfo;
	AlignmentPattern alignmentPattern;
	double dx;
	double dy;

	double CalculateModuleSize();
	int ProcessFinderPatternInfo(FinderPatternInfo info); //����ֵ����ʱ��
	Point2d CalcPosition(int moduleSize, int x, int y);
	bool FindAlignmentInRegion(double moduleSize, int estAlignmentX, int estAlignmentY, int allowanceFactor);
	void Rectify(int moduleSize, int width, int height);
	//~Detector();
};