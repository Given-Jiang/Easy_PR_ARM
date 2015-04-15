/*
 * test.c
 *
 *  Created on: 2015��3��28��
 *      Author: Given_Jiang
 */

#include <stdio.h>
#include <string.h>

//MiniGUI
#include <common.h>
#include <minigui.h>
#include <gdi.h>
#include <window.h>
#include <mywindows.h>
#include <control.h>


//EasyPR
#include "include/plate_recognize.h"
#include "include/util.h"
#include "include/features.h"
#include "include/CParser.h"

//ʱ�����
#include "time.h"
#include <sys/time.h>

#define IDC_CTRL0 0x000
#define IDC_CTRLx 0x020
#define IDC_CTRL1 0x001
#define IDC_CTRL2 0x002
#define IDC_CTRL3 0x003
#define IDC_CTRL4 0x004
#define IDC_CTRL5 0x005
#define IDC_CTRL10  0x010
#define IDC_CTRL11  0x001
#define IDC_CTRL12  0x002
#define IDC_CTRL13  0x003
#define IDC_CTRL14  0x004
#define ID_TIMER_1	20

#define IDM_ABOUT_THIS 103
#define IDM_104 104

static char text1 [32];
static char text2 [32];
static char text3 [32];
static char text4 [32];
static char text5 [32];
static char text6 [32];
static RECT msg1 = {220, 130, 320, 180};
static RECT msg2 = {560, 130, 660, 180};
static RECT msg3 = {220, 480, 320, 550};
static RECT msg4 = {460, 480, 660, 550};
static RECT msg5 = {345, 550, 660, 600};
static RECT msg6 = {780, 100, 900, 200};
static BITMAP logo_bmp,title_bmp,version_bmp;//minigui��ͼ��ṹ

struct timeval tstart,tend;//��������ʱ�����
float timeuse;

uint32_t clock_x = 0;
uint32_t clock_y = 0;

//�˵����Գ�������

uint32_t plate_index = 0;


//PR���Ժ���
int test_plate_locate(int plate_choose);
int test_chars_segment(int plate_choose);
string test_chars_recognise(int plate_choose);
string test_plate_recognize(int plate_choose);

//ʱ���������
int gettimeofday (struct timeval *tp, struct timezone *tzp);

static void make_title_text (void)
{
	sprintf (text1, "����ͼ��");
    sprintf (text2, "���ͼ��");
	sprintf (text3, "��ɫ��λ���");
    sprintf (text4, "����Sobel��λ���");
    sprintf (text5, "�ַ��ָ���");
    sprintf (text6, "��ǰ���Գ��ƣ�");
}

static const char* daxia [] =
{
    "��ߴ���Գ���",
    "�������Գ���",
    "ҹ����Գ���",
    "��бУ�����Գ���",

};

static void daxia_notif_proc (HWND hWnd, int id, int nc, DWORD add_data)
{
	uint32_t menu_index;
	menu_index = 0;
	menu_index = SendMessage (hWnd, MBM_GETCURITEM, 0, 0);
	switch (menu_index)
	{
		case 0:
			plate_index = 0;
			break;
		case 1:
			plate_index = 1;
			break;
		case 2:
			plate_index = 2;
			break;
		case 3:
			plate_index = 3;
			break;
		default:
			plate_index = 0;
			break;
	}
}

