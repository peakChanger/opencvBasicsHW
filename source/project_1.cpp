#include "../header/project_1.h"

vector<vector<int>> newPoints;

void project_one() {
	
	//[LimeGreen,GoldenYellow,Pink](hmin,smin,vmin,hmax,smax,vmax)
	vector<vector<int>> myColors{ {45,170,21,179,255,147} ,{0,220,65,29,255,190} ,{76,81,71,172,248,228} };
	//LimeGreen,GoldenYellow,Pink
	vector<Scalar> myColorValues{ {255,0,255},{0,255,0},{0,255,255} };

	//colorPicker();
	canvas(myColors,myColorValues);
}

void colorPicker() {

	Mat imgHSV, imgMask, imgColor;
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;

	VideoCapture cap(1);
	Mat img;

	namedWindow("Track Bar", WINDOW_AUTOSIZE);//創建視窗
	createTrackbar("Hue min", "Track Bar", &hmin, 179);
	createTrackbar("Hue Max", "Track Bar", &hmax, 179);
	createTrackbar("Sat min", "Track Bar", &smin, 255);
	createTrackbar("Sat max", "Track Bar", &smax, 255);
	createTrackbar("Val min", "Track Bar", &vmin, 255);
	createTrackbar("Val Max", "Track Bar", &vmax, 255);

	while (true) {

		cap.read(img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, imgMask);
		printf("%d,%d,%d,%d,%d,%d\n", hmin, smin, vmin, hmax, smax, vmax);
		imshow("Image", img);
		imshow("Mask", imgMask);

		waitKey(1);
	}

};

void canvas(vector<vector<int>> myColors, vector<Scalar> myColorValues) {
	VideoCapture cap(1);
	Mat img, imgHSV, imgMask, imgDraw;

	while (true)
	{
		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		imshow("Camera", img);
		img.copyTo(imgDraw);
		for (int i = 0; i < myColors.size(); i++)
		{
			Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
			Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
			inRange(imgHSV, lower, upper, imgMask);
			imshow(to_string(i), imgMask);
			Point myPoint = getCoutours(imgMask, imgDraw);
			if (myPoint.x != 0 && myPoint.y != 0)
				newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
		drawOnCanvas(imgDraw, newPoints, myColorValues);
		imshow("Paint", imgDraw);
		waitKey(1);
	}


}

void drawOnCanvas(Mat& img, vector<vector<int>> newPoints, vector<Scalar> myColorValues) {

	for (int i = 0; i < newPoints.size(); i++) {

		circle(img, Point(newPoints[i][0],newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

Point getCoutours(Mat input_img, Mat& output_img) {

	int areaSize = 1000;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(input_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(output_img, contours, -1, Scalar(255, 0, 255));

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {// 區域大小計算

		int area = contourArea(contours[i]);

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objType;

		if (area > areaSize) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//尋找最相近Poly
			cout << area << endl;
			cout << conPoly[i].size() << endl;

			boundRect[i] = boundingRect(conPoly[i]);//尋找包住圖案邊界的矩形
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y + boundRect[i].height / 2;

			drawContours(output_img, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
	return myPoint;
}