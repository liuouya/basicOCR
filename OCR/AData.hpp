#pragma once

#include <memory>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/ml.hpp>
#include "IPreprocessor.hpp"
#include "KNN/PreprocessorKNN.hpp"
#include "ANN/PreprocessorANN.hpp"
#include "Options.hpp"

class					AData
{
  
protected:
  
  typedef cv::ml::TrainData		TrainData;
    
  static constexpr int			class_n_ = 94; // 94 different digits
  static constexpr int			scale_x_ = 50; // image x-dim
  static constexpr int			scale_y_ = 50; // image y-dim
  
  const int				set_n_;
  std::shared_ptr<IPreprocessor>	pre_proc_;
  cv::Ptr<TrainData>			train_data_;	// smart ptr no need to destroy

  AData(int set_n)
  : set_n_(set_n),
    pre_proc_(Options::is_knn() ?
	      static_cast<IPreprocessor*>(new PreprocessorKNN) :
	      static_cast<IPreprocessor*>(new PreprocessorANN)) {}

  virtual void				load_data_() = 0;

public:

  static constexpr unsigned int		get_dim_x() { return scale_x_; }
  static constexpr unsigned int		get_dim_y() { return scale_y_; }
  static constexpr int			get_class_n() { return class_n_; }

  // instanciating Data will prepare data from training directories
  // currently training directories are hard coded, i.e. train_dirs_
  
  virtual ~AData() {}

  inline const cv::Ptr<TrainData>&	get_train_data() const { return train_data_; }
  
};
