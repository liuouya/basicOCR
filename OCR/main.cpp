#include <exception>
#include <stdexcept>
#include <iostream>
#include "Options.hpp"
#include "Gui.hpp"
#include "Ocr.hpp"

int	main(int ac, char** av)
{

  try
    {
      // parse command line options

      if (Options::HELP == Options::parse(ac, av))
	return 0;

      // if the user didn't provide image path for char or text
      // obtain a char image from gui

      if (not Options::has_char() && not Options::has_text())
	Gui::run();

      // run character-only ocr

      if (not Options::has_text())
	{
	  void* image = Options::has_char() ?
	    Gui::get_src_image(Gui::CHAR) : Gui::get_src_image();
	  if (not image)
	    throw std::runtime_error("cannot load target image ...");

	  Ocr ocr;
	  std::cout << ANSI_YELLOW
		    << std::endl << "********** prediction **********" << std::endl
		    << "char-only ocr result: " << ocr.classify(image)
		    << ANSI_RESET << std::endl << std::endl;
	}

      // run whole text ocr

      if (Options::has_text())
	{
	  void* image = Gui::get_src_image(Gui::TEXT);
	  if (not image)
	    throw std::runtime_error("cannot load target image ...");

	  Ocr ocr;
	  std::cout << ANSI_YELLOW
		    << std::endl << "********** prediction **********" << std::endl
		    << "whole-text ocr result: " << std::endl
		    << std::endl << ocr.digitize(image)
		    << ANSI_RESET << std::endl << std::endl;
	}
      
    }
  catch(const std::exception& e)
    {
      std::cerr << "error: " << e.what() << std::endl
		<< "something went wrong ... abort." << std::endl;
    }

  return 0;
}
