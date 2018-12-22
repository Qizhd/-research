#include <opencv\highgui.h>
#include <cv.h>
#include <vector>
#define  N  3
#define path "..\\..\\pic\\yq.tif"

using namespace cv;
using namespace std;

double arr[N][N] = { { 0 } };
static double max1 = 0;
static double min1 = 0;

void Laplacian();
void Robert();
void Sobel();

Mat LaplacianBH();
Mat RobertBH();
Mat SobelBH();
double compute(int bb[][N]);
void print();

int main()
{
	//Sobel，Robert，Laplacian
	Mat src = imread(path);
	imshow("原始图像", src);

	Laplacian();
	cout << "Laplacian" << endl;
	print();
	//imshow("Laplacian", LaplacianBH());

	Robert();
	cout << "Robert" << endl;
	print();
	//imshow("Robert", RobertBH());

	Sobel();
	cout << "Sobel" << endl;
	print();
	imshow("Sobel", SobelBH());

	//cvtColor(src, src, CV_BGR2GRAY);//变换成灰度图像
	//cout <<"min1="<< min1 << "\nmax1="<<max1 << endl;
	waitKey(0);

	return 0;
}
Mat LaplacianBH()
{
	Mat src = imread(path);
	int bb[N][N] = { { 0 } };

	int temp = 0;

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
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[0] ;
				}
			}
			temp = (int)src.at<Vec3b>(i , j )[0] - compute(bb)* 0.5;
			temp=temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[0] = (int)temp;
			//第二个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[1];
				}
			}
			temp = (int)src.at<Vec3b>(i, j)[1] - compute(bb) * 0.5;
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[1] = (int)temp;
			//第三个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[2];
				}
			}
			temp = (int)src.at<Vec3b>(i, j)[2] - compute(bb) * 0.5;
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[2] = (int)temp;
		}
	}

	return src;
}
Mat RobertBH()
{
	Mat src = imread(path);
	int bb[N][N] = { { 0 } };

	int temp = 0;

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
			temp = (int)src.at<Vec3b>(i, j)[0] + compute(bb);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[0] = (int)temp;
			//第二个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[1];
				}
			}
			temp = (int)src.at<Vec3b>(i, j)[1] + compute(bb);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[1] = (int)temp;
			//第三个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - 1 + w, j - 1 + h)[2];
				}
			}
			temp = (int)src.at<Vec3b>(i, j)[2] + compute(bb);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[2] = (int)temp;
		}
	}

	return src;
}
Mat SobelBH()
{
	Mat src = imread(path);
	int bb[N][N] = { { 0 } };
	int comp;
	int temp = 0;

	int i = src.rows, j = src.cols;
	int w = 0, h = 0;
	cout << i << "*" << j;
	for (i = N / 2; i < src.rows - 1 - N; i++)
	{
		for (j = N / 2; j < src.cols - 1 - N; j++)
		{
			//第一个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[0];
				}
			}
			//comp = compute(bb);
			//if (comp<0)comp = comp*(-1);
			//if (comp>255)comp = 255;
			temp = ((int)src.at<Vec3b>(i, j)[0] + compute(bb)*0.25);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[0] = (int)temp;
			//第二个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[1];
				}
			}
			//comp = compute(bb);
			//if (comp<0)comp = comp*(-1);
			//if (comp>255)comp = 255;

			temp = ((int)src.at<Vec3b>(i, j)[1] + compute(bb)*0.25);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[1] = (int)temp;
			//第三个通道
			for (w = 0; w < N; w++)
			{
				for (h = 0; h < N; h++)
				{
					bb[w][h] = (int)src.at<Vec3b>(i - N / 2 + w, j - N / 2 + h)[2];
				}
			}
			//comp = compute(bb);
			//if (comp<0)comp = comp*(-1);
			//if (comp>255)comp = 255;

			temp = ((int)src.at<Vec3b>(i, j)[2] + compute(bb)*0.25);
			temp = temp>255 ? 255 : temp;
			temp = temp<0 ? 0 : temp;
			src.at<Vec3b>(i, j)[2] = (int)temp;
		}
	}

	return src;
}
void Laplacian()
{
	arr[0][0] = 0;       
	arr[0][1] = 1;
	arr[0][2] = 0;

	arr[1][0] = 1;
	arr[1][1] = -4;
	arr[1][2] = 1;

	arr[2][0] = 0;
	arr[2][1] = 1;
	arr[2][2] = 0;
}
void Robert()
{
	//x方向
	arr[0][0] = 0;
	arr[0][1] = 0;
	arr[0][2] = 0;

	arr[1][0] = 0;
	arr[1][1] = 1;
	arr[1][2] = 0;

	arr[2][0] = 0;
	arr[2][1] = 0;
	arr[2][2] = -1;
}
void Sobel()
{
	//y方向
	arr[0][0] = -1;
	arr[0][1] = -2;
	arr[0][2] = -1;

	arr[1][0] = 0;
	arr[1][1] = 0;
	arr[1][2] = 0;

	arr[2][0] = 1;
	arr[2][1] = 2;
	arr[2][2] = 1;
}
double compute(int bb[][N])
{
	double temp = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp = arr[i][j] * bb[i][j] + temp;
		}
	}

	max1 = max1>temp ? max1 : temp;
	min1 = max1<temp ? min1 : temp;
	return temp;
}
void print()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(3) << arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}