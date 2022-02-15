#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
using namespace cv;

const int histSize = 256;
const int hist_w = 256;
const int hist_h = 256;

float range[] = { 0, 256 };

const float* histRange = range;

Mat grayImage;

int threshold_value = 100;
int max_value = 255;
Mat binarizedImage;

void calcHist(Mat* grayImage, int liczbaObrazow, int liczbaKanalow, Mat maska, Mat histogram, int liczbaWymiarow, int* histSize, float* histRange) {
	normalize(histogram, histogram, range[0], range[1], NORM_MINMAX);
	line(histImag)
}

void Threshold(int pos, void* userdata) {
	threshold(grayImage, binarizedImage, threshold_value, max_value, THRESH_BINARY);
	imshow("Binarization", binarizedImage);
	moveWindow("Binarization", 0, 600);
}

int main()
{
	// reading source file srcImage
	Mat srcImage;
	Mat blurImage;
	Mat CannyImage;
	Mat LaplacianImage;
	Mat scaledLaplacianImage;
	Mat brigthImage;
	Mat histImageGray(Size(hist_h, hist_w), CV_8UC3, Scalar(0,0,0));
	Mat histogramGray;
	srcImage = imread("Samples/ryba.jpg");
	if (!srcImage.data)
	{
		cout << "Error! Cannot read source file. Press ENTER.";
		waitKey();
		return(-1);
	}
	Mat resizedImage(100, 100, srcImage.type());
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	resize(srcImage, resizedImage, resizedImage.size());
	blur(srcImage, blurImage, Size(5, 5));
	Canny(srcImage, CannyImage, 50, 150);
	Laplacian(grayImage, LaplacianImage, CV_16S, 3);
	convertScaleAbs(LaplacianImage, scaledLaplacianImage);
	srcImage.copyTo(brigthImage);
	for (int i = 0; i < brigthImage.cols; i++) {
		for (int j = 0; j < brigthImage.rows; j++) {
			Vec3b pixelColor;
			pixelColor = brigthImage.at<Vec3b>(j, i);
			for (int k = 0; k < 3; k++) {
				if ((pixelColor[k] + 100) > 255) pixelColor[k] = 255;
				else pixelColor[k] += 100;
			}
			brigthImage.at<Vec3b>(j, i) = pixelColor;
		}
	}
	namedWindow("Binarization", (0, 600));
	createTrackbar("Threshold value", "Binarization", &threshold_value, max_value, Threshold);
	Threshold(threshold_value, NULL);

	imshow("Marek Brandt", srcImage);
	moveWindow("Marek Brandt", 0, 0);

	imshow("Gray image", grayImage);
	moveWindow("Gray image", 300, 0);

	imshow("Resized image", resizedImage);
	moveWindow("Resized image", 600, 0);

	imshow("Blurred image", blurImage);
	moveWindow("Blurred image", 900, 0);

	imshow("Canny edges", CannyImage);
	moveWindow("Canny edges", 1200, 0);

	imshow("Laplacian image", scaledLaplacianImage);
	moveWindow("Laplacian image", 1500, 0);

	imshow("Bright image", brigthImage);
	moveWindow("Bright image", 900, 300);

	imwrite("Samples/Gray image.jpg", grayImage);

	waitKey();

	Mat srcFrame;
	Mat dstFrame(100, 100, srcFrame.type());
	VideoCapture capture("Samples/Dino.avi");
	capture >> srcFrame;
	VideoWriter writer("Samples/Dino2.avi", -1, 25, srcFrame.size());
	while (waitKey(40) != 27 && !srcFrame.empty()) {
		//cvtColor(srcFrame, dstFrame, COLOR_BGR2GRAY);
		resize(srcFrame, dstFrame, Size(), 0.5, 0.5);
		//srcFrame.copyTo(dstFrame);
		writer << dstFrame;
		imshow("Src video", srcFrame);
		imshow("Dst video", dstFrame);
		moveWindow("Src video", 300, 600);
		moveWindow("Dst video", 900, 600);
		capture >> srcFrame;
	}
	
}
