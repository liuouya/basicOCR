#pragma once

#include <vector>
#include <opencv2/core.hpp>

class				IPreprocessor
{

public:

  virtual ~IPreprocessor() {}
  virtual cv::Mat		apply(cv::Mat* image, bool target = false) = 0;
  virtual std::vector<cv::Mat>	segmentation(cv::Mat* image) = 0;
  
};
