#pragma once

#include <opencv2/core.hpp>
#include "../IPreprocessor.hpp"

class				PreprocessorANN : public IPreprocessor
{

public:

  virtual ~PreprocessorANN() {}
  virtual cv::Mat		apply(cv::Mat* image, bool target = false);
  virtual std::vector<cv::Mat>	segmentation(cv::Mat* image);

};
