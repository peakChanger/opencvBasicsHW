#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void chapter_seven();//²Ä¤C³¹ Shapes/Counter Detection

void getCoutours(Mat input_img, Mat& output_img);