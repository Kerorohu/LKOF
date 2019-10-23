#pragma once
#ifndef LKOF_H_
#define LKOF_H_

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

namespace lk{
	class LKOF
	{
	public:
		bool addNewPoints();
		bool acceptTrackedPoint(int i);
		void setImage(Mat imageIn);
		void setPreImage(Mat preImageIn);
		void setFileName(String fileName);
		void setX(int x);
		void setY(int y);
		VideoCapture getVideo();
		int getX();
		int getY();
		String getFileName();
		Mat getImage();
		Mat getPreImage();
		float getRate();
		LKOF(String fileName);
		void getXandY(Mat &frame, Mat &output);

	private:
		struct Datas
		{
			Mat image;
			Mat preImage;
		}datas;
		String fileName;

		VideoCapture video;

		int cirStop;
		float rate;
		std::mutex myMutex;
		int x, y;
		string windowName;
		
		vector<Point2f> points[2];	// point0为特征点的原来位置，point1为特征点的新位置
		vector<Point2f> initial;	// 初始化跟踪点的位置
		vector<Point2f> features;	// 检测的特征
		int maxCount = 500;		// 检测的最大特征数
		double qLevel = 0.01;	// 特征检测的等级
		double minDist = 10.0;	// 两特征点之间的最小距离
		vector<uchar> status;	// 跟踪特征的状态，特征的流发现为1，否则为0
		vector<float> err;
	};

}
#endif // !LKOF_H_
