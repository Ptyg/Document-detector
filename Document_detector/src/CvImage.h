#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <array>
#include <memory>

using std::move;
using std::array;
using std::string;

using cv::imread;
using cv::Mat;
using cv::Point;


class CvImage
{
	static constexpr int POINT_AMOUNT = 4;
	cv::Mat originImage{};
public:
	CvImage(const string& fileName) : originImage(imread(fileName)) {}
	CvImage(string&& fileName) : originImage(imread(move(fileName))) {}

	[[nodiscard]] Mat preProcessing();
	[[nodiscard]] Mat warpImg(const array<Point, POINT_AMOUNT>& points);
	[[nodiscard]] array<Point, POINT_AMOUNT> reorder(const array<Point, POINT_AMOUNT>& points);
	[[nodiscard]] array<Point, POINT_AMOUNT> getCountours(const Mat& img);

	[[nodiscard]] Mat findDoc();
};

