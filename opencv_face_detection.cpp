#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


using namespace std;
using namespace cv;

void read_image_and_show(string filePath);// 讀取照片
void read_video_and_play(string filePath);//讀取影片
void read_webCam_and_show(int deviceID);//讀取網路攝影機

int main()
{
	string imageFile = ".\\Data\\ic_vanilla.png";
	//read_image_and_show(imageFile);


	string videoFile = ".\\Data\\guraLoading.mp4";
	//read_video_and_play(videoFile);
	

	int cameraID = 1;
	//read_webCam_and_show(cameraID);
}

void read_image_and_show(string filePath) {
	Mat img = imread(filePath);
	imshow("img", img);
	waitKey(0);
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
		imshow("Webcam Frame",img);
		waitKey(20);
	}
}