#include <opencv2/imgcodecs.hpp>
#include "PreprocessorANN.hpp"
#include "../AData.hpp"

cv::Mat	PreprocessorANN::apply(cv::Mat* image, bool target)
{
  cv::Mat	tmp(AData::get_dim_x(), AData::get_dim_y(), CV_32F);

  (void)image;
  (void)target;
  return tmp;
}

std::vector<cv::Mat>	PreprocessorANN::segmentation(cv::Mat* image)
{
  (void)image;
  return std::vector<cv::Mat>{cv::Mat()};
}
