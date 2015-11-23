#pragma once

#include <opencv2/core.hpp>
#include "../IPreprocessor.hpp"

class				PreprocessorKNN : public IPreprocessor
{

public:

  virtual ~PreprocessorKNN() {}
  virtual cv::Mat		apply(cv::Mat* image, bool target = false);
  virtual std::vector<cv::Mat>	segmentation(cv::Mat* image);

};
