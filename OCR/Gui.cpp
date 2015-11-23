#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Gui.hpp"
#include "Options.hpp"

const char	Gui::ESC_KEY = 27;
const int	Gui::T_WAITKEY = 10;
bool		Gui::start_ = 0;

// setup a black 800*800 pixel image

cv::Mat		Gui::menu_(cv::Size(800, 800), CV_32F, cv::Scalar(0, 0, 0));

// setup 2 white 800*800 pixel image
// image_ will be used for caching user input, and feeding to the classifier
// clear_ will be used for clearing screen

cv::Mat		Gui::image_(cv::Size(800, 800), CV_32F, cv::Scalar(255, 255, 255));
cv::Mat		Gui::clear_(cv::Size(800, 800), CV_32F, cv::Scalar(255, 255, 255));

void		Gui::init(void)
{

  // display a simple menu  

  cv::namedWindow("OCR", cv::WINDOW_NORMAL);
  cv::putText(menu_, "Press ENTER to start", cvPoint(250, 300),
	      cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(255, 255, 255));
  cv::putText(menu_, "MOUSE -> draw", cvPoint(250, 350),
	      cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255, 255, 255));
  cv::putText(menu_, "ENTER -> classify", cvPoint(250, 375),
	      cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255, 255, 255));
  cv::putText(menu_, "ESC -> clear screen", cvPoint(250, 400),
	      cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255, 255, 255));
  cv::imshow("OCR", menu_);
}

void		Gui::display(void)
{
  char		key_pressed = 0;
  
  while (1)
    {
      key_pressed = cv::waitKey(T_WAITKEY);
      if (not start_ && key_pressed == '\n')
	{
	  start_ = true;
	  clear_screen();
	  cv::setMouseCallback("OCR", Gui::mouse_callback);
	}
      else if (start_ && key_pressed == Gui::ESC_KEY)
	clear_screen();
      else if (start_ && key_pressed == '\n')
	return ;
    }
}

void		Gui::clear_screen(void)
{
  image_ = clear_;
  cv::imshow("OCR", image_);
}

void		Gui::cleanup(void)
{
  cv::destroyAllWindows();
}

void		Gui::mouse_callback(int event,
				    int x,
				    int y,
				    int flags,
				    void* userdata)
{
  static bool	draw;
  
  (void)flags;
  (void)userdata;
  if (cv::EVENT_LBUTTONDOWN == event)
    draw = true;
  if (cv::EVENT_LBUTTONUP == event)
    draw = false;
  if (draw)
    {
      cv::circle(image_, cv::Point(x,y), 20, cv::Scalar(0, 0, 0), -1);
      cv::imshow("OCR", image_);
    }  
}

void		Gui::run(void)
{
  init();
  display();
  cleanup();
}

void*		Gui::get_src_image(Type t)
{
  if (CHAR == t)
    image_ = cv::imread(Options::get_char_path().c_str(), CV_32F);
  if (TEXT == t)
    image_ = cv::imread(Options::get_text_path().c_str(), CV_8UC1);
  else if (image_.empty())
    {
      std::cerr << "error : image loading failed ..." << std::endl;
      return nullptr;
    }
  return &image_;
}
