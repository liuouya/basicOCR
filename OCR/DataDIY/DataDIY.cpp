#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include "DataDIY.hpp"
#include "../KNN/PreprocessorKNN.hpp"
#include "../ANN/PreprocessorANN.hpp"
#include "../Options.hpp"

const std::string	DataDIY::postfix_bmp_(".bmp");
const std::string	DataDIY::postfix_jpg_(".jpg");

const DataDIY::Map DataDIY::sample_files_ =
  {
    {'A', "liu_o-a"},
    {'a', "liu_o-a_small"},
    {'B', "liu_o-b"},
    {'b', "liu_o-b_small"},
    {'C', "liu_o-c"},
    {'c', "liu_o-c_small"},
    {'D', "liu_o-d"},
    {'d', "liu_o-d_small"},
    {'E', "liu_o-e"},
    {'e', "liu_o-e_small"},
    {'F', "liu_o-f"},
    {'f', "liu_o-f_small"},
    {'G', "liu_o-g"},
    {'g', "liu_o-g_small"},
    {'H', "liu_o-h"},
    {'h', "liu_o-h_small"},
    {'I', "liu_o-i"},
    {'i', "liu_o-i_small"},
    {'J', "liu_o-j"},
    {'j', "liu_o-j_small"},
    {'K', "liu_o-k"},
    {'k', "liu_o-k_small"},
    {'L', "liu_o-l"},
    {'l', "liu_o-l_small"},
    {'M', "liu_o-m"},
    {'m', "liu_o-m_small"},
    {'N', "liu_o-n"},
    {'n', "liu_o-n_small"},
    {'0', "liu_o-num_0"},
    {'1', "liu_o-num_1"},
    {'2', "liu_o-num_2"},
    {'3', "liu_o-num_3"},
    {'4', "liu_o-num_4"},
    {'5', "liu_o-num_5"},
    {'6', "liu_o-num_6"},
    {'7', "liu_o-num_7"},
    {'8', "liu_o-num_8"},
    {'9', "liu_o-num_9"},
    {'O', "liu_o-o"},
    {'o', "liu_o-o_small"},
    {'P', "liu_o-p"},
    {'p', "liu_o-p_small"},
    {'Q', "liu_o-q"},
    {'q', "liu_o-q_small"},
    {'R', "liu_o-r"},
    {'r', "liu_o-r_small"},
    {'S', "liu_o-s"},
    {'s', "liu_o-s_small"},
    {'T', "liu_o-t"},
    {'t', "liu_o-t_small"},
    {'U', "liu_o-u"},
    {'u', "liu_o-u_small"},
    {'V', "liu_o-v"},
    {'v', "liu_o-v_small"},
    {'W', "liu_o-w"},
    {'w', "liu_o-w_small"},
    {'X', "liu_o-x"},
    {'x', "liu_o-x_small"},
    {'Y', "liu_o-y"},
    {'y', "liu_o-y_small"},
    {'Z', "liu_o-z"},
    {'z', "liu_o-z_small"},
    {'&', "liu_o-sym_amper"},
    {'\'', "liu_o-sym_apos"},
    {'@', "liu_o-sym_arob"},
    {'`', "liu_o-sym_bquote"},
    {'\\', "liu_o-sym_bslash"},
    {'^', "liu_o-sym_caret"},
    {':', "liu_o-sym_colon"},
    {',', "liu_o-sym_comma"},
    {'$', "liu_o-sym_dollar"},
    {'=', "liu_o-sym_equal"},
    {'!', "liu_o-sym_exclmark"},
    {'>', "liu_o-sym_gthan"},
    {'-', "liu_o-sym_hyphen"},
    {'{', "liu_o-sym_lcbracket"},
    {'(', "liu_o-sym_lparen"},
    {'[', "liu_o-sym_lsqbracket"},
    {'<', "liu_o-sym_lthan"},
    {'#', "liu_o-sym_num"},
    {'%', "liu_o-sym_pcent"},
    {'|', "liu_o-sym_pipe"},
    {'+', "liu_o-sym_plus"},
    {'.', "liu_o-sym_point"},
    {'?', "liu_o-sym_questmark"},
    {'"', "liu_o-sym_quotmark"},
    {'}', "liu_o-sym_rcbracket"},
    {')', "liu_o-sym_rparen"},
    {']', "liu_o-sym_rsqbracket"},
    {';', "liu_o-sym_scolon"},
    {'/', "liu_o-sym_slash"},
    {'*', "liu_o-sym_star"},
    {'~', "liu_o-sym_tilde"},
    {'_', "liu_o-sym_under"}
  };

const char* DataDIY::train_dirs_[] =
  {
    "training_set/step1/monsieur_fed/",
    "training_set/step1/cheddar_jack/",
    "training_set/step1/honey_script/",
    "training_set/step1/notera/",
    "training_set/step1/a_little_sunshine/",
    "training_set/step1/intranet/"
  };

cv::Mat		DataDIY::load_image(const std::string& dirs, const std::string& files)
{
  cv::Mat image = cv::imread((dirs + files + postfix_bmp_).c_str());
  if (image.empty())
    image = cv::imread((dirs + files + postfix_jpg_).c_str());
  if (image.empty())
    std::cerr << "file " << dirs + files + postfix_bmp_
	      << " cannot be loaded ..." << std::endl;
  return image;
}

DataDIY::DataDIY(const std::string& test_path)
  : AData(test_path == "" ? 6 : 1),	// number of sample sets (94 digits is each set)
    sample_dirs_(test_path == "" ?
		 // load the training set
		 std::vector<std::string>(train_dirs_, end(train_dirs_)) :
		 // load the test set
		 std::vector<std::string>{test_path}),
    extractor_()
{
  
  // create a n by m matrix for storing features
  // n is the total number of images available in the training set
  // m is the number of features
  // Mat type should be CV_32F as required by opencv's TrainData methods

  cv::Mat features(class_n_ * set_n_, extractor_.size(), CV_32F);

  // read each sample file, preprocess it, extract features, and store
  // each row represents one sample's features

  Map::const_iterator res_it = sample_files_.begin(), res_end = sample_files_.end();

  for (int i = 0, j = 0; i < class_n_ * set_n_; ++i)
    {
      if (res_it == res_end)
	{
	  res_it = sample_files_.begin();
	  ++j;
	}
      cv::Mat image_raw = load_image(sample_dirs_[j], res_it->second);
      cv::Mat image(pre_proc_->apply(&image_raw));

      // copy extracted features to feature matrix's i-th row
      
      extractor_.extract(image).copyTo(features.row(i));

      ++res_it;
    }
  
  
  // create a m by 1 column matrix to store each sample's corresponding label
  // m is the the total number of images, i.e. 1 label per image
  // Mat type should be CV_32F or CV_32S, will use CV_32F for now
  
  cv::Mat train_labels(class_n_ * set_n_, 1, CV_32F);
  res_it = sample_files_.begin();
  for (int i = 0; i < class_n_ * set_n_; ++i)
    {
      if (res_it == res_end)
	res_it = sample_files_.begin();
      train_labels.at<float>(i, 0) = res_it->first;
      ++res_it;
    }

  // store features and their corresponding labels in a opencv TrainData object

  train_data_ = cv::ml::TrainData::create(features, cv::ml::ROW_SAMPLE, train_labels);
}
