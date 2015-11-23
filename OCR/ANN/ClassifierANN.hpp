#pragma once

#include <opencv2/core.hpp>
#include "../IClassifier.hpp"

class			ClassifierANN : public IClassifier
{

public:
  
  virtual ~ClassifierANN() {}
  virtual void		train();
  virtual float		test();
  virtual char		classify(cv::Mat* image);
  virtual std::string	digitize(cv::Mat* image);

};
