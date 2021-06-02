#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void chapter_one(int choose);//第一章教學 Read Image Video and Webcam

void read_image_and_show(string filePath);// 讀取照片
void read_video_and_play(string filePath);//讀取影片
void read_webCam_and_show(int deviceID);//讀取網路攝影機