#include <iostream>
#include <cstdlib>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

int main(int argv, char **argc)
{
	cv::Mat image;
	if (argv != 2) {
		std::cout << "enter image path" << std::endl;
		return -1;
	}

	std::string img_path = argc[1];
	image = cv::imread(img_path, cv::IMREAD_COLOR);

	if (!image.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	int ch = image.channels();
	std::vector<cv::Mat> channels(ch);
	split(image, channels);

	cv::Size size = image.size();
	cv::Mat new_img(size.height * 3, size.width *  (ch + 1) + 1, image.type(), cv::Scalar(0, 0, 0));

	cv::Rect zone(0, 0, size.width, size.height);
	image.copyTo(new_img(zone));

	for (int i = 0; i < ch; i++) {
		cv::Mat tmp_img;
		cvtColor(channels[i], tmp_img, cv::COLOR_GRAY2RGB, ch);
		zone = cv::Rect(size.width * (i + 1), 0, size.width, size.height);
		tmp_img.copyTo(new_img(zone));
	}
	for (int i = 0; i < ch; i++) {
		zone = cv::Rect(size.width * (i + 1), size.height, size.width, size.height);

		cv::Mat tmp_img;
		std::vector<cv::Mat> tmp_channels(ch, cv::Mat::zeros(size.height, size.width, channels[0].type()));
		tmp_channels[i] = channels[i];
		merge(tmp_channels, tmp_img);
		tmp_img.copyTo(new_img(zone));
	}


	cv::Scalar colorLine(0, 0, 255);
	int thicknessLine = 2;
	int len = std::min(size.width, size.height);
	cv::Point p1, p2;
	p1 = cv::Point(len / 4, len / 4 * 3 + size.height);
	p2 = cv::Point(len / 4 * 3, len / 4 * 3 + size.height);
	cv::line(new_img, p1 , p2, colorLine, thicknessLine);

	p1 = cv::Point(len / 8 * 3, len / 4 * 1 + size.height);
	p2 = cv::Point(len / 8 * 3, len / 4 * 2 + size.height);
	cv::line(new_img, p1, p2, colorLine, thicknessLine);

	p1 = cv::Point(len / 8 * 5, len / 4 * 1 + size.height);
	p2 = cv::Point(len / 8 * 5, len / 4 * 2 + size.height);
	cv::line(new_img, p1, p2, colorLine, thicknessLine);

	cv::Point centerCircle(size.width / 2, size.height / 2 + size.height);
	int radiusCircle = len / 2;
	cv::Scalar colorCircle1(0, 0, 255);
	int thicknessCircle = 2;
	cv::circle(new_img, centerCircle, radiusCircle, colorCircle1, thicknessCircle);

	cv::putText(new_img,
		img_path,
		cv::Point(0, size.height * 5 / 2),
		cv::FONT_HERSHEY_COMPLEX_SMALL,
		1.0,
		cv::Scalar(255, 255, 255),
		1);

	imshow("new_img", new_img);

	cv::Mat gray_image;
	cvtColor(image, gray_image, cv::COLOR_RGBA2GRAY, 3);

	imshow("gray_image", gray_image);

	int histSize = 256;

	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	cv::Mat hist;

	calcHist(&gray_image, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512; 
	int hist_h = 512;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0));

	int sq = size.area();
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w * (i - 1), hist_h * (1 - hist.at<float>(i - 1) / sq)),
			cv::Point(bin_w * (i), hist_h * (1 - hist.at<float>(i) / sq)),
			cv::Scalar(255), 2, 8, 0);
	}

	imshow("hist gray", histImage);

	cv::waitKey(0);
	return 0;
}