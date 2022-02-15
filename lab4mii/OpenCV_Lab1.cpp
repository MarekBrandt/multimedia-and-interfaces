
#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
using namespace cv;
#include "Typedefs.h"
const float scale = 3.5;

void imgShow(String nazwa, Mat src, int x, int y) {
	namedWindow(nazwa);
	moveWindow(nazwa, x, y);
	imshow(nazwa, src);
}

int main()
{
	// reading source file srcImage
	Mat srcImage;
	Mat resizedImage;
	Mat grayImage;
	Size patternsize;
	
	
	srcImage = imread( "Images/184590_D.jpg" );
	if ( !srcImage.data )
	{
		cout << "Error! Cannot read source file. Press ENTER.";
		waitKey();
		return( -1 );
	}

	vector<Point2f> corners;

	resize(srcImage, resizedImage, Point(), 1/scale, 1/scale);
	cvtColor(resizedImage, grayImage, COLOR_BGR2GRAY);
	patternsize.width = CheckerboardInnerWidth[TOP];
	patternsize.height = CheckerboardInnerHeight[TOP];
	if (findChessboardCorners(grayImage, patternsize, corners) == false) {
		std::cout << "Nie udalo sie znalezc naroznikow" << std::endl;
		waitKey();
		return(-1);
	}
	if (corners.front().y > corners.back().y)
		reverse(corners.begin(), corners.end());
	cornerSubPix(grayImage, corners, patternsize,Size(-1,-1),TermCriteria());
	drawChessboardCorners(grayImage, patternsize, corners, 1);

	cout << "Odleglosc euklidesowa wierzcholkow 0 i 1\n";
	float xl = corners[1].x - corners[0].x;
	float yl = corners[1].y - corners[0].y;
	cout << sqrt((xl * xl + yl * yl));
	cout << endl;

	float reverseScale = 37.0f;
	vector <Point2f > templateCorners;

	for (int i = 0; i < corners.size(); i++) {
		float x = corners[i].x;
		float y = corners[i].y;
		putText(grayImage, to_string(i), Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255));
	}

	Mat homography;

	for (int i = 1; i <= CheckerboardInnerHeight[TOP]; i++) {
		for (int j = 1; j <= CheckerboardInnerWidth[TOP]; j++) {
			Point2f coord;
			coord.x = CheckerboardLTCoordinatesWithMargin[TOP].x + j * CHECKERBOARD_FIELD_SIZE;
			coord.y = CheckerboardLTCoordinatesWithMargin[TOP].y + i * CHECKERBOARD_FIELD_SIZE;
			templateCorners.push_back(coord * reverseScale);
		}
	}

	homography = findHomography(corners, templateCorners);

	Mat dewarpedImage(resizedImage.size(), resizedImage.type());
	warpPerspective(resizedImage, dewarpedImage, homography, dewarpedImage.size());

	Mat dewarpedROI = dewarpedImage(Rect(reverseScale * TemplateLT, reverseScale * TemplateRB));
	Mat debugImage = dewarpedROI.clone();
	vector<Point2f>dewarpedCorners;
	perspectiveTransform(corners, dewarpedCorners, homography);

	for (int i = 0; i < dewarpedCorners.size(); i++) {
		circle(debugImage, dewarpedCorners[i], 8, Scalar(255, 0, 0),2);
	}

	imgShow("Marek Brandt", grayImage, 0, 0);
	//imgShow("Marek Brandt2", dewarpedImage, 0, 0);
	//imgShow("Marek Brandt2", debugImage, 0, 0);
	imwrite("Images/184590_D_TopChessboardFound.jpg", grayImage);
	imwrite("Images/184590_D_Dewarped.jpg", dewarpedImage);
	imwrite("Images/184590_D_Dewarped_ROI.jpg", debugImage);
	

	waitKey();
}
