#include <iosfwd>
#include "ClassifierKNN.hpp"
#include "../Options.hpp"
#include "../DataDIY/DataDIY.hpp"
#include "../DataUCI/DataUCI.hpp"

ClassifierKNN::ClassifierKNN()
  : data_loader_(Options::is_uci() ?
		 reinterpret_cast<AData*>(new DataUCI) :
		 reinterpret_cast<AData*>(new DataDIY)),
    test_loader_(new DataDIY(Options::get_test_path())),
    pre_proc_(),
    extractor_(),
    train_data_(data_loader_->get_train_data()),	// add option to load from file?
    test_data_(test_loader_->get_train_data()),
    knn_(cv::ml::KNearest::create()),
    k_(Options::get_k())				// will find k-th nearest neighbour
{
  std::cout << ANSI_MAGENTA
	    << std::endl << "classifying using k-Nearest Neighbour ..."
	    << ANSI_RESET << std::endl;
}

void	ClassifierKNN::train()
{
  knn_->train(train_data_);
}

float	ClassifierKNN::test()
{
  cv::Mat result;

  std::cout << ANSI_GREEN
	    << std::endl << "**********    test    **********" << std::endl
	    << "generating test from " << Options::get_test_path() << " ..."
	    << ANSI_RESET << std::endl;

  knn_->findNearest(test_data_->getTrainSamples(), k_, result);
  result -= test_data_->getTrainResponses();   
  return static_cast<float>(cv::countNonZero(result)) / static_cast<float>(AData::get_class_n());
}

char	ClassifierKNN::classify(cv::Mat* image)
{
  cv::Mat image_post_proc(pre_proc_.apply(image, Options::has_char() ? false : true));
  cv::Mat features(extractor_.extract(image_post_proc));
  return knn_->findNearest(features, k_, cv::noArray());
}

std::string		ClassifierKNN::digitize(cv::Mat* image)
{
  std::vector<cv::Mat>	segments(pre_proc_.segmentation(image));
  cv::Mat		image_post_proc, features;
  std::string		text;

  int i = 0;
  for (auto c : segments)
    {
      image_post_proc = pre_proc_.apply(&c, true);
      features = extractor_.extract(image_post_proc);
      text.push_back(knn_->findNearest(features, k_, cv::noArray()));
      if (not ++i % 50)
	text.push_back('\n');
    }
  return text;
}
