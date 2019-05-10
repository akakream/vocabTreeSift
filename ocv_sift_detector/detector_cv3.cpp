/*
This code computes SIFT descriptors using the OpenCV library for
a given input image and writes them to a text file using the
file format defined by Dave Lowes SIFT demo code. The written
file starts with two integers giving the total number of
keypoints n and the length of the descriptor vector d. The first
row of each descriptor describes the keypoint with four floating
point numbers (subpixel row and column, size and orientation
(radians -pi/pi). The following ceil(d/20) rows contain the
invariant descriptor.
*/
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


std::vector<std::string> ocv_kps_to_strings(const std::vector<cv::KeyPoint> &kps)
{
  std::vector<std::string> strings;
  for(auto const &kp: kps){
    std::stringstream buffer;
    buffer << kp.pt.x << " " << kp.pt.y << " " << kp.size << " " << (kp.angle - 180.0)*M_PI/180.0;
    strings.push_back(buffer.str());
  }
  return strings;
}


std::vector<std::string> ocv_mat_to_strings(const cv::Mat &d)
{
  std::vector<std::string> strings;
  for(unsigned i = 0; i < d.rows; ++i){
    std::stringstream buffer;
    for(unsigned j = 0; j < d.cols; ++j){
      if(j > 0 && j % 20 == 0){ buffer << std::endl; }
      buffer << d.at<float>(i, j) << " ";
    }
    strings.push_back(buffer.str());
  }
  return strings;
}


std::vector<std::string> ocv_descriptor_strings(const std::vector<cv::KeyPoint> &kps, const cv::Mat &d)
{
  std::vector<std::string> ostrings;
  std::vector<std::string> dstrings = ocv_mat_to_strings(d);
  std::vector<std::string> kstrings = ocv_kps_to_strings(kps);

  for(unsigned i = 0; i < kstrings.size(); ++i){ ostrings.push_back(kstrings[i] + '\n' + dstrings[i]); }

  return ostrings;
}


int write_to_descriptor_file(std::string filename, const std::vector<string> &v, unsigned binc)
{
  ofstream file;
  file.open(filename);
  file << v.size() << " " << binc << std::endl;
  for(auto const &e: v){ file << e << std::endl; }
  file.close();
  return 0;
}


int main(int argc, const char* argv[])
{
  if(argc < 3){
    std::cout << "This program computes the SIFT descriptors of an image and writes them to a output file."
              << std::endl << "ocv_sift_detector <input> <output>" << std::endl;
    return 1;
  }

  const cv::Mat input = cv::imread(argv[1]);

  Ptr<FeatureDetector> detector = cv::xfeatures2d::SIFT::create();
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(input, keypoints);

  Mat descriptors;
  detector->compute(input, keypoints, descriptors);

  std::vector<string> strings = ocv_descriptor_strings(keypoints, descriptors);
  write_to_descriptor_file(argv[2], strings, descriptors.cols);

  // Add results to image and save.
  //cv::Mat output;
  //cv::drawKeypoints(input, keypoints, output);
  //cv::imwrite("sift_result.jpg", output);

  return 0;
}
