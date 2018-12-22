#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define PI2 2*3.141592654

int main()
{

	Mat image = imread("..\\..\\pic\\lz.jpg");
	cvtColor(image, image, CV_BGR2GRAY);//�任�ɻҶ�ͼ��

	///////////////���ٸ���Ҷ�任////////
	int oph = getOptimalDFTSize(image.rows);
	int opw = getOptimalDFTSize(image.cols);
	//Mat padded;
	copyMakeBorder(image, image, 0, oph - image.rows, 0, opw - image.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat temp[] = { Mat_<float>(image), Mat::zeros(image.size(), CV_32F) };
	Mat complexI;
	merge(temp, 2, complexI);

	dft(complexI, complexI);

	split(complexI, temp);

	magnitude(temp[0], temp[1], temp[0]);

	Mat magnitudeimg = temp[0];
	magnitudeimg += Scalar::all(1);

	log(magnitudeimg, magnitudeimg);//log����

	magnitudeimg = magnitudeimg(Rect(0, 0, magnitudeimg.cols&-2, magnitudeimg.rows&-2));
	int cx = magnitudeimg.cols / 2;
	int cy = magnitudeimg.rows / 2;
	//�����ƶ���ԭ��
	Mat q0(magnitudeimg, Rect(0, 0, cx, cy));
	Mat q1(magnitudeimg, Rect(cx, 0, cx, cy));
	Mat q2(magnitudeimg, Rect(0, cy, cx, cy));
	Mat q3(magnitudeimg, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magnitudeimg, magnitudeimg, 0, 1, CV_MINMAX);//��һ������
	imshow("DFTƵ��", magnitudeimg);

	//////////////////////////Ƶ���˲�//////
	//����Ƶ���˲���
	Mat LXDT(image.size(), CV_32FC2);
	Mat LXGT(image.size(), CV_32FC2);
	float D0 = 500*500;
//	cout << "�����ֹƵ��" << endl;
//	cin >> D0;
	for(int i=0; i<oph; i++)
	{
	    float *p = LXDT.ptr<float>(i);
	    float *q = LXGT.ptr<float>(i);
	    for(int j=0; j<opw; j++)
	    {	//��˹��ͨ����˹��ͨ
	        //float d = pow(i-oph/2, 2) + pow(j-opw/2, 2);
	        //p[2*j] = expf(-d / D0);
	        //p[2*j+1] = expf(-d / D0);

	        //q[2*j] = 1 - expf(-d / D0);
	        //q[2*j+1] = 1 - expf(-d / D0);

			float d = pow(i-oph/2, 2) + pow(j-opw/2, 2);
			//d = sqrt(d);
			if (D0 > d)
			{
			p[2*j] = 0;
			p[2 * j + 1] = 0;
			q[2 * j] = 255;
			q[2 * j + 1] = 255 ;
			}
			else
			{
				p[2 * j] = 255;
				p[2 * j + 1] = 255;
				q[2 * j] = 0;
				q[2 * j + 1] = 0;
			}
	    }
	}

	//�����ͨ�˲��� �����ͨ�˲�
	multiply(complexI, LXDT, LXDT);
	multiply(complexI, LXGT, LXGT);

	//����Ҷ���任
	dft(LXDT, LXDT, CV_DXT_INVERSE);
	dft(LXGT, LXGT, CV_DXT_INVERSE);

	Mat dstBlur[2], dstSharpen[2];
	split(LXDT, dstBlur);
	split(LXGT, dstSharpen);

	for(int i=0; i<oph; i++)        //���Ļ�
	{
	    float *p = dstBlur[0].ptr<float>(i);
	    float *q = dstSharpen[0].ptr<float>(i);
	    for(int j=0; j<opw; j++)
	    {
	        p[j] = p[j] * pow(-1, i+j);
	        q[j] = q[j] * pow(-1, i+j);
	    }
	}
	normalize(dstBlur[0], dstBlur[0], 1, 0, CV_MINMAX);
	normalize(dstSharpen[0], dstSharpen[0], 1, 0, CV_MINMAX);

	imshow("�����ͨ�˲�",dstBlur[0]);
	imshow("�����ͨ�˲�",dstSharpen[0]);

	waitKey(0);
	return 0;
}