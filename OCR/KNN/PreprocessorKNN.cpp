#include <vector>
#include <stdexcept>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include "PreprocessorKNN.hpp"
#include "../Options.hpp"
#include "../AData.hpp"

#include "iosfwd"

cv::Mat	PreprocessorKNN::apply(cv::Mat* image, bool target)
{
  cv::Mat	grey, blur, threshold;
  cv::Mat       roi, resize, final;
  
  // RGB to gray convertion
  // except for image captured from GUI, it's already in grayscale

  grey = image->clone();
  if (not target)
    cv::cvtColor(grey, grey, cv::COLOR_BGR2GRAY);
  
  // smoothing by applying Gaussian blur
  // this should be done before applying adaptive threshold to avoid breaking digits

  cv::GaussianBlur(grey, blur, cv::Size(5, 5), 2, 2);

  // apply adaptive threshold
  // this helps in localizing the effect
  // image captured from GUI need to be converted to CV_8UC1 first
  
  if (target)
    blur.convertTo(blur, CV_8UC1);
  cv::adaptiveThreshold(blur, threshold, 255, 1, 1, 11, 2);

  // contour detection
  // box up ROI and crop

  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(threshold, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
  std::vector<cv::Rect> boxes(contours.size());
  if (not contours.size())
    {
      if (target)
	throw std::runtime_error("cannot detect any character from the target image ...");
      roi = cv::Mat(cv::Size(AData::get_dim_x(), AData::get_dim_y()),
		    CV_32F, cv::Scalar(0, 0, 0));
    }
  else
    {
      int idx = 0;
      for (size_t i = 0; i < contours.size(); ++i)
	{
	  boxes[i]= cv::boundingRect(contours[i]);
	  if (boxes[i].area() > boxes[idx].area())
	    idx = i;
	}
      roi = threshold(boxes[idx]);
    }
  
  // scale the image to x * y pixels

  cv::Size size(AData::get_dim_x(), AData::get_dim_y());
  cv::resize(roi, resize, size);

  // convert it to CV_32F as required by KNN
  
  resize.convertTo(final, CV_32F);

  return final;
}

std::vector<cv::Mat>	PreprocessorKNN::segmentation(cv::Mat* image)
{
  cv::Mat	        grey, blur, threshold, display;
  std::vector<cv::Mat>	segments;

  grey = image->clone();

  // smoothing by applying Gaussian blur
  // this should be done before applying adaptive threshold to avoid breaking digits

  cv::GaussianBlur(grey, blur, cv::Size(5, 5), 2, 2);

  // apply adaptive threshold
  // this helps in localizing the effect
  // image captured from GUI need to be converted to CV_8UC1 first
  
  blur.convertTo(blur, CV_8UC1);
  cv::adaptiveThreshold(blur, threshold, 255, 1, 1, 11, 2);

  // apply some dilation and erosion to join the gaps

  cv::dilate(threshold, threshold, cv::Mat(), cv::Point(-1, -1), 3);
  cv::erode(threshold, threshold, cv::Mat(), cv::Point(-1, -1), 3 * 2);
  cv::dilate(threshold, threshold, cv::Mat(), cv::Point(-1, -1), 3);

  // contour detection
  // box up ROIs and pushback to segments

  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(threshold, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
  std::vector<cv::Rect> boxes(contours.size());
  if (not contours.size())
    throw std::runtime_error("cannot detect any character from the target image ...");
  else
    {
      cv::Scalar colour(255, 0, 0);
      display = threshold.clone();
      for (size_t i = 0; i < contours.size(); ++i)
	{
	  boxes[i]= cv::boundingRect(contours[i]);
	  segments.emplace_back(threshold, boxes[i]);
	  cv::rectangle(display, boxes[i].tl(), boxes[i].br(), colour);
	}
    }

  // display contour boxes
  
  cv::namedWindow("OCR - contour", cv::WINDOW_NORMAL);
  cv::imshow("OCR - contour", display);
  cv::waitKey(0);
  cv::destroyAllWindows();

  return segments;
}
