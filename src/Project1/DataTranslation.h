#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class DataTranslator {
private:

	unsigned short**DataArray = nullptr;//�����ά�����
	int dx = 25;
	int dy = 25;
	int sum = 0;
	int nowx = 0, nowy = 0, direction = 1;
	int ByteNum = 0;
	int Parity = 0;//������Ϊ1��ż����Ϊ0
	//void DtoString();

	int getnextD();
	bool WhetherInArea(int x, int y);
	short InternetCheckSum(unsigned short*buf, int nwords);
	void Initialization(unsigned short **tes);//Parity,DataArray���г�ʼ��
	void OutPutData(unsigned char*data);
public:
	void DateTranslate(unsigned short**tes);//���ض���������

};
