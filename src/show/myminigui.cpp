/*
 * myminigui.cpp
 *
 *  Created on: 2015年3月30日
 *      Author: Given_Jiang
 */

#include <common.h>
#include <minigui.h>
#include <gdi.h>
#include <window.h>
#include <mywindows.h>
#include <control.h>

#include "../include/plate_locate.h"
#include "../include/plate_judge.h"
#include "../include/chars_segment.h"
#include "../include/chars_identify.h"

#include "../include/plate_detect.h"
#include "../include/chars_recognise.h"

#include "../include/plate_recognize.h"

#include "../include/myminigui.h"

//MiniGUI显示彩色图像

void dispimage(Mat &image, int px, int py)
{
int nl = image.rows;
	int nc = image.cols * image.channels();
	for(int j=0; j<nl ;++j)
	{
		uchar *data = image.ptr<uchar>(j);
		for(int i=0; i<nc; i=i+3)
		{
			SetPixelRGB(HDC_SCREEN,((i/3)+px),j+py,data[i+2],data[i+1],data[i]);

		}

	}
}
