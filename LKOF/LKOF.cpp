// LKOF.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "LKOF.h"
#include <mutex>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\core\core.hpp>//OpenCV核心库头文件
#include <opencv2\highgui\highgui.hpp>//OpenCV图形处理头文件
#include <opencv2/opencv.hpp>

using namespace lk;

void LKOF::setImage(Mat imageIn) {
	datas.image = imageIn;
}

void LKOF::setPreImage(Mat preImageIn) {
	datas.image = preImageIn;
}

void LKOF::setX(int xIn) {
	std::lock_guard<std::mutex> guard(myMutex);
	x = xIn;
}

void LKOF::setY(int yIn) {
	y = yIn;
}

int LKOF::getX() {
	return x;
}

int LKOF::getY() {
	return y;
}

Mat LKOF::getImage() {
	return datas.image;
}

Mat LKOF::getPreImage() {
	return datas.preImage;
}

String LKOF::getFileName() {
	return fileName;
}

float LKOF::getRate() {
	return rate;
}

void LKOF::setFileName(String fileNameIn) {
	fileName = fileNameIn;
}

VideoCapture LKOF::getVideo() {
	return video;
}

//类初始化构造
LKOF::LKOF(String file) {

	//初始化变量
	setFileName(file);
	video.open(fileName);
	if (!video.isOpened())
		std::cout << "读取文件失败" << std::endl;

	Mat pImage;
	Mat nImage;

	video.read(pImage);
	video.read(nImage);

	setPreImage(pImage);;
	setImage(nImage);

	cirStop = true;

	rate = video.get(CAP_PROP_FPS);
	windowName = "LKOF";
}

void LKOF::getXandY(Mat &frame, Mat &output) {
	cvtColor(frame, datas.preImage, COLOR_BGR2GRAY);
	frame.copyTo(output);
	// 添加特征点
	if (addNewPoints())
	{
		goodFeaturesToTrack(datas.preImage, features, maxCount, qLevel, minDist);
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}

	if (datas.image.empty())
	{
		datas.preImage.copyTo(datas.image);
	}
	// l-k光流法运动估计
	calcOpticalFlowPyrLK(datas.image, datas.preImage, points[0], points[1], status, err);

	// 去掉一些不好的特征点
	int k = 0;
	for (size_t i = 0; i < points[1].size(); i++)
	{
		if (acceptTrackedPoint(i))
		{
			initial[k] = initial[i];
			points[1][k++] = points[1][i];
		}
	}
	points[1].resize(k);
	initial.resize(k);
	// 显示特征点和运动轨迹
	for (size_t i = 0; i < points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(255, 0, 0), -1);
	}

	// 把当前跟踪结果作为下一此参考
	swap(points[1], points[0]);
	swap(datas.image, datas.preImage);

	imshow(windowName, output);
}

bool LKOF::addNewPoints()
{
	return points[0].size() <= 10;
}

bool LKOF::acceptTrackedPoint(int i)
{
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
