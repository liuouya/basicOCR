#pragma once

#include <string>
#include <opencv2/core.hpp>

class			IClassifier
{
  
public:

  virtual ~IClassifier() {}
  virtual void		train() = 0;
  virtual float		test() = 0;
  virtual char		classify(cv::Mat* image) = 0;
  virtual std::string	digitize(cv::Mat* image) = 0;

};
