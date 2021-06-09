#include "../header/chapter_8.h"

void chapter_eight() {

	string xmlPath = "./Resources/haarcascade_frontalface_default.xml";
	string imgPath = "./Data/20210329_110721.jpg";
	Mat img = imread(imgPath);
	Mat imgFaces;
	img.copyTo(imgFaces);

	CascadeClassifier faceCascade;
	faceCascade.load(xmlPath);
	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> faces;//¤HÁy¶°
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
	for (int i = 0; i < faces.size(); i++) {
		rectangle(imgFaces, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 2);
	}
	
	imshow("Original", img);
	imshow("Image Faces", imgFaces);
	waitKey();
}