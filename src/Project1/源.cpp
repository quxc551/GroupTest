#include <cstdio>
#include "detector.h"
#include "opencv2/opencv.hpp" //opencv 的头文件
#include "slicer.h"
#include "FileToVedio.h"
#include "FileToMp4.h"
#include <bitset>
#include "DataTranslation.h"
using namespace std;

using namespace cv; //opencv 的命名空间


int main(int argc, char* argv[])
{
	static unsigned char temporary[3][10485760] = { 0 };
	static unsigned char checktemporary[3][10485760] = { 0 };
	int range[3];
	/*FileToVedio a(R"(C:\Users\yuyua\Desktop\e1.bin)");
	a.GenerateVedio(R"(D:\QR_Code\QR_Code.mp4)", 1080, 1920, 10);*/
	
	/*FileToMp4 a;
	a.MakePictureSequence();*/
	int start = getTickCount();
	Mat imgGray, res;
	Mat img;
	int count = 1;
	string inputfile = argv[count++];
	string outfile1 = argv[count++];
	string outfile2 = argv[count++];
	//VedioSlicer GT(inputfile);


	int ST = 0;
	int error = 0;
	int all = 0;
	for (int j = 0; j < 3; j++)
	{
		string a = "";
		string b = "";
		DataTranslator D(a, b);
		VedioSlicer GT(inputfile);
		int i = 0;
		while (1)
		{
			++i;

			img = GT.GetNextFrame();
			if (i % 3 != j)continue;
			if (img.empty())
			{
				break;
			}
			Detector d(img, 108, 192, 10);
			if (!d.Detect())throw;
			char x[2];
			d.picCount(x);
			D.DateTranslate(d.GetBinaryData(),temporary[j],checktemporary[j]);
		}
		range[j] = D.getSum();
		int nowall = D.getall();
		int nowerror = D.geterror();
		//cout << nowall << " " << nowerror<<endl;
		if (nowall > all)
		{
			ST = j;
			all = nowall;
			error = nowerror;
		}
		else if (nowall == all)
		{
			if (error > nowerror)
			{
				ST = j;
				all = nowall;
				error = nowerror;
			}
		}
	}

	DataTranslator DT(outfile1, outfile2);
	DT.OutPutData(temporary[ST], checktemporary[ST], range[ST]);
	cout << "error:" << error << endl << "all:" << all << endl;
	//int i = 0;
	//while (1)
	//{
	//	++i;
	//	img = DS.GetNextFrame();
	//	if (i % 3 != ST)continue;
	//	//cout << i << ' ';
	//	//img = imread(R"(D:\QR_Code\Code10_trans.png)");
	//	if (img.empty())
	//	{
	//		break;
	//	}
	//	//imwrite(".//1.jpg", res);
 //		Detector d(img, 108, 192, 10);
	//	if (!d.Detect())throw;
	//	char x[2];
	//	d.picCount(x);
	//	//cout << (int)x[0] << (int)x[1] << endl;
	//	DT.DateTranslate(d.GetBinaryData());
	//}
	//DT.out();
	int end = getTickCount();
	int last = end - start;
	cout << "time consume: " << last / getTickFrequency() << 's' << endl;
	return 0;
}