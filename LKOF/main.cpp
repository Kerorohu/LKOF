#include "pch.h"
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\core\core.hpp>//OpenCV���Ŀ�ͷ�ļ�
#include <opencv2\highgui\highgui.hpp>//OpenCVͼ�δ���ͷ�ļ�
#include <opencv2/opencv.hpp>
#include "LKOF.h"

using namespace std;
using namespace cv;
using namespace lk;

int main() {
	Mat frame;
	Mat result;

	LKOF *lk = new LKOF("test.mp4");
	namedWindow("LKOF", WINDOW_AUTOSIZE);

	while (true)
	{
		lk->getVideo >> frame;

		if (!frame.empty())
		{
			lk->getXandY(frame, result);
		}
		else
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		int c = waitKey(100);
		if ((char)c == 27)
		{
			break;
		}
	}
}