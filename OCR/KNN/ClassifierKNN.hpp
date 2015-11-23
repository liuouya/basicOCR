#pragma once

#include <memory>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/ml.hpp>
#include "PreprocessorKNN.hpp"
#include "../IClassifier.hpp"
#include "../AData.hpp"
#include "../FeatureExtractor.hpp"

class				ClassifierKNN : public IClassifier
{

  typedef cv::ml::TrainData	TrainData;
  typedef cv::ml::KNearest	KNearest;
  
  std::shared_ptr<AData>	data_loader_;
  std::shared_ptr<AData>	test_loader_;
  PreprocessorKNN		pre_proc_;
  FeatureExtractor		extractor_;
  cv::Ptr<TrainData>		train_data_;
  cv::Ptr<TrainData>		test_data_;
  cv::Ptr<KNearest>		knn_;
  int				k_;
  
public:

  ClassifierKNN();
  virtual ~ClassifierKNN() {}
  virtual void			train();
  virtual float			test();
  virtual char			classify(cv::Mat* image);
  virtual std::string		digitize(cv::Mat* image);

};
