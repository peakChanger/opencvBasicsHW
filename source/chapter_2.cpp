#include "../header/chapter_2.h"

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
