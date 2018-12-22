#include <opencv\highgui.h>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <cv.h>
#include <algorithm>
#include <numeric>
#include <vector>

#define path "..\\..\\pic\\lz.jpg"

using namespace cv;
using namespace std;
int main()
{
	Mat src = imread(path);
	cvtColor(src, src, CV_BGR2GRAY);//�任�ɻҶ�ͼ��
	if (!src.data)	cout << "open imge error";
	imshow("ԭʼͼ��",src);
	int col = getOptimalDFTSize(src.cols);
	int row = getOptimalDFTSize(src.rows);
	cout << src.cols << src.rows << endl;
	//���߽�
	copyMakeBorder(src, src, 0, col - src.cols, 0, row - src.rows, BORDER_CONSTANT, Scalar::all(0));
	//imshow("a", src);

	Mat planes[] = {Mat_<float>(src),Mat::zeros(src.size(),CV_32F)};
	Mat compleximg;
	merge(planes, 2, compleximg);//compleximg������ű任�Ľ��

	dft(compleximg, compleximg);

	split(compleximg, planes);

	magnitude(planes[0], planes[1], planes[0]);

	Mat magnitudeimg = planes[0];
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

	imshow("DFT�任���ͼ��", magnitudeimg);
	cout <<src.cols << src.rows << endl;
	waitKey(0);
	return 0;
}