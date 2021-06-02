#include "../header/chapter_2.h"

void chapter_two() {
	string imageFile = ".\\Data\\ic_vanilla.png";
	Mat img = imread(imageFile);
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

	resize(img, img, Size(), 0.5, 0.5);//���Y��H��K�����i

	//�Ƕ�
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	//�����ҽk
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);

	//Canny ��t�����A�q�`�b�����ҽk��i����t���
	Canny(imgBlur, imgCanny, 50, 150);

	//Dilate �v������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//�W�[Size�W�[��쪺�q�A�Ϥ���M
	dilate(imgCanny, imgDilate, kernel);

	//Erode �v���I�k
	erode(imgDilate, imgErode, kernel);

	imshow("Original", img);
	imshow("Gray Img", imgGray);
	imshow("Gaussian Blur", imgBlur);
	imshow("Canny", imgCanny);
	imshow("dilate", imgDilate);
	imshow("Erode", imgErode);
	waitKey(0);
}
