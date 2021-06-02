#include "../header/chapter_6.h"

void chapter_six() {

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	string file_path = "./Data/88945093_p0.png";
	Mat img_neko_gura = imread(file_path);
	resize(img_neko_gura, img_neko_gura, Size(), 0.65, 0.65);

	Mat img_hsv, img_mask;
	cvtColor(img_neko_gura, img_hsv, COLOR_BGR2HSV);

	namedWindow("Track Bar",(500,200));
	createTrackbar("Hue min", "Track Bar", &hmin, 179);
	createTrackbar("Hue Max", "Track Bar", &hmax, 179);
	createTrackbar("Sat min", "Track Bar", &smin, 255);
	createTrackbar("Sat max", "Track Bar", &smax, 255);
	createTrackbar("Val min", "Track Bar", &vmin, 255);
	createTrackbar("Val Max", "Track Bar", &vmax, 255);

	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(img_hsv, lower, upper, img_mask);

		imshow("original Gura", img_neko_gura);
		imshow("HSV Gura", img_hsv);
		imshow("mask Gura", img_mask);
		waitKey(1);
	}

}