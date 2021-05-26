﻿#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


using namespace std;
using namespace cv;

void chapter_one(int choose);//第一章教學 Read Image Video and Webcam
void chapter_two();//第二章教學 Basic Function
void chapter_three();//Resize and Crop

void read_image_and_show(string filePath);// 讀取照片
void read_video_and_play(string filePath);//讀取影片
void read_webCam_and_show(int deviceID);//讀取網路攝影機



int main()
{
	//chapter_one(2);//(0照片，1影片，2網路攝影機)
	chapter_two();
	//chapter_three();
}

void chapter_one(int choose) {
	string imageFile;
	string videoFile;
	int cameraID;
	switch (choose)
	{
	case 0:
		imageFile = ".\\Data\\ic_vanilla.png";
		read_image_and_show(imageFile);
		break;
	case 1:
		videoFile = ".\\Data\\guraLoading.mp4";
		read_video_and_play(videoFile);
		break;
	case 2:
		cameraID = 1;
		read_webCam_and_show(cameraID);
		break;
	default:
		printf("Error number");
		break;
	}
	return;
}

void chapter_two() {
	string imageFile = ".\\Data\\ic_vanilla.png";
	Mat img = imread(imageFile);
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

	resize(img, img, Size(), 0.5, 0.5);//先縮放以方便做報告

	//灰階
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	//高斯模糊
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);

	//Canny 邊緣偵測，通常在高斯模糊後進行邊緣抓取
	Canny(imgBlur, imgCanny, 50, 150);

	//Dilate 影像膨脹
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//增加Size增加找到的量，反之亦然
	dilate(imgCanny, imgDilate, kernel);

	//Erode 影像侵蝕
	erode(imgDilate, imgErode, kernel);

	imshow("Original", img);
	imshow("Gray Img", imgGray);
	imshow("Gaussian Blur", imgBlur);
	imshow("Canny", imgCanny);
	imshow("dilate", imgDilate);
	imshow("Erode", imgErode);
	waitKey(0);
}

void chapter_three() {
	string filePath = ".\\Data\\choco_vanilla.jpg";
	Mat img = imread(filePath);
	Mat imgResize,imgCrop;

	//重新縮放影像尺寸
	cout << img.size() << endl;
	//resize(img, imgResize, Size(1110, 690));//指定縮小尺寸
	resize(img, imgResize, Size(), 0.5, 0.5);//依比例縮小

	//剪裁影像
	Rect roi(700,280,500,500);//region of interest
	imgCrop = img(roi);


	imshow("Original", img);
	imshow("Resize", imgResize);
	imshow("Crop", imgCrop);
	waitKey(0);
}

void read_image_and_show(string filePath) {
	Mat img = imread(filePath);
	imshow("img", img);
	waitKey(0);//有waitKey才會停滯畫面，否則視窗不會保留
}

void read_video_and_play(string filePath) {
	VideoCapture cap(filePath);
	Mat img;
	while (1) {
		cap.read(img);
		imshow("Frame", img);
		waitKey(20);
	}
};

void read_webCam_and_show(int deviceID) {
	VideoCapture cap(deviceID);
	Mat img;
	while (1) {
		cap.read(img);
		imshow("Webcam Frame", img);
		waitKey(20);
	}
}