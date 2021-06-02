#include "../header/chapter_5.h"

void chapter_five() {

	string file_path = "./Data/88775396_p0.png";
	Mat img_gura = imread(file_path);
	resize(img_gura, img_gura, Size(), 0.5, 0.5);

	float w = 300, h = 200;

	Point2f src[4] = { {473,562},{588,526},{480,653},{587,607} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	Mat img_warp;
	warpPerspective(img_gura, img_warp, matrix, Point(w, h));

	for (int i = 0; i < 4; i++)
		circle(img_gura, src[i], 10, Scalar(0, 0, 256), FILLED);

	imshow("Gawr Gura", img_gura);
	imshow("Warp Perspective", img_warp);
	waitKey(0);
}