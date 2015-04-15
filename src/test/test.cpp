#include "../include/plate_locate.h"
#include "../include/plate_judge.h"
#include "../include/chars_segment.h"
#include "../include/chars_identify.h"

#include "../include/plate_detect.h"
#include "../include/chars_recognise.h"

#include "../include/plate_recognize.h"

#include "../include/myminigui.h"

using namespace easypr;

int test_plate_locate();
int test_plate_judge();
int test_chars_segment();
int test_chars_identify();
int test_plate_detect();
string test_chars_recognise();
string test_plate_recognize();
int testMain();

//MiniGUI��ʾ����

void dispimage(Mat &image, int px, int py);


//����Ҫ���Ե�ͼƬ��ַд������
const string test_img = "";


const string testOption[] = 
	{
		"1. test plate_locate(���ƶ�λ);"		/* ���ƶ�λ */,
		"2. test plate_judge(�����ж�);"		/* �����ж� */,  
		"3. test plate_detect(���Ƽ��);"		/* ���Ƽ�⣨�������ƶ�λ�복���жϣ� */, 
		"4. test chars_segment(�ַ��ָ�);"		/* �ַ��ָ� */, 
		"5. test chars_identify(�ַ�����);"		/* �ַ����� */,  
		"6. test chars_recognise(�ַ�ʶ��);"		/* �ַ�ʶ�𣨰����ַ��ָ����ַ����� */,
		"7. test plate_recognize(����ʶ��);"		/* ����ʶ�� */, 
		"8. test all(����ȫ��);"		/* ����ȫ�� */,
		"9. ����;"		/* �˳� */,
	};

const int testOptionCount = 9;

int testMain()
{
	bool isExit = false;
	while (isExit != true)
	{
		stringstream selectOption(stringstream::in | stringstream::out);
		selectOption << "EasyPR Test:"<< endl;
		for(int i = 0; i < testOptionCount; i++)
		{
			selectOption << testOption[i] << endl;
		}

		cout << "////////////////////////////////////"<< endl;
		cout << selectOption.str();
		cout << "////////////////////////////////////"<< endl;
		cout << "��ѡ��һ�����:";

		int select = -1;
		bool isRepeat = true;
		while (isRepeat)
		{
			cin >> select;
			isRepeat = false;
			switch (select)
			{
			case 1:
//				assert (test_plate_locate() == 0);
				break;
			case 2:
				assert (test_plate_judge() == 0);
				break;
			case 3:
				assert (test_plate_detect() == 0);
				break;
			case 4:
//				assert (test_chars_segment() == 0);
				break;
			case 5:
				assert (test_chars_identify() == 0);
				break;
			case 6:
//				assert (test_chars_recognise() == 0);
				break;
			case 7:
//				assert (test_plate_recognize() == 0);
				break;
			case 8:
//				assert (test_plate_locate() == 0);
				assert (test_plate_judge() == 0);
				assert (test_plate_detect() == 0);

//				assert (test_chars_segment() == 0);
				assert (test_chars_identify() == 0);
//				assert (test_chars_recognise() == 0);

//				assert (test_plate_recognize() == 0);
				break;
			case 9:
				isExit = true;
				break;
			default:
				cout << "�����������������:";
				isRepeat = true;
				break;
			}
		}
	}

	return 0;
}


int test_plate_locate(int plate_choose)
{
//	cout << "test_plate_locate" << endl;
	string str;
	switch(plate_choose)
	{
	case 0:
		str = "image/test.jpg";
		break;
	case 1:
		str = "image/test2.jpg";
		break;
	case 2:
		str = "image/test3.jpg";
		break;
	case 3:
		str = "image/test4.jpg";
		break;
	default:
		str = "image/test.jpg";
		break;
	}
	Mat src = imread(str);

	Mat srcshow ;
	//����ͼƬ�ߴ緽����ʾ
	resize(src,srcshow,Size(320,240),0,0,CV_INTER_LINEAR);
	dispimage(srcshow,100,180);

	//�������Զ�λ����Ϊ��ȼ�⺯��
	vector<Mat> resultVec;
	CPlateDetect local;

	int result = local.plateDetectDeep(src, resultVec, 1, 0);
	if (result == 0)
	{
		int num = resultVec.size();
		if(plate_choose == 2)
		{
			Mat resultMat = resultVec[0];
			dispimage(resultMat, 200+(1*262), 522);
		}else{
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			dispimage(resultMat, 200+(j*262), 522);
		}
		}
	}

	return result;
}

int test_plate_judge()
{
	cout << "test_plate_judge" << endl;

	Mat src = imread("image/plate_judge.jpg");

	//�����ǳ��Ƶ�ͼ�鼯��
	vector<Mat> matVec;

	//����SVM�жϺ�õ���ͼ�鼯��
	vector<Mat> resultVec;

	CPlateLocate lo;
	lo.setDebug(1);
	lo.setLifemode(true);

	int resultLo = lo.plateLocate(src, matVec);

	if (0 != resultLo)
		return -1;

	cout << "plate_locate_img" << endl;
	if (resultLo == 0)
	{
		int num = matVec.size();
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = matVec[j];
			imshow("plate_judge", resultMat);
			waitKey(0);
		}
        destroyWindow("plate_judge");
	}

	CPlateJudge ju;
	int resultJu = ju.plateJudge(matVec, resultVec);

	if (0 != resultJu)
		return -1;

	cout << "plate_judge_img" << endl;
	if (resultJu == 0)
	{
		int num = resultVec.size();
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			imshow("plate_judge", resultMat);
			waitKey(0);
		}
        destroyWindow("plate_judge");
	}

	return resultJu;
}

