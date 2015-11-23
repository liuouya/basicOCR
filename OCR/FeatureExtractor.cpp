#include <iostream>

#include <opencv2/imgproc.hpp>
#include "FeatureExtractor.hpp"

FeatureExtractor::FeatureExtractor()
  : features_{ cv::Mat(1, s_hu_moments_, CV_32F),
    cv::Mat(1, s_colour_count_, CV_32F),
    cv::Mat(1, s_pixels_, CV_32F) },
    features_all_(),
    f_weights_(cv::Mat::ones(0, FeatureExtractor::size(), CV_32F)),
    pre_proc_(Options::is_knn() ?
	      static_cast<IPreprocessor*>(new PreprocessorKNN) :
	      static_cast<IPreprocessor*>(new PreprocessorANN))
{   
  // rebalance feature weights
  
}

const cv::Mat&		FeatureExtractor::get_weights() const
{
  return f_weights_;
}

cv::Mat			FeatureExtractor::extract(cv::Mat& image)
{
  // extract Hu's Moments
  cv::HuMoments(cv::moments(image),features_[MOMENT]);
  features_[MOMENT] = features_[MOMENT].reshape(0, 1);
  features_[MOMENT].convertTo(features_[MOMENT], CV_32F);

  // extract coloured pixel count
  features_[COLOUR] = 0;

  // extract pixels
  features_[PIXEL] = image.reshape(0, 1);
  
  // consolidate all features
  cv::hconcat(features_, features_all_);

  return features_all_;
}
