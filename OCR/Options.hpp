#pragma once

#include <string>

#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_RESET   "\x1b[0m"

class				Options
{

  static const std::string	usage_;
  static int			op_n_;
  static unsigned char	        char_;
  static unsigned char	        text_;
  static unsigned char	        test_;
  static unsigned char		knn_;
  static unsigned char		ann_;
  static unsigned char		uci_;
  static std::string		char_path_;
  static std::string		text_path_;
  static std::string		test_path_;
  static unsigned int		k_;

public:

  static const char		HELP;

  static int			parse(int ac, char** av);
  static int		        op_n() { return op_n_; }
  static bool			has_char() { return char_; }
  static bool			has_text() { return text_; }
  static bool			run_test() { return test_; }
  static bool			is_knn() { return knn_; }
  static bool			is_ann() { return ann_; }
  static bool			is_uci() { return uci_; }
  static const std::string&	get_char_path() { return char_path_; }
  static const std::string&	get_text_path() { return text_path_; }
  static const std::string&	get_test_path() { return test_path_; }
  static unsigned int		get_k() { return k_; }

};
