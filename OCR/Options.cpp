#include <boost/program_options.hpp>
#include <stdexcept>
#include "Options.hpp"

const std::string	Options::usage_("usage: try --help for details on the options available");
int			Options::op_n_ = 0;
unsigned char		Options::char_ = false;
unsigned char		Options::text_ = false;
unsigned char		Options::test_ = false;
unsigned char		Options::knn_ = false;
unsigned char		Options::ann_ = false;
unsigned char		Options::uci_ = false;
std::string		Options::char_path_;
std::string		Options::text_path_;
std::string		Options::test_path_;
unsigned int		Options::k_ = false;

const char		Options::HELP = 1;

int	Options::parse(int ac, char** av)
{
  namespace po = boost::program_options;

  po::options_description desc("allowed options");
  desc.add_options()
    ("char", po::value<std::string>(), "run character-only ocr, and set input file path to arg")
    ("text", po::value<std::string>(), "run whole-text ocr, and set input file path to arg")
    ("test", po::value<std::string>(), "set test dataset's path to arg")
    ("knn", "run classification using K-Nearest Neighbour")
    ("k", po::value<int>(), "run K-Nearest Neighbour with k=arg")
    ("ann", "run classification using Artificial Neural Network")
    ("uci", "use UCI Machine Learning Repository's training set")
    ("help", "produce help message")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
    {
      std::cout << desc << std::endl;
      return HELP;
    }

  if (vm.count("char"))
    {
      char_ = true;
      char_path_ = vm["char"].as<std::string>();
    }

  if (vm.count("text"))
    {
      text_ = true;
      text_path_ = vm["text"].as<std::string>();
    }

  if (vm.count("test"))
    {
      test_ = true;
      test_path_ = vm["test"].as<std::string>();
    }
  
  if (vm.count("knn"))
    {
      knn_ = true;
    }

  if (vm.count("ann"))
    {
      ann_ = true;
    }

  if (vm.count("k"))
    {
      if (ann_)
	throw std::runtime_error("--k cannot be set for --ann ... did you mean to use --knn instead?");
      k_ = vm["k"].as<int>();
    }
  else
    k_ = 1;

  if (vm.count("uci"))
    {
      uci_ = true;
    }

  if (not knn_ && not ann_)
    {
      knn_ = true;
    }
  
  if (knn_ && ann_)
    throw std::runtime_error("cannot run with both --knn and --ann option");
    
  return 0;
}
