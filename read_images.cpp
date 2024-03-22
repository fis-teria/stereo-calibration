#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"

using namespace std;
using namespace cv;

int x = 0;

std::string make_spath(std::string dir, int var, std::string tag)
{
  std::string back;
  if (var < 10)
  {
    back = dir + "/00000" + std::to_string(var) + tag;
  }
  else if (var < 100)
  {
    back = dir + "/0000" + std::to_string(var) + tag;
  }
  else if (var < 1000)
  {
    back = dir + "/000" + std::to_string(var) + tag;
  }
  else if (var < 10000)
  {
    back = dir + "/00" + std::to_string(var) + tag;
  }
  std::cout << back << std::endl;
  return back;
}

int main(int argc, char const *argv[])
{
  char* imgs_directory;
  char* extension;
  int im_width, im_height;

  static struct poptOption options[] = {
    { "img_width",'w',POPT_ARG_INT,&im_width,0,"Image width","NUM" },
    { "img_height",'h',POPT_ARG_INT,&im_height,0,"Image height","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory,0,"Directory to save images in","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension,0,"Image extension","STR" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);
  int c;
  while((c = popt.getNextOpt()) >= 0) {}

  VideoCapture cap1(0);
  cap1.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
  cap1.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
  cap1.set(cv::CAP_PROP_BUFFERSIZE, 1);
  cap1.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

  VideoCapture cap2(2);
  cap2.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
  cap2.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
  cap2.set(cv::CAP_PROP_BUFFERSIZE, 1);
  cap2.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

  Mat img1, img_res1, img2, img_res2;
  std::string dir = imgs_directory;
  std::string imgs_directory1 = dir + "left/";
  std::string imgs_directory2 = dir + "right/";
  while (1)
  {
    cap1 >> img1;
    cap2 >> img2;
    //resize(img1, img_res1, Size(im_width, im_height));
    //resize(img2, img_res2, Size(im_width, im_height));
    imshow("IMG1", img_res1);
    imshow("IMG2", img_res2);
    if (waitKey(30) > 0) {
      //char filename1[200], filename2[200];
      //sprintf(filename1, "%sleft%d.%s", imgs_directory, x, extension);
      //sprintf(filename2, "%sright%d.%s", imgs_directory, x, extension);
      std::string filename1 = make_spath(imgs_directory1, x, extension);
      std::string filename2 = make_spath(imgs_directory2, x, extension);

      cout << "Saving img pair " << x << endl;
      imwrite(filename1, img_res1);
      imwrite(filename2, img_res2);
      x++;
    }
  }
  return 0;
}
