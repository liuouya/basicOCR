#pragma once

#include <map>
#include <vector>
#include <string>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/ml.hpp>
#include "../AData.hpp"
#include "../IPreprocessor.hpp"
#include "../FeatureExtractor.hpp"

class				DataDIY : public AData
{
  
  typedef std::map<int, const std::string>	Map;
  typedef std::vector<std::string>		Vector;
  typedef cv::ml::TrainData			TrainData;
  
  static const std::string	relative_path_;
  static const std::string	postfix_bmp_;
  static const std::string	postfix_jpg_;
  static const Map		sample_files_;
  static const char*		train_dirs_[];
  
  template<typename T, size_t N>
  static T*			end(T (&arr)[N]) { return arr + N; }

  Vector			sample_dirs_;
  FeatureExtractor	        extractor_;

  cv::Mat			load_image(const std::string& train_dirs,
					   const std::string& files);
  virtual void			load_data_() {}
  
public:

  // instanciating DataDIY will load and prepare the DIY training set
  // currently training directories are hard coded, i.e. train_dirs_
  // giving string arg will load the test set instead
  
  virtual ~DataDIY() {}
  DataDIY(const std::string& test_path = "");
  
};
