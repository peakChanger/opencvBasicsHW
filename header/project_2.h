#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void project_two();  // Document scanner
void drawPoints(vector<Point> points, Scalar, Mat input_img, Mat& output_img);
vector<Point> reorderPoints(vector<Point> inputPoints);
Mat preProcessing(Mat img);
Mat getWarp(Mat img, vector<Point>, float width, float height);
vector<Point> findPaper(Mat input_img, Mat& output_img);