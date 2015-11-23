#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

class			Gui
{

  static const char     ESC_KEY;
  static const int      T_WAITKEY;
  static bool		start_;
  static cv::Mat	image_;
  static cv::Mat	clear_;
  static cv::Mat	menu_;

  static void		init(void);
  static void		display(void);
  static void		clear_screen(void);
  static void		cleanup(void);
  static void		mouse_callback(int event,
				       int x,
				       int y,
				       int flags,
				       void* userdata = nullptr);

public:

  enum			Type
    {
      GUI,
      CHAR,
      TEXT
    };

  static void		run(void);
  static void*		get_src_image(Type t = GUI);

};
