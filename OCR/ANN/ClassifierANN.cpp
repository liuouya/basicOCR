#include "ClassifierANN.hpp"

void	ClassifierANN::train()
{
  
}

float	ClassifierANN::test()
{
  return 100.00;
}

char	ClassifierANN::classify(cv::Mat* image)
{
  (void)image;
  return 'A';
}

std::string	ClassifierANN::digitize(cv::Mat* image)
{
  (void)image;
  return std::string("no idea what's in this doc :D");
}
