#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void project_one();//Virtual painter

void colorPicker();

void canvas(vector<vector<int>> myColors, vector<Scalar> myColorValues);

void drawOnCanvas(Mat& img, vector<vector<int>> newPoints, vector<Scalar> myColorValues);

Point getCoutours(Mat input_img, Mat& output_img);