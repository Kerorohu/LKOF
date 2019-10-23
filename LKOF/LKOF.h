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
		
		vector<Point2f> points[2];	// point0Ϊ�������ԭ��λ�ã�point1Ϊ���������λ��
		vector<Point2f> initial;	// ��ʼ�����ٵ��λ��
		vector<Point2f> features;	// ��������
		int maxCount = 500;		// �������������
		double qLevel = 0.01;	// �������ĵȼ�
		double minDist = 10.0;	// ��������֮�����С����
		vector<uchar> status;	// ����������״̬��������������Ϊ1������Ϊ0
		vector<float> err;
	};

}
#endif // !LKOF_H_
