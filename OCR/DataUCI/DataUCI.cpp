#include "DataUCI.hpp"

const std::string DataUCI::train_path_("../training_set/step1/uci/digits.png");

DataUCI::DataUCI()
  : AData(500)			// number of sample sets (94 digits is one set)
{
}
