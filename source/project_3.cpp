#include "../header/project_3.h"

void project_three() {

	VideoCapture cap(1);
	Mat img;
	vector<Rect> plates;

	// �w�V�m��
	string xmlPath = "./Resources/haarcascade_russian_plate_number.xml";
	CascadeClassifier plateCascade;
	plateCascade.load(xmlPath);
	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	while (true) {

		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
		
		for (int i = 0; i < plates.size(); i++) {//����e�����C�Ӫ����P
			Mat imgCrop = img(plates[i]);
			imshow(to_string(i), imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 2);
		}
		imshow("Original", img);
		waitKey(1);
	}
}