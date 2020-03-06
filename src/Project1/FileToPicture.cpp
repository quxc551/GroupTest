
#include "FileToPicture.h"
void FileToPicture::MakePictureSequence() {
	char readFile[20];
	FILE* readFp = NULL;
	errno_t readErr = 0;
	while (true) {
		cout << "Please enter the file you want to deliver" << endl
			<< R"(use '\\' to replace '\':)";
		cin >> readFile;
		readErr = fopen_s(&readFp, readFile, "rb");
		if (readErr == 0) break;
		cout << "Can not open the file" << endl;
	}

	FILE* writeFp = NULL;
	errno_t writeErr = 0;
	writeErr = fopen_s(&writeFp, "D:\\result.txt", "w");
	if (writeErr != 0) return;

	Trans(readFp, writeFp);

	int length, width, blockSize;
	while (true) {
		cout << "Please enter the length & width & length of block of your pic:";
		cin >> length >> width >> blockSize;
		if (length && width && blockSize) break;
	}

	Draw(length, width, 10);

}
void FileToPicture::Trans(FILE* readFp, FILE* writeFp) {
	int fill[2] = { 237,17 };//������11101101 00010001

	if (readFp)
	{
		fseek(readFp, 0, SEEK_END);
		int size = ftell(readFp);
		int current = 0;
		char * buf = new char[100];
		int nRead;
		fseek(readFp, 0, SEEK_SET);
		while (current != size) {
			nRead = fread(buf, sizeof(char), 18, readFp);
			current += nRead;
			if (nRead > 0)
			{
				int record[20] = { 0 };
				//����ȡ���ַ�תΪ�������� ����result�ļ�
				for (int i = 0; i < nRead; i++) record[i] = buf[i] - '\0';
				if (nRead < 18)
					for (int k = nRead; k < 18; k++)
						record[k] = fill[(k - nRead) % 2];

				int temp = chksum(record, 18);
				record[18] = temp >> 8;
				record[19] = temp & 0xff;

				for (int k = 0; k < 20; k++) {
					int bin = 0, j = 1;
					while (record[k]) {
						bin += j * (record[k] % 2);
						record[k] = record[k] / 2;
						j = j * 10;
					}
					fprintf(writeFp, "%08d", bin);
				}
			}
		}
		fclose(readFp);
		fclose(writeFp);
		delete buf;
	}
}
int FileToPicture::chksum(void *dataptr, unsigned short len)
{
	unsigned long acc;
	unsigned short src;
	unsigned char *octetptr;
	acc = 0;
	octetptr = (unsigned char*)dataptr;

	while (len > 1)
	{
		src = (*octetptr) << 8;  //2���ֽڽ��
		octetptr++;
		src |= (*octetptr);

		octetptr++;
		acc += src;
		len -= 2;
	}
	if (len > 0)            //��󵥸��ֽڣ���0�����2�ֽ�
	{
		src = (*octetptr) << 8;
		acc += src;
	}
	if ((acc & 0xffff0000UL) != 0)  //��16λ + ��16λ
	{
		acc = (acc >> 16) + (acc & 0x0000ffffUL);
	}

	src = (unsigned short)acc;
	return ~src;
}
void FileToPicture::Draw_Template(Mat img, int col, int row) {
	for (int i = 1; i < 6; i++) {
		//���Ϸ���
		Draw_White_block(img, 1, i);
		Draw_White_block(img, i, 1);
		Draw_White_block(img, 5, i);
		Draw_White_block(img, i, 5);
		//���Ϸ���
		Draw_White_block(img, 1, i + col - 7);
		Draw_White_block(img, i, 1 + col - 7);
		Draw_White_block(img, 5, i + col - 7);
		Draw_White_block(img, i, col - 2);
		//���·���
		Draw_White_block(img, row - 6, i);
		Draw_White_block(img, i + row - 7, 1);
		Draw_White_block(img, row - 2, i);
		Draw_White_block(img, i + row - 7, 5);
	}
	for (int i = 0; i < 8; i++) {
		//��������
		Draw_White_block(img, i, 7);
		Draw_White_block(img, 7, i);
		//��������
		Draw_White_block(img, i, col - 8);
		Draw_White_block(img, 7, i + col - 8);
		//��������
		Draw_White_block(img, i + row - 8, 7);
		Draw_White_block(img, row - 8, i);
	}
	for (int i = 0; i < 3; i++) {
		//���¶����
		Draw_White_block(img, row - 5, col - 5 + i);
		Draw_White_block(img, row - 3, col - 5 + i);
		Draw_White_block(img, row - 5 + i, col - 5);
		Draw_White_block(img, row - 5 + i, col - 3);
	}

}
void FileToPicture::Draw_White_block(Mat img, int pt0, int pt1) {
	int pixel = 10;
	rectangle(img,
		Point(pt1 * pixel, pt0 * pixel),
		Point((pt1 + 1) * pixel, (pt0 + 1) * pixel),
		Scalar(256, 256, 256),
		FILLED,
		LINE_8);
}
void FileToPicture::Draw(int length, int width, int blockSize) {
	char fill[] = "1110110100010001";//������

	FILE* fp = NULL;
	errno_t err = 0;
	err = fopen_s(&fp, "D:\\result.txt", "r");
	if (err != 0) return;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	int count = 0;
	int capacity;
	int currentLoc = 1;
	Mat QR_Code = Mat::zeros(width, length, CV_8UC3);
	fseek(fp, 0, SEEK_SET);
	int PicLength = width * length - 243;
	//243 = 8*8*3 + 5*5 + 2+16 + 8
	int col = length / 10, row = width / 10;

	while (currentLoc < size) {
		rectangle(QR_Code,
			Point(0, 0),
			Point(length, width),
			Scalar(0, 0, 0),
			FILLED,
			LINE_8);
		Draw_Template(QR_Code, col, row);
		if (count % 2) Draw_White_block(QR_Code, 0, 9);
		else Draw_White_block(QR_Code, 0, 8);

		if (size - currentLoc > PicLength) capacity = PicLength;
		else capacity = size - currentLoc;

		int bin = 0, j = 1, k = 15;
		char lengthch[] = "0000000000000000";

		while (capacity) {
			bin += j * (capacity % 2);
			lengthch[k--] = (capacity % 2) + '0';
			capacity /= 2;
			j = j * 10;
		}
		for (int k = 0; k < 16; k++) 
			if (lengthch[k] == '1') Draw_White_block(QR_Code, 0, k + 10);

		bool alert = true;
		int i = 0, chRe = 0;
		j = 26;
		char ch;
		while (alert)
		{
			if (!feof(fp) && currentLoc % PicLength) ch = fgetc(fp);
			else if (feof(fp) && currentLoc % PicLength) {
				ch = fill[chRe++];
				chRe %= 16;
			}
			if(alert) {
				if (ch == '1') Draw_White_block(QR_Code, i, j);
				currentLoc++;
				if (i % 2) {
					if (i >= 0 && i < 7) {
						if (j == 8) i++;
						else j--;
					}
					if (i == 7) {
						if (j == 8) {
							i++;
							j -= 8;
						}
						else j--;
					}
					else if (i > 7 && i < row - 9) {
						if (j == 0) i++;
						else j--;
					}
					else if (i == row - 9) {
						if (j == 0) {
							i++; j += 8;
						}
						else j--;
					}
					else if (i > row - 9 && i < row - 6) {
						if (j == 8) i++;
						else j--;
					}
					else if (i >= row - 6 && i <= row - 1) {
						if (j == col - 1) j -= 6;
						else if (j == 8) i++;
						else j--;
					}
					if (i == row - 1 && j == 16) alert = false;
				}
				else {
					if (i >= 0 && i < 7) {
						if (j == col - 9) i++;
						else j++;
					}
					else if (i >= 7 && i < row - 6) {
						if (j == col - 1) i++;
						else j++;
					}
					else if (i >= row - 6 && i < row) {
						if (j == col - 9) j += 6;
						else if (j == col - 1) i++;
						else j++;
					}
				} 
			}
		}
		string filename = "D:\\QR_Code\\QR_Code" + to_string(count) + ".jpg";
		cout << filename << endl;
		cv::imwrite(filename, QR_Code);
		currentLoc++;
		count++;
	}
	system("pause");
	fclose(fp);
}