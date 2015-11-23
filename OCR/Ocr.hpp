#pragma once

#include <memory>
#include <string>
#include <opencv2/core.hpp>
#include "IClassifier.hpp"

class					Ocr
{

  cv::Mat*				src_image_;
  std::shared_ptr<IClassifier>		classifier_;
  
public:

  Ocr();
  char					classify(void* image);
  std::string				digitize(void* image);
  
};
