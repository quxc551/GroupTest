#include <cstdio>
#include "detector.h"
#include "opencv2/opencv.hpp" //opencv ��ͷ�ļ�
#include "slicer.h"
#include "VedioGenerator.h"
using namespace std;

using namespace cv; //opencv �������ռ�


int main()
{

    VedioGenerator a;
    a.Read();
    a.Draw();
    
    
    return 0;
}