#include "CvImage.h"

#include <opencv2/imgproc.hpp>

#include <vector>

using std::vector;

using cv::cvtColor;
using cv::GaussianBlur;
using cv::Canny;
using cv::dilate;
using cv::COLOR_BGR2GRAY;
using cv::getStructuringElement; 
using cv::getPerspectiveTransform;
using cv::warpPerspective;
using cv::findContours;
using cv::contourArea;
using cv::arcLength;
using cv::approxPolyDP;
using cv::MORPH_RECT;
using cv::RETR_EXTERNAL;
using cv::CHAIN_APPROX_SIMPLE;
using cv::Size;
using cv::Point2f;
using cv::Vec4i;
using cv::Rect;

Mat CvImage::preProcessing()
{
	Mat imgConverter{};

	cvtColor(originImage, imgConverter, COLOR_BGR2GRAY);
	GaussianBlur(imgConverter, imgConverter, Size(5, 5), 3, 0);
	Canny(imgConverter, imgConverter, 25, 25);

	auto kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgConverter, imgConverter, kernel);

	return imgConverter;
}

Mat CvImage::warpImg(const array<Point, CvImage::POINT_AMOUNT>& points)
{
	float w{}, h{};
	w = sqrtf(powf(static_cast<float>(points[1].x - points[0].x), 2.0f) 
		+ powf(static_cast<float>(points[1].y - points[0].y), 2.0f));
	h = sqrtf(powf(static_cast<float>(points[2].x - points[0].x), 2.0f)
		+ powf(static_cast<float>(points[2].y - points[0].y), 2.0f));

	Point2f src[4] = { points[0], points[1], points[2], points[3] };
	Point2f dst[4] = {
		{0.0f, 0.0f},
		{w, 0.0f},
		{0.0f, h},
		{w, h},
	};
	Mat matrix = getPerspectiveTransform(src, dst), imgWarp{};
	warpPerspective(originImage, imgWarp, matrix, Point(w, h));
	return imgWarp;
}

array<Point, CvImage::POINT_AMOUNT> CvImage::reorder(const array<Point, CvImage::POINT_AMOUNT>& points)
{
	array<Point, CvImage::POINT_AMOUNT> newPoints{};
	vector<int> sumPoints(points.size()), subPoints(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		sumPoints[i] = points[i].x + points[i].y;
		subPoints[i] = points[i].x - points[i].y;
	}
	newPoints[0] = points[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()];
	newPoints[1] = points[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()];
	newPoints[2] = points[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()];
	newPoints[3] = points[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()];

	return newPoints;
}

array<Point, CvImage::POINT_AMOUNT> CvImage::getCountours(const Mat& img)
{
	vector<vector<Point>> countors{};
	vector<Vec4i> hierarchy{};

	findContours(img, countors, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	array<Point, POINT_AMOUNT> biggestArea{};
	vector<vector<Point>> conPoly(countors.size());
	vector<Rect> boundRect(countors.size());

	double area{}, maxArea{}, peri{};
	int objCor{};

	for (int i = 0; i < countors.size(); i++)
	{
		area = contourArea(countors[i]);

		if (area > 1000.0)
		{
			peri = arcLength(countors[i], true);
			approxPolyDP(countors[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				maxArea = area;
				biggestArea = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
			}
		}
	}

	return biggestArea;
}

Mat CvImage::findDoc()
{
	array<Point, POINT_AMOUNT> points = getCountours(preProcessing());
	Mat imgWarp = warpImg(reorder(points));

	return imgWarp;
}
