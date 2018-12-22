#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace cv;
using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//��ɫͼ���ֱ��ͼ���⻯
void CalcHistRGB(IplImage *);
IplImage* EqualizeHistColorImage(IplImage *);
//main
int main(int argc, char** argv)
{


	IplImage *pSrcImage = cvLoadImage("..\\..\\pic\\h.jpg", CV_LOAD_IMAGE_UNCHANGED);

	IplImage *pHisEquaImage = EqualizeHistColorImage(pSrcImage);
	CalcHistRGB(pHisEquaImage);

	cvNamedWindow("��ɫԭͼ", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("��ɫ���⻯��", CV_WINDOW_AUTOSIZE);

	cvShowImage("��ɫԭͼ", pSrcImage);
	cvShowImage("��ɫ���⻯��", pHisEquaImage);


	cvWaitKey(0);

	return 0;
}
void CalcHistRGB(IplImage *pImage)
{
	IplImage* img_source = pImage;

	if (img_source)
	{
		IplImage* RedChannel = cvCreateImage(cvGetSize(img_source), 8, 1);
		IplImage* GreenChannel = cvCreateImage(cvGetSize(img_source), 8, 1);
		IplImage* BlueChannel = cvCreateImage(cvGetSize(img_source), 8, 1);
	//	IplImage* alphaChannel = cvCreateImage(cvGetSize(img_source), 8, 1);
		//IplImage* gray_plane = cvCreateImage(cvGetSize(img_source), 8, 1);


		//�ָ�Ϊ��ͨ��ͼ��
		cvSplit(img_source, BlueChannel, GreenChannel, RedChannel, 0);
		// ��ʾͼ��


		//cvCvtColor(img_source, gray_plane, CV_BGR2GRAY);


		//Ȼ��Ϊ������ͼ������Ӧ��ֱ��ͼ�ṹ��
		int hist_size = 100;

		int hist_height = 100;

		float range[] = { 0, 255 };

		float* ranges[] = { range };

		CvHistogram* r_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

		CvHistogram* g_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

		CvHistogram* b_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

		//CvHistogram* gray_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

		//����������ֱ��ͼ������������ʾֱ��ͼ��ͼ����ȥ��һ�����ظ����룬����Ҳ��

		cvCalcHist(&RedChannel, r_hist, 0, 0);
		cvCalcHist(&GreenChannel, g_hist, 0, 0);
		cvCalcHist(&BlueChannel, b_hist, 0, 0);
		//cvCalcHist(&gray_plane, gray_hist, 0, 0);
		//cvNormalizeHist(gray_hist, 1.0);
		cvNormalizeHist(r_hist, 1.0);
		cvNormalizeHist(g_hist, 1.0);
		cvNormalizeHist(b_hist, 1.0);

		int scale = 2;

		IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale, hist_height * 3), 8, 3);

		cvZero(hist_image);

		//Ȼ��ʼ��ʾ�������ֱ��ͼ�����˱�׼��������Ȼ�Ļ��޷��۲쵽���Եı仯��

		float r_max_value = 0;
		float g_max_value = 0;
		float b_max_value = 0;
		//float gray_max_value = 0;
		cvGetMinMaxHistValue(r_hist, 0, &r_max_value, 0, 0);
		cvGetMinMaxHistValue(g_hist, 0, &g_max_value, 0, 0);
		cvGetMinMaxHistValue(b_hist, 0, &b_max_value, 0, 0);
		//cvGetMinMaxHistValue(b_hist, 0, &gray_max_value, 0, 0);
		for (int i = 0; i<hist_size; i++)
		{

			float r_bin_val = cvQueryHistValue_1D(r_hist, i);

			int r_intensity = cvRound(r_bin_val*hist_height / r_max_value);
			cvRectangle(
				hist_image,
				cvPoint(i*scale, hist_height - 1),
				cvPoint((i + 1)*scale - 1, hist_height - r_intensity),
				CV_RGB(255, 0, 0));

			float g_bin_val = cvQueryHistValue_1D(g_hist, i);
			int g_intensity = cvRound(g_bin_val*hist_height / g_max_value);
			cvRectangle(
				hist_image,
				cvPoint(i*scale, 2 * hist_height - 1),
				cvPoint((i + 1)*scale - 1, 2 * hist_height - g_intensity),
				CV_RGB(0, 255, 0));

			float b_bin_val = cvQueryHistValue_1D(b_hist, i);
			int b_intensity = cvRound(b_bin_val*hist_height / b_max_value);
			cvRectangle(
				hist_image,
				cvPoint(i*scale, 3 * hist_height - 1),
				cvPoint((i + 1)*scale - 1, 3 * hist_height - b_intensity),
				CV_RGB(0, 0, 255));

		}

		cvNamedWindow("ֱ��ͼ", WINDOW_NORMAL);
		cvShowImage("ֱ��ͼ", hist_image);


	}

}
IplImage* EqualizeHistColorImage(IplImage *pImage)
{
	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);

	// ԭͼ��ֳɸ�ͨ�����پ��⻯,���ϲ�����ɫͼ���ֱ��ͼ���⻯
	const int MAX_CHANNEL = 4;
	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };

	int i;
	for (i = 0; i < pImage->nChannels; i++)
		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);

	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);

	for (i = 0; i < pImage->nChannels; i++)
		cvEqualizeHist(pImageChannel[i], pImageChannel[i]);

	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);

	for (i = 0; i < pImage->nChannels; i++)
		cvReleaseImage(&pImageChannel[i]);

	return pEquaImage;
}