int test_chars_segment(int plate_choose)
{
//	cout << "test_chars_segment" << endl;
	string str;
	switch(plate_choose)
	{
	case 0:
		str = "image/new_location.jpg";
		break;
	case 1:
		str = "image/new_location2.jpg";
		break;
	case 2:
		str = "image/new_location3.jpg";
		break;
	case 3:
		str = "image/new_location4.jpg";
		break;
	default:
		str = "image/new_location.jpg";
		break;
	}

	Mat src = imread(str);

	vector<Mat> resultVec;
	CCharsSegment plate;
	Mat srcshow ;

	int result = plate.charsSegment(src, resultVec);
	if (result == 0)
	{
		int num = resultVec.size();
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			int nc = resultMat.cols;
			int nl = resultMat.rows;
//			cout << "cols= " << nc << "\nrows= " << nl << endl;
			//����ͼƬ�ߴ緽����ʾ
			resize(resultMat, srcshow, Size(60, 60), 0, 0, CV_INTER_LINEAR);
			dispimage(srcshow, 295+j*30, 592);
//			imshow("chars_segment", resultMat);
//			waitKey(0);
		}
//        destroyWindow("chars_segment");
	}

	return result;
}

int test_chars_identify()
{
	cout << "test_chars_identify" << endl;

	Mat src = imread("image/chars_identify.jpg");

	vector<Mat> resultVec;
	CCharsSegment cs;
	CCharsIdentify ci;

	string plateIdentify = "";

	int result = cs.charsSegment(src, resultVec);
	if (result == 0)
	{
		int num = resultVec.size();
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			bool isChinses = false;

			//Ĭ���׸��ַ����������ַ�
			if (j == 0)
				isChinses = true;

			string charcater = ci.charsIdentify(resultMat, isChinses);
			plateIdentify = plateIdentify + charcater;
		}
	}

	const string plateLicense = "��E771H6";

	cout << "plateLicense: " << plateLicense << endl;
	cout << "plateIdentify: " << plateIdentify << endl;

	if (plateLicense != plateIdentify)
	{
		cout << "Identify Not Correct!" << endl;
		return -1;
	}
	cout << "Identify Correct!" << endl;

	return result;
}


int test_plate_detect()
{
	cout << "test_plate_detect" << endl;

	//Mat src = imread("image/plate_detect.jpg");
	Mat src = imread("image/baidu_image/test1.jpg");

	vector<Mat> resultVec;
	CPlateDetect pd;
	pd.setPDLifemode(true);

	int result = pd.plateDetect(src, resultVec);
	if (result == 0)
	{
		int num = resultVec.size();
		for (int j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			imshow("plate_detect", resultMat);
			waitKey(0);
		}
        destroyWindow("plate_detect");
	}

	return result;
}


string test_chars_recognise(int plate_choose)
{
//	cout << "test_chars_recognise" << endl;

	string str;
	switch(plate_choose)
	{
	case 0:
		str = "image/new_location.jpg";
		break;
	case 1:
		str = "image/new_location2.jpg";
		break;
	case 2:
		str = "image/new_location3.jpg";
		break;
	case 3:
		str = "image/new_location4.jpg";
		break;
	default:
		str = "image/new_location.jpg";
		break;
	}

	Mat src = imread(str);

	CCharsRecognise cr;
	string charsRecognise = "";

	int result = cr.charsRecognise(src, charsRecognise);
	if (result == 0)
	{
//		cout << "charsRecognise: " << charsRecognise << endl;
	}

	return charsRecognise;
}

string test_plate_recognize(int plate_choose)
{
//	cout << "test_plate_recognize" << endl;

	string str;
	switch(plate_choose)
	{
	case 0:
		str = "image/test.jpg";
		break;
	case 1:
		str = "image/test2.jpg";
		break;
	case 2:
		str = "image/test3.jpg";
		break;
	case 3:
		str = "image/test4.jpg";
		break;
	default:
		str = "image/test.jpg";
		break;
	}
	Mat src = imread(str);

	Mat srcshow ;

	//����ͼƬ�ߴ緽����ʾ
	resize(src,srcshow,Size(320,240),0,0,CV_INTER_LINEAR);

	dispimage(srcshow,100,180);

	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	pr.setLifemode(true);
	pr.setDebug(true);

	vector<string> plateVec;

	string PR_result;

	int result_last = pr.plateRecognize(src, plateVec);
	if (result_last == 0)
	{
		int num = plateVec.size();
		if (num == 2)
		{
			PR_result = "��ɫ��λ: " + plateVec[0] + "\n" + "����Sobel��λ: " + plateVec[1];
//			cout << "plateRecognize: " << plateVec[j] << endl;
		}else
		{
			PR_result = "��ɫ��λ" + plateVec[0];
		}
	}

//	if (result_last != 0)
//		cout << "result:" << result << endl;

	return PR_result;
}
