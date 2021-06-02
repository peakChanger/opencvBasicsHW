#include "../header/chapter_3.h"

void chapter_three() {
	string filePath = ".\\Data\\choco_vanilla.jpg";
	Mat img = imread(filePath);
	Mat imgResize, imgCrop;

	//���s�Y��v���ؤo
	cout << img.size() << endl;
	//resize(img, imgResize, Size(1110, 690));//���w�Y�p�ؤo
	resize(img, imgResize, Size(), 0.5, 0.5);//�̤���Y�p

	//�ŵ��v��
	Rect roi(700, 280, 500, 500);//region of interest
	imgCrop = img(roi);


	imshow("Original", img);
	imshow("Resize", imgResize);
	imshow("Crop", imgCrop);
	waitKey(0);
}
