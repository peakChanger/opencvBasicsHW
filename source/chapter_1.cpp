#include "../header/chapter_1.h"

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