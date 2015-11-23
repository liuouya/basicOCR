#include <iosfwd>
#include <iomanip>
#include "Ocr.hpp"
#include "Options.hpp"
#include "IClassifier.hpp"
#include "KNN/ClassifierKNN.hpp"
#include "ANN/ClassifierANN.hpp"

Ocr::Ocr()
  : src_image_(nullptr),
    classifier_(Options::is_knn() ?
		static_cast<IClassifier*>(new ClassifierKNN) :
		static_cast<IClassifier*>(new ClassifierANN))
{
  classifier_->train();
  if (Options::run_test())
    {
      std::streamsize ss = std::cout.precision();
      std::cout << ANSI_GREEN
		<< "test result: " << std::setprecision(2) << std::fixed
		<< (1.00 - classifier_->test()) * 100 << "% accurate"
		<< std::setprecision(ss) << ANSI_RESET << std::endl;
    }
}

char	Ocr::classify(void* image)
{
  src_image_ = reinterpret_cast<cv::Mat*>(image);
  return classifier_->classify(src_image_);
}

std::string	Ocr::digitize(void* image)
{
  src_image_ = reinterpret_cast<cv::Mat*>(image);
  return classifier_->digitize(src_image_);
}
