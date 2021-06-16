#include "../header/project_3.h"

void project_three() {

	VideoCapture cap(1);
	Mat img;
	vector<Rect> plates;

	// 預訓練集
	string xmlPath = "./Resources/haarcascade_russian_plate_number.xml";
	CascadeClassifier plateCascade;
	plateCascade.load(xmlPath);
	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	while (true) {

		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
		
		for (int i = 0; i < plates.size(); i++) {//抓取畫面中每個的車牌
			Mat imgCrop = img(plates[i]);
			imshow(to_string(i), imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 2);
		}
		imshow("Original", img);
		waitKey(1);
	}
}