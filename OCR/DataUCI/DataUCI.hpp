#pragma once

#include <string>
#include "../AData.hpp"

class				DataUCI : public AData
{

  static const std::string	train_path_;

  virtual void			load_data_() {}

public:

  // instanciating DataUCI will load UCI Machine Learning repository's sample set
  // currently path to the training set is hard coded, i.e. train_path_
  
  virtual ~DataUCI() {}
  DataUCI();
  
};
