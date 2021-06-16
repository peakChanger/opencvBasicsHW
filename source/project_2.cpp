#include "../header/project_2.h"


void project_two() {


	string filePath = "./Data/paper.jpg";
	Mat img = imread(filePath);

	resize(img, img, Size(), 0.2, 0.2);

	//�_�l��M�쪺�I�P���ӻݨD�Ʀn���I
	vector<Point> initPoints, docPoints;

	//�M��e�����̤j���|����
	Mat imgContours;
	img.copyTo(imgContours);
	initPoints = findPaper(preProcessing(img), imgContours);

	//�e�W�����I�I
	Mat imgPoints, imgPoints2;
	drawPoints(initPoints, Scalar(0, 0, 255), imgContours, imgPoints);

	//���s�Ƨ��I�I�H�Q�]��
	docPoints = reorderPoints(initPoints);
	drawPoints(docPoints, Scalar(0, 0, 255), imgContours, imgPoints2);

	//Warp
	Mat imgWarp;
	float w = 420, h = 596;//A4 Paper Size
	imgWarp = getWarp(img, docPoints, w, h);

	//Crop
	int cropValue = 5;
	Mat imgCrop;
	Rect roi(cropValue, cropValue, w - (2 * cropValue), h - (2 * cropValue));
	imgCrop = imgWarp(roi);

	imshow("img", img);
	imshow("imgPoints2", imgPoints2);
	imshow("imgWarp", imgWarp);
	imshow("imgCrop", imgCrop);
	waitKey(0);

	return;
}

void drawPoints(vector<Point> points, Scalar color, Mat input_img, Mat& output_img) {
	input_img.copyTo(output_img);

	for (int i = 0; i < points.size(); i++) {
		circle(output_img, points[i], 15, color, FILLED);
		putText(output_img, to_string(i), points[i], FONT_HERSHEY_SIMPLEX, 1, color, 3);
	}
	return;
}

vector<Point> reorderPoints(vector<Point> inputPoints) {

	vector<Point> reorderPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < inputPoints.size(); i++) {
		sumPoints.push_back(inputPoints[i].x + inputPoints[i].y);
		subPoints.push_back(inputPoints[i].x - inputPoints[i].y);
	}

	reorderPoints.push_back(inputPoints[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	reorderPoints.push_back(inputPoints[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	reorderPoints.push_back(inputPoints[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	reorderPoints.push_back(inputPoints[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return reorderPoints;
}

Mat getWarp(Mat img, vector<Point> points, float width, float height) {
	Mat imgWarp;
	const int cornerCount = 4;

	Point2f src[cornerCount];
	for (int i = 0; i < cornerCount; i++) {
		src[i] = points[i];
	}
	Point2f dst[4] = { {0.0f,0.0f},{width,0.0f},{0.0f,height},{width,height} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(width, height));

	return imgWarp;
}

Mat preProcessing(Mat img) {
	Mat imgGray, imgBlur, imgCanny, imgErode, imgDilate;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernal);

	return imgDilate;
}

vector<Point> findPaper(Mat input_img, Mat& output_img) {

	int areaSize = 1000;
	int maxArea = 0;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(input_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	if (output_img.size == 0)//�קK�e�b��Mat
		input_img.copyTo(output_img);

	vector<Point> biggest;
	for (int i = 0; i < contours.size(); i++) {// �ϰ�j�p�p��

		int area = contourArea(contours[i]);

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objType;

		if (area > areaSize) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//�M��̬۪�Poly

			if (area > maxArea && conPoly[i].size() == 4) {//�M��|����
				drawContours(output_img, conPoly, i, Scalar(255, 0, 255), 2);
				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
				maxArea = area;
			}
		}
	}
	return biggest;
}