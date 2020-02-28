#include <cstdio>
#include "detector.h"
#include "opencv2/opencv.hpp" //opencv ��ͷ�ļ�
#include "slicer.h"
using namespace std;

using namespace cv; //opencv �������ռ�


int main()
{

    Mat img = imread("C:\\Users\\yuyua\\Desktop\\����.png");  //���ͼƬ��Ҫ�Լ�׼��������projectĿ¼�£�����ֱ��д����·��
    Mat imgGray, res;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    double x = threshold(imgGray, res, 128, 255, THRESH_BINARY_INV);
    //cout << (int)res.at<uchar>(120, 60);
    Detector lalala(res);
    lalala.Detect();
    lalala.GetBinaryData(25,25);
    
    waitKey(10000);
    return 0;
}