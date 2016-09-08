#include <iostream>
#include <cv.h>

#include "ImageHandler.h"
#include "MotionCalc.h"

using namespace std;

int main()
{
	//摄像头宽、高（分辨率），显示图片宽度（高度等比例缩放）
	const int CAMERA_WIDTH = 640, CAMERA_HIGHT = 480, COMPRESS_WIDTH = 400;
	int objXValue = -1, compressHight, angleMin,angleMax, xValue;
	ImageHandler imageTool;	
	Mat sourceFrame,background,foreground, compressFrame;
	compressHight = 1.0 * CAMERA_HIGHT * COMPRESS_WIDTH / CAMERA_WIDTH;

	VideoCapture capture(0);
	if (!capture.isOpened()) return 0;
	MotionCalc motionCalc(CAMERA_WIDTH);
	angleMax = motionCalc.MAX_VISION_ANGLE / 2;
	angleMin = -1 * angleMax;

	//高斯混合背景/前景分割方法
	BackgroundSubtractorMOG2 toolGaussBackground(100,16);
	bool stopFlag(false);
	while (!stopFlag)
	{
		if (!capture.read(sourceFrame))	break;
		//显示原始图像
		imshow("Source Image", sourceFrame);
		moveWindow("Source Image",0,0);
		//高斯分离前景
		toolGaussBackground(sourceFrame, foreground, -1);
		//运动目标识别
		xValue = imageTool.TrackMotionTarget(sourceFrame,foreground);
		////人脸跟踪识别
		//resize(sourceFrame,compressFrame,Size(COMPRESS_WIDTH, compressHight));
		//xValue = imageTool.RecognitionHumanFace(compressFrame);
		if(xValue >= 0 && (xValue >= objXValue + 1 || xValue <= objXValue - 1))
		{//转动不低于一度才显示
			objXValue = xValue;
			double nextAngle = motionCalc.CalcAngleByLocation(xValue);
			for(int i=angleMin;i<angleMax;i += 2)
			{
				cout << ((nextAngle + 2 >= i && nextAngle - 2 <= i) ? "|":"_");
			}
			cout<<endl;
		}

		//程序结束开关
		if (waitKey(10) == 27)
		{//监听到ESC退出
			stopFlag = true;
		}
	}
	return 0;
}