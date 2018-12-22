#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <highgui.h>
#include <cstdio>
#include <string>
using namespace cv;
using namespace std;
void logTran();
void gammaTran();
void BS();
void HD();
int main()
{
	logTran();//对数变换
	gammaTran();//伽马变换
	BS();//补色变换
	HD();//灰度变换与二值化
	waitKey(0);
	return 0;
}
void logTran()
{
	Mat src = cvLoadImage("..\\..\\pic\\h.jpg");
	
	Mat dst = cvCreateImage(src.size(), IPL_DEPTH_8U, 1);

	double c = 50.0;
	int M = 0;
	int N = 0;
	if (src.empty()){
		std::cout << "Src pic is empty\n" << std::endl;
		return;
	}
	M = src.rows;
	N = src.cols;
	int j = 0;
	double gray = 0.0;
	for (int i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			gray = (double)src.at<Vec3b>(i, j)[0];
			gray = c*log((double)(1 + gray));
			(uchar)dst.at<uchar>(i, j) = (uchar)saturate_cast<uchar>(gray);
		}
	}
	imshow("对数变换",dst);
}
void gammaTran()
{
	Mat src = cvLoadImage("..\\..\\pic\\h.jpg");

	Mat dst = cvCreateImage(src.size(),IPL_DEPTH_8U, 1);

	double gamma = 0.8;
	double comp = 0.8;
	int M = 0;
	int N = 0;
	if (src.empty()){
		std::cout << "Src pic is empty" << std::endl;
		return;
	}
	M = src.rows;
	N = src.cols;
	int j = 0;
	uchar gray = 0;
	for (int i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			gray = (float)src.at<Vec3b>(i, j)[0];
			gray = pow((gray + comp) / 255.0, gamma) * 255;
			(uchar)dst.at<uchar>(i, j) = saturate_cast<uchar>(gray);				   
		}
	}

	imshow("伽马变换，gamma = 0.8;comp = 0.8;", dst);
}
void BS()
{
	Mat src = cvLoadImage("..\\..\\pic\\h.jpg");
	Mat dst = cvCreateImage(src.size(), IPL_DEPTH_8U, 1);
	if (src.empty()){
		std::cout << "Src pic is empty\n" << std::endl;
		return;
	}

	int M = src.rows;
	int N = src.cols;
	int j = 0;
	uchar gray = 0.0;
	for (int i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			(uchar)src.at<Vec3b>(i, j)[0] = 225 - (uchar)src.at<Vec3b>(i, j)[0];
			(uchar)src.at<Vec3b>(i, j)[1] = 225 - (uchar)src.at<Vec3b>(i, j)[1];
			(uchar)src.at<Vec3b>(i, j)[2] = 255 - (uchar)src.at<Vec3b>(i, j)[2];
		}
	}
	imshow("补色变换", src);
}
void HD()
{
	Mat src = cvLoadImage("..\\..\\pic\\h.jpg");
	Mat dst = cvCreateImage(src.size(), IPL_DEPTH_8U, 1);
	if (src.empty()){
		std::cout << "Src pic is empty\n" << std::endl;
		return ;
	}
	int M = src.rows;
	int N = src.cols;
	int j = 0;
	uchar gray = 0.0;
	for (int i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			gray = (uchar)src.at<Vec3b>(i, j)[0];
			(uchar)src.at<Vec3b>(i, j)[1] = gray;
			(uchar)src.at<Vec3b>(i, j)[2] = gray;
			dst.at<uchar>(i, j) = gray>128 ? 255 : 0;
		}
	}
	imshow("二值化图像", dst);
	imshow("灰度图", src);
}