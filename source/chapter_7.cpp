#include "../header/chapter_7.h"

void chapter_seven() {
	string file_path = "./Data/shapes.png";
	Mat img = imread(file_path);

	Mat imgGray, imgBlur, imgCanny, imgDil;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	Mat imgDraw;
	img.copyTo(imgDraw);
	getShapes(imgDil, imgDraw);

	imshow("Original",img);
	//imshow("Image Gray",imgGray);
	//imshow("Image Blur",imgBlur);
	//imshow("Image Dil", imgDil);

	imshow("Result", imgDraw);
	waitKey();
}

void getShapes(Mat input_img, Mat& output_img) {

	int areaSize = 1000;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(input_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(output_img, contours, -1, Scalar(255, 0, 255));

	
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

			//透過數量判斷形狀
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objType = "Triangle"; }
			if (objCor == 4) { 
				float aspectRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspectRatio > 0.95 && aspectRatio < 1.05)
					objType = "Square";
				else
					objType = "Rectangle"; 
				cout << aspectRatio << endl;
			}
			if (objCor > 4 ) { objType = "Circle"; }

			drawContours(output_img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(output_img, boundRect[i].tl(), boundRect[i].br(), Scalar(128, 128, 128), 2);
			putText(output_img, objType, { boundRect[i].x ,boundRect[i].y-5}, FONT_HERSHEY_SCRIPT_COMPLEX, 0.5, Scalar(118, 32, 172), 1);

		}
	}
}