#include <opencv\highgui.h>
#include <cv.h>
#include <vector>
#define  N  5
#define path "..\\..\\pic\\mg.jpg"

using namespace cv;
using namespace std;

double arr[N][N] = { { 0 } };

void inital33(double arr[][N]);
void inital55(double arr[][N]);
void JZ(Mat src);
int compute(int bb[][N]);

int main()
{

	inital55(arr);
	Mat src = imread(path);
	//imshow("aaa",src);
	JZ(src);
	waitKey(0);
	return 0;
}
void JZ(Mat src)
{
	int bb[N][N] = { { 0 } };

	int i = src.rows, j = src.cols;
	int w = 0, h = 0;
	cout << i << "*" << j;

	for (i = N / 2; i < src.rows - 1 - N/2; i++)
	{
		for (j = N / 2; j < src.cols - 1 - N/2; j++)
		{

			//第一个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[0];
				}
			}
			src.at<Vec3b>(i, j)[0] = compute(bb);
			//第二个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[1];
				}
			}
			src.at<Vec3b>(i, j)[1] = compute(bb);
			//第三个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[2];
				}
			}
			src.at<Vec3b>(i, j)[2] = compute(bb);
		}
	}
	imshow("高斯滤波", src);
}
void inital33(double arr[][N])
{
	arr[0][0] = 1;
	arr[0][1] = 2;
	arr[0][3] = 1;

	arr[1][0] = 2;
	arr[1][1] = 4;
	arr[1][2] = 2;

	arr[2][0] = 1;
	arr[2][1] = 2;
	arr[2][2] = 1;
}
void inital55(double arr[][N])
{
	arr[0][0] = 1;
	arr[0][1] = 4;
	arr[0][2] = 7;
	arr[0][3] = 4;
	arr[0][4] = 1;

	arr[1][0] = 4;
	arr[1][1] = 16;
	arr[1][2] = 26;
	arr[1][3] = 16;
	arr[1][4] = 4;


	arr[2][0] = 7;
	arr[2][1] = 26;
	arr[2][2] = 41;
	arr[2][3] = 26;
	arr[2][4] = 7;

	arr[3][0] = 4;
	arr[3][1] = 16;
	arr[3][2] = 26;
	arr[3][3] = 16;
	arr[3][4] = 4;

	arr[4][0] = 1;
	arr[4][1] = 4;
	arr[4][2] = 7;
	arr[4][3] = 4;
	arr[4][4] = 1;

}
int compute(int bb[][N])
{
	double temp = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp = arr[i][j] * bb[i][j] + temp;
		}
	}
	return temp/(273);
}