#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

void GammaCorrection(cv::Mat& src, cv::Mat& dst, float fGamma)

{

	unsigned char lut[256];

	for (int i = 0; i < 256; i++)

	{

		lut[i] = static_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
	}

	dst = src.clone();
    const int channels = dst.channels();

	switch (channels)
	{
	case 1:
		for (auto it = dst.begin<uchar>(); it != dst.end<uchar>(); ++it) 
		{
			*it = lut[(*it)];
		}

		break;
	case 3:
		for (auto it = dst.begin<cv::Vec3b>(); it != dst.end<cv::Vec3b>(); ++it)
		{
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}

		break;
	}

}

int main(int argv, char **argc)
{
	const int max = 256;
	const int block_w = 768;
	const int block_h = 60;
	cv::Size size(block_w, block_h);

	const int count = 6;

	cv::Mat image(block_h, block_w, CV_8UC1, cv::Scalar(0));
	for (int i = 0; i < block_w; ++i) 
	{
		for (int j = 0; j < block_h; ++j)
		{
			image.at<unsigned char>(j, i) = i * max / block_w;
		}
	}

	cv::Mat new_image1(block_h * count, block_w, CV_8UC1, cv::Scalar(0));
	cv::Rect zone = cv::Rect(0, 0, size.width, size.height);
	image.copyTo(new_image1(zone));

	cv::Mat tmp_img;
	for (int i = 1; i < count; i++) {
		zone = cv::Rect(0, size.height * i, size.width, size.height);
		float fGamma = 2.1 + i * 0.1;
		GammaCorrection(image, tmp_img, fGamma);
		tmp_img.copyTo(new_image1(zone));

		cv::putText(new_image1,
			std::to_string(fGamma),
			cv::Point(0, size.height * (i + 0.5)),
			cv::FONT_HERSHEY_COMPLEX_SMALL,
			1,
			cv::Scalar::all(255),
			1);
	}

	imshow("qamma_correction_img1", new_image1);

	for (int i = 0; i < block_w; ++i)
	{
		for (int j = 0; j < block_h; ++j)
		{
			image.at<unsigned char>(j, i) = i * max / block_w / 10 * 10;
		}
	}

	cv::Mat new_image2(block_h * count, block_w, CV_8UC1, cv::Scalar(0));
	zone = cv::Rect(0, 0, size.width, size.height);
	image.copyTo(new_image2(zone));

	for (int i = 1; i < count; i++) {
		zone = cv::Rect(0, size.height * i, size.width, size.height);
		float fGamma = 2.1 + i * 0.1;
		GammaCorrection(image, tmp_img, fGamma);
		tmp_img.copyTo(new_image2(zone));

		cv::putText(new_image2,
			std::to_string(fGamma),
			cv::Point(0, size.height * (i + 0.5)),
			cv::FONT_HERSHEY_COMPLEX_SMALL,
			1,
			cv::Scalar::all(255),
			1);
	}
	imshow("qamma_correction_img2", new_image2);

	cv::waitKey(0);
	return 0;
} 