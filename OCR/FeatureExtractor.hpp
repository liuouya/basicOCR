#pragma once

#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include "IPreprocessor.hpp"
#include "AData.hpp"

class				FeatureExtractor
{
    
  enum				IDX
    {
      MOMENT,
      COLOUR,
      PIXEL
    };

  // feature sizes
  constexpr static int			s_hu_moments_ = 7;
  constexpr static int			s_colour_count_ = 1;
  constexpr static int			s_pixels_ = AData::get_dim_x() * AData::get_dim_y();

  // feature descriptions
  std::vector<cv::Mat>			features_;
  cv::Mat				features_all_;

  // feature weights
  cv::Mat				f_weights_;

  // preprocessor  
  std::shared_ptr<IPreprocessor>	pre_proc_;  

public:

  static  constexpr size_t		size()
  {
    return s_pixels_ + s_hu_moments_ + s_colour_count_;
  }

  FeatureExtractor();
  inline const cv::Mat&			get_weights() const;
  cv::Mat				extract(cv::Mat& image);
  
};
