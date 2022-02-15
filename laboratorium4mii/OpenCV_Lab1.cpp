
#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
#include "opencv2/core/types_c.h"
#include "opencv2/calib3d/calib3d_c.h"
using namespace cv;

#pragma once

// checkerboards types and number
// The counterclockwise order is required to start searching from the biggest one !!!!
enum ReferenceRegionsTypes { TOP, LEFT, BOTTOM, RIGHT, CHECKERBOARD_NUM };

// checkerboards locations
const int CheckerboardInnerWidth[CHECKERBOARD_NUM] = { 13, 3, 11, 3 }; // number of inner horizontal corners 
const int CheckerboardInnerHeight[CHECKERBOARD_NUM] = { 3, 12, 3, 10 }; // number of inner vertical corners 

const float CHECKERBOARD_FIELD_SIZE = 0.8f; // size of all checkerboard fields
const float CheckerboardsMargin = 1.6f; // outer margin around checkerboard

const Point2f CheckerboardLTCoordinatesWithMargin[CHECKERBOARD_NUM] =
{ // Coordinates of outer left-top corner
	Point2f(4.4f, 0.5f), // TOP
	Point2f(0.5f, 4.8f), // LEFT
	Point2f(5.2f, 16.3f), // BOTTOM
	Point2f(16.3f, 5.6f) // RIGHT
};

// Coordinates of the output region of interest 
const Point2f TemplateLT = Point2f(0.0f, 0.0f); // left-top corner
const Point2f TemplateRB = Point2f(20.0f, 20.0f); // right-bottom corner

int main()
{
	// reading source file srcImage
	Mat srcImage;
	srcImage = imread( "Images/184590_E.jpg" );
	if ( !srcImage.data )
	{
		cout << "Error! Cannot read source file. Press ENTER.";
		waitKey();
		return( -1 );
	}
	Mat resizedImage;

	resize(srcImage, resizedImage, Size(), 0.5, 0.5);

	Mat greyImage;
	cvtColor(resizedImage, greyImage, COLOR_BGR2GRAY);
	Size patternsize;
	vector<Point2f>srcCorners;

	patternsize.width = CheckerboardInnerWidth[TOP];
	patternsize.height = CheckerboardInnerHeight[TOP];
	if (findChessboardCorners(greyImage, patternsize, srcCorners) == false) {
		std::cout << "Nie udalo sie znalezc naroznikow" << std::endl;
		waitKey();
		return(-1);
	}
	cornerSubPix(greyImage, srcCorners, patternsize, Size(-1, -1), TermCriteria());
	if (srcCorners.front().y > srcCorners.back().y)
		reverse(srcCorners.begin(), srcCorners.end());
	drawChessboardCorners(greyImage, patternsize, srcCorners, 2);

	float x1 = srcCorners[1].x;
	float x0 = srcCorners[0].x;
	float y1 = srcCorners[1].y;
	float y0 = srcCorners[0].y;

	cout << "Odleglosc c1 i c0:   " << sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)) << endl;

	for (int i = 0; i < srcCorners.size(); i++) {
		float x = srcCorners[i].x;
		float y = srcCorners[i].y;
		putText(greyImage, to_string(i), Point(x, y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255));
	}

	float reverseScale = 65.0f;
	vector <Point2f > templateCorners;

	for (int i = 1; i <= CheckerboardInnerHeight[TOP]; i++) {
		for (int j = 1; j <= CheckerboardInnerWidth[TOP]; j++) {
			Point2f coord;
			coord.x = CheckerboardLTCoordinatesWithMargin[TOP].x + j * CHECKERBOARD_FIELD_SIZE;
			coord.y = CheckerboardLTCoordinatesWithMargin[TOP].y + i * CHECKERBOARD_FIELD_SIZE;
			templateCorners.push_back(coord * reverseScale);
		}
	}

	Mat homography;
	homography = findHomography(srcCorners, templateCorners);
	Mat dewarpedImage(resizedImage.size(), resizedImage.type());
	warpPerspective(resizedImage, dewarpedImage, homography, dewarpedImage.size());

	Mat dewarpedROI = dewarpedImage(Rect(reverseScale * TemplateLT, reverseScale * TemplateRB));
	vector<Point2f>dewarpedCorners;
	perspectiveTransform(srcCorners, dewarpedCorners, homography);

	for (int i = 0; i < dewarpedCorners.size(); i++) {
		circle(dewarpedROI, dewarpedCorners[i], 8, Scalar(0, 255, 0), 2);
	}


	imwrite("Images/184590_E_ChessboardFound.jpg", greyImage);
	imwrite("Images/184590_E_Dewarped.jpg", dewarpedImage);
	imwrite("Images/184590_E_DewarpedROI.jpg", dewarpedROI);
	return(0);
}
