#include "../header/chapter_3.h"

void chapter_three() {
	string filePath = ".\\Data\\choco_vanilla.jpg";
	Mat img = imread(filePath);
	Mat imgResize, imgCrop;

	//重新縮放影像尺寸
	cout << img.size() << endl;
	//resize(img, imgResize, Size(1110, 690));//指定縮小尺寸
	resize(img, imgResize, Size(), 0.5, 0.5);//依比例縮小

	//剪裁影像
	Rect roi(700, 280, 500, 500);//region of interest
	imgCrop = img(roi);


	imshow("Original", img);
	imshow("Resize", imgResize);
	imshow("Crop", imgCrop);
	waitKey(0);
}
