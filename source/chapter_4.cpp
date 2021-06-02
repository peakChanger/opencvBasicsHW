#include "../header/chapter_4.h"

void chapter_four() {
	//512*512 ¯Â¥Õµe¥¬
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

	circle(img, Point(256, 256), 155, Scalar(128,128,0), FILLED);
	rectangle(img, Point(100, 100), Point(200, 200), Scalar(0, 128, 128),FILLED);
	line(img, Point(100, 100), Point(365, 365), Scalar(128, 0, 128), 2);

	putText(img,"Nekopara",Point(130,450), FONT_HERSHEY_SCRIPT_COMPLEX,2,Scalar(118,32,172),2);

	imshow("Paint",img);
	waitKey(0);
}