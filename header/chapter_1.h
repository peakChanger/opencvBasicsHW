#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void chapter_one(int choose);//�Ĥ@���о� Read Image Video and Webcam

void read_image_and_show(string filePath);// Ū���Ӥ�
void read_video_and_play(string filePath);//Ū���v��
void read_webCam_and_show(int deviceID);//Ū��������v��