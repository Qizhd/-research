#include <opencv\highgui.h>
#include <cv.h>
#include <vector>
#define  N  9
#define path "..\\..\\pic\\mg.jpg"

using namespace cv;
using namespace std;

double arr[N][N] = { { 0 } };

void inital(double arr[][N]);
void JZ(Mat src);
uchar compute(int bb[][N]);

int main()
{

	inital(arr);
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

	for (i = 1; i < src.rows - 1 - N; i++)
	{
		for (j = 1; j < src.cols - 1 - N; j++)
		{

			//第一个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[0];
				}
			}
			(uchar)src.at<Vec3b>(i, j)[0] = compute(bb);
			//第二个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[1];
				}
			}
			(uchar)src.at<Vec3b>(i, j)[1] = compute(bb);
			//第三个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[2];
				}
			}
			(uchar)src.at<Vec3b>(i, j)[2] = compute(bb);
		}
	}
	imshow("aa", src);
}
void inital(double arr[][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			arr[i][j] = (double)1 / (N*N);
		}
	}
}
uchar compute(int bb[][N])
{
	int temp = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp = arr[i][j] * bb[i][j] + temp;
		}
	}
	return temp;
}