static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    int id;
    switch (message) {
        case MSG_CREATE:
        	LoadBitmap(HDC_SCREEN,&logo_bmp,"logo.bmp");//����logoͼƬ
        	LoadBitmap(HDC_SCREEN,&title_bmp,"title.bmp");//����titleͼƬ
        	LoadBitmap(HDC_SCREEN,&version_bmp,"version.bmp");//����authͼƬ
            make_title_text ();//������Ƶ���ڱ���

            CreateWindow(CTRL_STATIC,"������ͼ�񼰴�����",WS_VISIBLE|SS_CENTER|WS_BORDER,IDC_CTRL0,90,100,670,310,hWnd,0);
            CreateWindow(CTRL_STATIC,"�ֲ�������",WS_VISIBLE|SS_CENTER|WS_BORDER,IDC_CTRL0,90,420,670,310,hWnd,0);
            CreateWindow(CTRL_BUTTON,"�����ť����ȥ��������UI��������",BS_CHECKED|WS_VISIBLE|WS_GROUP|BS_AUTORADIOBUTTON|BS_LEFT,IDC_CTRLx,1920,100,230,30,hWnd,0);
//            CreateWindow(CTRL_BUTTON,"����ͼƬ��",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|BS_LEFT,IDC_CTRL2,780,130,230,30,hWnd,0);
//            CreateWindow(CTRL_BUTTON,"����ͼƬ��",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|BS_LEFT,IDC_CTRL3,780,160,230,30,hWnd,0);
            CreateWindow(CTRL_BUTTON,"���ƶ�λ&�ж�",WS_VISIBLE|BS_AUTORADIOBUTTON,IDC_CTRL1,100,445,120,30,hWnd,0);
            CreateWindow(CTRL_BUTTON,"�ַ��ָ�",WS_VISIBLE|BS_AUTORADIOBUTTON,IDC_CTRL2,220,445,85,30,hWnd,0);
            CreateWindow(CTRL_BUTTON,"����ȫ��",WS_VISIBLE|BS_AUTORADIOBUTTON,IDC_CTRL3,390,445,85,30,hWnd,0);
            CreateWindow(CTRL_BUTTON,"�ַ�ʶ��",WS_VISIBLE|BS_AUTORADIOBUTTON,IDC_CTRL4,305,445,85,30,hWnd,0);
            CreateWindow(CTRL_STATIC,"��Ϣ��ʾ",WS_VISIBLE|WS_BORDER|SS_LEFT|WS_CAPTION,IDC_CTRL10,780,420,230,250,hWnd,0);

            CreateWindow(CTRL_MENUBUTTON,"��ѡ�����ͼƬ",WS_CHILD | WS_VISIBLE,IDC_CTRL5,780,120,230,30,hWnd,0);

            SetDlgItemText(hWnd,IDC_CTRL10,"");

            SetTimerEx(hWnd, ID_TIMER_1,5,NULL);

            break;
        case MSG_PAINT:
            hdc = BeginPaint (hWnd);
            FillBoxWithBitmap(hdc,30,20,0,0,&logo_bmp);//��ʾlogo
            FillBoxWithBitmap(hdc,150,20,0,0,&title_bmp);//��ʾtitle
            FillBoxWithBitmap(hdc,850,700,0,0,&version_bmp);//��ʾversion
            DrawText (hdc, text1, -1, &msg1, DT_LEFT | DT_WORDBREAK);//��ʾ��������Ƶ��
            DrawText (hdc, text2, -1, &msg2, DT_LEFT | DT_WORDBREAK);//��ʾ�������Ƶ��
            DrawText (hdc, text3, -1, &msg3, DT_LEFT | DT_WORDBREAK);//��ʾ������ͼ��
            DrawText (hdc, text4, -1, &msg4, DT_LEFT | DT_WORDBREAK);//��ʾ��ͼ�������
            DrawText (hdc, text5, -1, &msg5, DT_LEFT | DT_WORDBREAK);//��ʾ��ͼ�������
            DrawText (hdc, text6, -1, &msg6, DT_LEFT | DT_WORDBREAK);//��ʾ��ͼ�������
            EndPaint (hWnd, hdc);
            return 0;

        case MSG_DESTROY:
        	DestroyAllControls(hWnd);//�ر����пؼ�
        	return(0);
        case MSG_CLOSE:
            KillTimer(hWnd,ID_TIMER_1);
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
        case MSG_TIMER:
        	{
        	int timer_id= (int)wParam;
        	DWORD tick_count=(DWORD)lParam;
        	clock_x=clock_x+2;clock_y++;
        	}
        	break;

        case MSG_COMMAND:
        	id=LOWORD(wParam);
        	switch(id)
        	{
        	case 1:
        		PostMessage(hWnd,MSG_USER,0x0,0x01);//Ͷ���û�������Ϣ
        		break;
        	 case 2:
        	    PostMessage(hWnd,MSG_USER,0x0,0x02);//Ͷ���û�������Ϣ
        	    break;
        	 case 3:
        		PostMessage(hWnd,MSG_USER,0x0,0x03);//Ͷ���û�������Ϣ
        		break;
        	 case 4:
        		PostMessage(hWnd,MSG_USER,0x0,0x04);//Ͷ���û�������Ϣ
        		break;
         	case 5:
         		PostMessage(hWnd,MSG_USER,0x0,0x05);//Ͷ���û�������Ϣ
         		break;
        	 default:
        		 break;
        	}
        	break;
       	case MSG_USER://�Զ�����Ϣ����
        	        	switch(lParam)
        	        	        	{case 1:
        	        	        	{
        	        	        		gettimeofday(&tstart, NULL);//��������ʱ�俪ʼ
        	        	        		test_plate_locate(plate_index);
        	        	        		gettimeofday(&tend, NULL);//��������
        	        	        		timeuse=(tend.tv_sec-tstart.tv_sec);
        	        	        		char str_local[90];
        	        	        		switch(plate_index)
        	        	        		{
        	        	        			case 0:  memcpy(str_local, "����ͼ��: BGR,1920x1078\n��ǰ�㷨:���ƶ�λ&�ж�\n��ɫ��λ+����Sobel+SVM�ж�\n����ʱ�䣺", 85);
        	        	        			break;
        	        	        			case 1: memcpy(str_local, "����ͼ��: BGR,614x333\n��ǰ�㷨:���ƶ�λ&�ж�\n��ɫ��λ+����Sobel+SVM�ж�\n����ʱ�䣺", 85);
        	        	        			break;
        	        	        			case 2: memcpy(str_local, "����ͼ��: BGR,800x332\n��ǰ�㷨:���ƶ�λ&�ж�\n��ɫ��λ+����Sobel+SVM�ж�\n����ʱ�䣺", 85);
        	        	        			break;
        	        	        			case 3: memcpy(str_local, "����ͼ��: BGR,720x576\n��ǰ�㷨:���ƶ�λ&�ж�\n��ɫ��λ+����Sobel+SVM�ж�\n����ʱ�䣺", 85);
        	        	        			break;
        	        	        		}
        	        	        		char stime_local[8];
        	        	        		sprintf(stime_local, "%d", (uint32_t)timeuse);//������ʱ��תΪ�ַ���
        	        	        		strcat(str_local, stime_local);//�ϲ��ַ���
        	        	        		strcat(str_local, " s");
        	        	        		SetDlgItemText(hWnd, IDC_CTRL10, str_local);
        	        	        		break;
        	        	        	}
        	        	        	 case 2:
        	        	        	 {
        	        	        		gettimeofday(&tstart, NULL);//��������ʱ�俪ʼ
        	        	        		test_chars_segment(plate_index);
        	        	        		gettimeofday(&tend, NULL);//��������
        	        	        		timeuse=1000000*(tend.tv_sec-tstart.tv_sec)+(tend.tv_usec-tstart.tv_usec); //����Ϊ΢��
        	        	        		char str_seg[90]="����ͼ��: BGR,136x36\n��ǰ�㷨:�ַ��ָ�\n����ʱ�䣺";
        	        	        		char stime_seg[8];
        	        	        		sprintf(stime_seg, "%d", (uint32_t)timeuse);//������ʱ��תΪ�ַ���
        	        	        		strcat(str_seg, stime_seg);//�ϲ��ַ���
        	        	        		strcat(str_seg, " uS");
        	        	        		SetDlgItemText(hWnd, IDC_CTRL10, str_seg);
        	        	        	    break;
        	        	        	 }
        	        	        	 case 3:
        	        	        	 {
        	        	        		 gettimeofday(&tstart, NULL);//��������ʱ�俪ʼ
        	        	        		 string result_all = test_plate_recognize(plate_index);
        	        	        		 gettimeofday(&tend, NULL);//��������
        	        	        		 char result_PRall[60];
        	        	        		 strcpy(result_PRall, result_all.c_str());
        	        	        		 timeuse = (tend.tv_sec-tstart.tv_sec); //����Ϊ΢��
        	        	        		 char str_all[120]="����ͼ��: BGR,1920x1078\n��ǰ�㷨:����ȫ��\nʶ������\n";
           	        	        		 strcat(str_all, result_PRall);//�ϲ��ַ���
           	        	        		 strcat(str_all, "\n����ʱ��:");//�ϲ��ַ���
             	        	        	 char stime_all[8];
             	        	        	 sprintf(stime_all, "%d", (uint32_t)timeuse);//������ʱ��תΪ�ַ���
             	        	        	 strcat(str_all, stime_all);//�ϲ��ַ���
             	        	        	 strcat(str_all, " s");
            	        	        	 SetDlgItemText(hWnd, IDC_CTRL10, str_all);
        	        	        	 }
        	        	        	 break;
        	        	        	 case 4:
        	        	        	 {
        	        	        		 gettimeofday(&tstart, NULL);//��������ʱ�俪ʼ
        	        	        		 string result_PR = test_chars_recognise(plate_index);
        	        	        		 gettimeofday(&tend, NULL);//��������
        	        	        		 char result_PRText[10];
        	        	        		 strcpy(result_PRText, result_PR.c_str());
        	        	        		 timeuse=1000000*(tend.tv_sec-tstart.tv_sec)+(tend.tv_usec-tstart.tv_usec); //����Ϊ΢��
        	        	        		 char str_reg[90]="����ͼ��: BGR,136x36\n��ǰ�㷨:�ַ�ʶ��\nʶ������";
        	        	        		 strcat(str_reg, result_PRText);//�ϲ��ַ���
        	        	        		 strcat(str_reg, "\n����ʱ��:");//�ϲ��ַ���
         	        	        		 char stime_reg[8];
         	        	        		 sprintf(stime_reg, "%d", (uint32_t)timeuse);//������ʱ��תΪ�ַ���
         	        	        		 strcat(str_reg, stime_reg);//�ϲ��ַ���
         	        	        		 strcat(str_reg, " uS");
        	        	        		 SetDlgItemText(hWnd, IDC_CTRL10, str_reg);
        	        	        	 }
        	        	        		break;

        	        	        	 case 5:
        	        	        	 {
        	        	        		 int i;
        	        	        		 for (i = 0; i < 4; i++)
        	        	        		 {
        	        	        			 MENUBUTTONITEM mbi;
        	        	        			 mbi.text = daxia[i];
        	        	        			 mbi.bmp = NULL;
        	        	        			 mbi.data = 0;
        	        	        		 SendDlgItemMessage(hWnd, IDC_CTRL5, MBM_ADDITEM, -1, (LPARAM)&mbi);
        	        	        		 }
        	        	        		SetNotificationCallback (GetDlgItem (hWnd, IDC_CTRL5), daxia_notif_proc);
        	        	             	SendDlgItemMessage(hWnd, IDC_CTRL5, MBM_SETCURITEM, 0, 0);
        	        	        		 break;
        	        	        	 }
        	        	        	 case 6:

        	        	        		 break;
        	        	        	 case 7:
        	        	        	     break;
        	        	        	 default:break;
        	        	        	}
        	        	break;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;
#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "helloworld" , 0 , 0);
#endif

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "����DSP�ĳ���ʶ��ϵͳ�������ʵ��";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = g_rcScr.right;
    CreateInfo.by = g_rcScr.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindow (&CreateInfo);

    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);

    return 0;
}
#ifndef _LITE_VERSION
#include <dti.c>
#endif
