/*********************************************************
  Copyright (C), 2009-2012
  File name:	ui_msg_ctrl.c
  Author:   	caogw
  Version:   	2.0
  Date: 		2014-11-18
  Description:  ��Ϣ�ؼ�
  History:            
*********************************************************/
#include "gui_include.h"

/************************��������************************/
#define GUI_TIMER_ID			1					// ��ʱ��ID
#define TIMEOUT					2

#ifdef _TFT_7_
#define MSG_ICON_W				40
#define MSG_ICON_H				40
#define MSG_ICON_XPOS			(FORM_MSG_W-MSG_ICON_W)/2
#define MSG_ICON_YPOS			(68+(132-MSG_ICON_H)/2)
#define MSG_TEXT_LEFT			0
#define MSG_TEXT_TOP1			9
#define MSG_TEXT_TOP2			26
#define MSG_TEXT_RIGHT			FORM_MSG_W
#define MSG_TEXT_BOTTOM			68

#define QUERY_ICON_XPOS			15
#define QUERY_ICON_YPOS			(68-MSG_ICON_H)/2
#define QUERY_TEXT_LEFT			70
#define QUERY_TEXT_TOP			(68-16)/2
#define QUERY_TEXT_DISX			(FORM_MSG_W-QUERY_TEXT_LEFT)

#define QUERY_BUTTON_W			100
#define QUERY_BUTTON_H			52
#define QUERY_BUTTON_XPOS		((FORM_MSG_W-2*QUERY_BUTTON_W)/3)
#define QUERY_BUTTONON_XPOS		2*QUERY_BUTTON_XPOS + QUERY_BUTTON_W
#define QUERY_BUTTON_YPOS		(68+(132-QUERY_BUTTON_H)/2)

#define QUERY_YES_DISX			QUERY_BUTTON_W
#define QUERY_YES_LEFT1			QUERY_BUTTON_XPOS+42	// ��ʾ����ʱ������
#define QUERY_YES_TOP1			(68+(132-16)/2)
#define QUERY_NO_LEFT1			QUERY_BUTTONON_XPOS+42
#define QUERY_YES_LEFT2			QUERY_BUTTON_XPOS+42	// ��ʾӢ��ʱ������
#define QUERY_YES_TOP2			(68+(132-16)/2)
#define QUERY_NO_LEFT2			QUERY_BUTTONON_XPOS+42

#define HIT_ICON_W				72
#define HIT_ICON_H				72
#define HIT_ICON_XPOS			(FORM_MSG_W-HIT_ICON_W)/2
#define HIT_ICON_YPOS			(FORM_MSG_H-68-HIT_ICON_H)/2
#define HIT_TEXT_LEFT			0
#define HIT_TEXT_TOP			132+(68-16)/2
#define HIT_TEXT_RIGHT			FORM_MSG_W
#define HIT_TEXT_BOTTOM			FORM_MSG_H
#else
#define MSG_ICON_XPOS			93
#define MSG_ICON_YPOS			63
#define MSG_TEXT_LEFT			0
#define MSG_TEXT_TOP1			5
#define MSG_TEXT_TOP2			12
#define MSG_TEXT_RIGHT			214
#define MSG_TEXT_BOTTOM			40

#define QUERY_BUTTON_XPOS		30
#define QUERY_BUTTON_YPOS		63
#define QUERY_BUTTONON_XPOS		116
#define QUERY_ICON_XPOS			12
#define QUERY_ICON_YPOS			7
#define QUERY_TEXT_LEFT			50
#define QUERY_TEXT_TOP			12
#define QUERY_TEXT_DISX			150
#define QUERY_YES_LEFT1			55					// ��ʾ����ʱ������
#define QUERY_YES_TOP1			72
#define QUERY_YES_DISX			15
#define QUERY_NO_LEFT1			141
#define QUERY_YES_LEFT2			49					// ��ʾӢ��ʱ������
#define QUERY_YES_TOP2			71
#define QUERY_NO_LEFT2			140

#define HIT_ICON_XPOS			81
#define HIT_ICON_YPOS			12
#define HIT_TEXT_LEFT			0
#define HIT_TEXT_TOP			86
#define HIT_TEXT_RIGHT			214
#define HIT_TEXT_BOTTOM			114
#endif

#ifdef _E81S_UI_STYLE_
#define MSG_ICON_Y				44					// ͼ��Yλ��
#define MSG_ICON_X				44					// ͼ��Xλ��
#define MSG_TEXT_DIS			30
#define FORM_QUERY_W	
#define YES_ICON_W				98
#define YES_ICON_H				38		
#define YES_ICON_DIS			40
#define YES_ICON_XPOS			(FORM_QUERY_W-YES_ICON_H-2*YES_ICON_W)/2
#define YES_ICON_YPOS			136
#define NO_ICON_XPOS			(YES_ICON_XPOS+YES_ICON_W+YES_ICON_DIS)

#define ICON_W					48
#define ICON_H					48
#define HIT_TEXT_XPOS			116
#define FORM_HIT_H				100
#endif

/************************��������************************/
static HWND g_MsgWin = 0;
static MSG_INFO g_pData;
static uint8 g_RebootFlag = 0;

/************************��������************************/
CREATE_FORM(FrmMsgCtrl);

/*************************************************
  Function:		ui_reflash
  Description: 	ˢ����Ļ
  Input:	
  	1.hDlg		���ھ��
  Output:		��
  Return:		��
  Others:
*************************************************/
static void ui_reflash(HWND hDlg)
{
	InvalidateRect(hDlg, NULL, FALSE);
}

#ifdef _E81S_UI_STYLE_
/*************************************************
  Function:		draw_aurine_hit
  Description: 	��ʾ�����������硢����Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_aurine_hit(HDC hdc)
{
	RECT Textrc;
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);

	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));
	if (g_pData.TextID > 0)
	{
		if (ENGLISH == storage_get_language())
		{
			Textrc.left = HIT_TEXT_XPOS-20;
		}
		else
		{
			Textrc.left = HIT_TEXT_XPOS;
		}
		Textrc.top = (FORM_HIT_H - Font16X16)/2;
		Textrc.right = Textrc.left+200;
		Textrc.bottom = Textrc.top+Font16X16;
		DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT);
	}
}

/*************************************************
  Function:		draw_aurine_msg
  Description: 	��ʾ��Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_aurine_msg(HDC hdc)
{
	RECT Textrc;
	
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);
	DrawBmpID(hdc, MSG_ICON_X, MSG_ICON_Y, 0, 0, g_pData.MsgIcon);
	
	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));
	if (g_pData.TextID > 0)
	{	
		// ���п�����25���ַ�
		if (ENGLISH != storage_get_language())
		{
			if (strlen(get_str(g_pData.TextID)) > 25)
			{
				Textrc.left = MSG_ICON_X + ICON_W + MSG_TEXT_DIS;
                Textrc.top = MSG_ICON_Y + (ICON_H - Font16X16)/2 - 17;
                Textrc.right = (FORM_MSG_W - (MSG_ICON_X + MSG_TEXT_DIS));
                Textrc.bottom = Textrc.top + Font16X16;
                DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT|DT_WORDBREAK );
			}
			else
			{
				Textrc.left = MSG_ICON_X + ICON_W + MSG_TEXT_DIS;
                Textrc.top = MSG_ICON_Y + (ICON_H - Font16X16)/2;
                Textrc.right = (FORM_MSG_W - (MSG_ICON_X + MSG_TEXT_DIS));
                Textrc.bottom = Textrc.top + Font16X16;
                DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CENTER);            
			}
		}
		else
		{
			Textrc.left = MSG_ICON_X + ICON_W + MSG_TEXT_DIS;
			Textrc.top = MSG_ICON_Y + (ICON_H - Font16X16)/2;
			Textrc.right = MSG_TEXT_RIGHT;
			Textrc.bottom = Textrc.top + Font16X16;
			DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CENTER);
		}
	}
}

/*************************************************
  Function:		draw_aurine_query
  Description: 	��ʾ��Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:		e81sȷ����Ϣ��
*************************************************/
static void draw_aurine_query(HDC hdc)
{	
	RECT Textrc, Textrc1;
	uint32 Image1, Image2;
	
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);
	DrawBmpID(hdc, MSG_ICON_X, MSG_ICON_Y, 0, 0, g_pData.MsgIcon);
	
	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));
	if (g_pData.TextID > 0)
	{
			Textrc.left = QUERY_TEXT_LEFT+40;
			Textrc.top = QUERY_TEXT_TOP+30;
			Textrc.right = Textrc.left + QUERY_TEXT_DISX;
			Textrc.bottom = Textrc.top + Font16X16;
			DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CALCRECT);
			DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT);
	}
	
	Image1 = BID_QueryButton;
	Image2 = BID_QueryButton;
	switch (g_pData.Select)
	{
		case 0:
			Image1 = BID_QueryButtonON;
			break;

		case 1:
			Image2 = BID_QueryButtonON;
			break;

		default:
			break;
	}
	DrawBmpID(hdc, QUERY_BUTTON_XPOS, QUERY_BUTTON_YPOS+20, 0, 0, Image1);	
    DrawBmpID(hdc, QUERY_BUTTONON_XPOS, QUERY_BUTTON_YPOS+20, 0, 0, Image2);

	Textrc.left = QUERY_YES_LEFT1;
	Textrc.top = QUERY_YES_TOP1+20;
	Textrc.right = Textrc.left + QUERY_YES_DISX;
	Textrc.bottom = Textrc.top + Font16X16;

	Textrc1.left = QUERY_NO_LEFT1;
	Textrc1.top = QUERY_YES_TOP1+20;
	Textrc1.right = Textrc1.left + QUERY_YES_DISX;
	Textrc1.bottom = Textrc1.top + Font16X16;

    if(0 == g_pData.Select)
    {
        SetTextColor(hdc, COLOR_BLACK);
    }
    else
    {
        SetTextColor(hdc, COLOR_WHITE);
    }
	DrawText(hdc, get_str(SID_Msg_Yes), -1, &Textrc, DT_CALCRECT|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	DrawText(hdc, get_str(SID_Msg_Yes), -1, &Textrc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
    if(1 == g_pData.Select)
    {
        SetTextColor(hdc, COLOR_BLACK);
    }
    else
    {
        SetTextColor(hdc, COLOR_WHITE);
    }
	DrawText(hdc, get_str(SID_Msg_No), -1, &Textrc1, DT_CALCRECT|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	DrawText(hdc, get_str(SID_Msg_No), -1, &Textrc1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
#endif

/*************************************************
  Function:		draw_hit
  Description: 	��ʾ�����������硢����Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_hit(HDC hdc)
{
	RECT Textrc;
	
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);
	DrawBmpID(hdc, HIT_ICON_XPOS, HIT_ICON_YPOS, 0, 0, g_pData.MsgIcon);
	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));

	if (g_pData.TextID > 0)
	{
		Textrc.left = HIT_TEXT_LEFT;
		Textrc.top = HIT_TEXT_TOP;
		Textrc.right = HIT_TEXT_RIGHT;
		Textrc.bottom = HIT_TEXT_BOTTOM;
		DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CENTER);
	}
}

/*************************************************
  Function:		draw_msg
  Description: 	��ʾ��Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_msg(HDC hdc)
{
	RECT Textrc;
	
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);
	DrawBmpID(hdc, MSG_ICON_XPOS, MSG_ICON_YPOS, 0, 0, g_pData.MsgIcon);
	
	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));
	if (g_pData.TextID > 0)
	{	
		// ���п�����25���ַ�
		if (ENGLISH != storage_get_language())
		{
			if (strlen(get_str(g_pData.TextID)) > 25)
			{
				Textrc.left = MSG_TEXT_LEFT;
				Textrc.top = MSG_TEXT_TOP1;
				Textrc.right = MSG_TEXT_RIGHT;
				Textrc.bottom = MSG_TEXT_BOTTOM;
				DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT|DT_WORDBREAK );
			}
			else
			{
				Textrc.left = MSG_TEXT_LEFT;
				Textrc.top = MSG_TEXT_TOP2;
				Textrc.right = MSG_TEXT_RIGHT;
				Textrc.bottom = MSG_TEXT_BOTTOM;
				DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CENTER);
			}
		}
		else
		{
			#ifndef _TFT_7_
			if (strlen(get_str(g_pData.TextID)) > 28)
			{
				Textrc.left = MSG_TEXT_LEFT;
				Textrc.top = MSG_TEXT_TOP1;
				Textrc.right = MSG_TEXT_RIGHT;
				Textrc.bottom = MSG_TEXT_BOTTOM;
				DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT|DT_WORDBREAK );
			}
			else
			#endif
			{
				Textrc.left = MSG_TEXT_LEFT;
				Textrc.top = MSG_TEXT_TOP2;
				Textrc.right = MSG_TEXT_RIGHT;
				Textrc.bottom = MSG_TEXT_BOTTOM;
				DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CENTER);
			}
		}
	}
}

/*************************************************
  Function:		draw_query
  Description: 	��ʾ��Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_query(HDC hdc)
{	
	RECT Textrc, Textrc1;
	uint32 Image1, Image2;
	
	DrawBmpID(hdc, 0, 0, 0, 0, g_pData.MsgBk);
	DrawBmpID(hdc, QUERY_ICON_XPOS, QUERY_ICON_YPOS, 0, 0, g_pData.MsgIcon);
	
	SetTextColor(hdc, COLOR_WHITE);
	SelectFont(hdc, GetBoldFont(FONT_16));
	if (g_pData.TextID > 0)
	{
		Textrc.left = QUERY_TEXT_LEFT;
		Textrc.top = QUERY_TEXT_TOP;
		Textrc.right = Textrc.left + QUERY_TEXT_DISX;
		Textrc.bottom = Textrc.top + Font16X16;
		DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_CALCRECT);
		DrawText(hdc, get_str(g_pData.TextID), -1, &Textrc, DT_LEFT);
	}
	
	Image1 = BID_QueryButton;
	Image2 = BID_QueryButton;
	switch (g_pData.Select)
	{
		case 0:
			Image1 = BID_QueryButtonON;
			break;

		case 1:
			Image2 = BID_QueryButtonON;
			break;

		default:
			break;
	}
	DrawBmpID(hdc, QUERY_BUTTON_XPOS, QUERY_BUTTON_YPOS, 0, 0, Image1);
	DrawBmpID(hdc, QUERY_BUTTONON_XPOS, QUERY_BUTTON_YPOS, 0, 0, Image2);
	
	if (ENGLISH != storage_get_language())
	{
		Textrc.left = QUERY_YES_LEFT1;
		Textrc.top = QUERY_YES_TOP1;
		Textrc.right = Textrc.left + QUERY_YES_DISX;
		Textrc.bottom = Textrc.top + Font16X16;

		Textrc1.left = QUERY_NO_LEFT1;
		Textrc1.top = QUERY_YES_TOP1;
		Textrc1.right = Textrc1.left + QUERY_YES_DISX;
		Textrc1.bottom = Textrc1.top + Font16X16;
	}
	else
	{
		Textrc.left = QUERY_YES_LEFT2;
		Textrc.top = QUERY_YES_TOP2;
		Textrc.right = Textrc.left + QUERY_YES_DISX;
		Textrc.bottom = Textrc.top + Font16X16;

		Textrc1.left = QUERY_NO_LEFT2;
		Textrc1.top = QUERY_YES_TOP2;
		Textrc1.right = Textrc1.left + QUERY_YES_DISX;
		Textrc1.bottom = Textrc1.top + Font16X16;
	}
	
	DrawText(hdc, get_str(SID_Msg_Yes), -1, &Textrc, DT_CALCRECT|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	DrawText(hdc, get_str(SID_Msg_Yes), -1, &Textrc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	DrawText(hdc, get_str(SID_Msg_No), -1, &Textrc1, DT_CALCRECT|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	DrawText(hdc, get_str(SID_Msg_No), -1, &Textrc1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

#if 0
/*************************************************
  Function:		draw_ts
  Description: 	У׼��ʾ��Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_ts(HDC hdc)
{	
}
/*************************************************
  Function:		draw_new_pass
  Description: 	�����
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
void draw_new_pass(HDC hdc)
{
}

/*************************************************
  Function:		draw_jd
  Description: 	�ҵ��ַ��
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
void draw_jd(HDC hdc)
{
}

/*************************************************
  Function:		draw_jd_control
  Description: 	�ҵ����
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
void draw_jd_control(HDC hdc)
{
}

/*************************************************
  Function:		draw_jd_control
  Description: 	�ҵ����
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
void draw_aurine_jd_control(HDC hdc)
{

}

/*************************************************
  Function:		draw_jd_control
  Description: 	�ҵ����
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void draw_aurine_jd_window_control(HDC hdc)
{
}

/*************************************************
  Function:		draw_jd_control
  Description: 	�ҵ����
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
void draw_aurine_jd_mode_control(HDC hdc)
{

}
#endif

/*************************************************
  Function:		ui_msgctrl_paint
  Description: 	��ť������Ϣ
  Input:		�� 		
  Output:		��
  Return:		��
  Others:
*************************************************/
static void ui_msgctrl_paint(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
	
   	HDC hdc = BeginPaint(hDlg);
	GetClientRect(hDlg, &rect);
	SetBkMode(hdc, BM_TRANSPARENT);
	switch (g_pData.Mode)
	{
		case MSG_INFORMATION:						// ��Ϣ
		case MSG_WARNING:							// ����
		case MSG_ERROR:								// ����
		case MSG_RIGHT:
		case MSG_HIT:
			#ifdef _E81S_UI_STYLE_
			draw_aurine_msg(hdc);
			#else	
			draw_msg(hdc);
			#endif
			break;

		case MSG_QUERY:								// ȷ��
			#ifdef _E81S_UI_STYLE_
			draw_aurine_query(hdc);
			#else	
			draw_query(hdc);
			#endif
			break;

		case MSG_CALL_MESSAGE:						// �����硢����Ϣ���¾���
		case MSG_MESSAGE:					
		case MSG_ALARM:								
			#ifdef _E81S_UI_STYLE_
			draw_aurine_hit(hdc);
			#else
			draw_hit(hdc);
			#endif
			break;

		case MSG_IPCODE:	
		case MSG_PASS:								// �����
			break;

		case MSG_NEW_PASS:							// �����
			break;
			
		case MSG_TS:								// У׼��ʾ
			break;

		case MSG_JDADDR:
			break;

		case MSG_JD_TJ:								// �ҵ����
			break;

	    case MSG_AURINE_JD_TJ:
	        break;

	    case MSG_AURINE_JD_MODE:
	        break;

		default:
			break;
	}
	EndPaint(hDlg, hdc);
}

/*************************************************
  Function:		msg_tick_proc
  Description: 	��ʱ
  Input:		
  	1.hDlg      ���ھ��
  	2.wParam
  	3.lParam
  Output:		��
  Return:		TRUE �� FALSE ��
  Others:		
*************************************************/
static void msg_tick_proc(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//KillTimer(hDlg, GUI_TIMER_ID);
	form_close(&FrmMsgCtrl);
	if (g_RebootFlag)
	{
		g_RebootFlag = 0;
		hw_stop_feet_dog();
	}
}

/*************************************************
  Function:		KeyCommand
  Description: 	�ؼ��¼���������
  Input: 		
	1.id		���صĿؼ�ID
	2.hWnd		�ؼ����
	3.hDlg		���
  Output:		��
  Return:		��
  Others:
*************************************************/
static void KeyCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch ((uint32)wParam)
	{
		case SCANCODE_F1:
			break;

		case SCANCODE_F2:
			break;
			
		case SCANCODE_F3:
			sys_key_beep();
			if (g_pData.Mode == MSG_QUERY)
			{
				if (g_pData.Select)
				{
					g_pData.Select = 0;
				}
				else
				{
					g_pData.Select = 1;
				}
				ui_reflash(hDlg);
			}
			SetScreenTimer();
			break;
			
		case SCANCODE_F4:
			sys_key_beep();
			if (g_pData.Mode == MSG_QUERY)
			{
				form_close(&FrmMsgCtrl);
				if (g_pData.Select)
				{
					SendMessage(g_pData.parent, MSG_COMMAND, g_pData.ID, MSG_EVENT_NO);
				}
				else
				{
					SendMessage(g_pData.parent, MSG_COMMAND, g_pData.ID, MSG_EVENT_YES);
				}
				SendMessage(g_pData.parent,	WM_Change_RightKey, g_pData.ID, 0);
			}
			SetScreenTimer();
			break;
		
		case SCANCODE_F5:
			sys_key_beep();
			if (g_pData.Mode == MSG_QUERY)
			{
				SendMessage(g_pData.parent,	WM_Change_RightKey, g_pData.ID, 0);
				form_close(&FrmMsgCtrl);
			}
			SetScreenTimer();
			break;
				
		default:
			break;
	}
}

/*************************************************
  Function:		WindowProc
  Description: 	��Ϣ��������
  Input: 		
  	1.hDlg		���
  	2.message	��Ϣ
  	3.wParam	����1
  	4.lParam	����2
  Output:		��
  Return:		��
  Others:
*************************************************/
static int WindowProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case MSG_CREATE:
			g_MsgWin = hDlg;
			break;
		
		case MSG_INITDIALOG:
			SetWindowBkColor(hDlg, PAGE_BK_COLOR);
			break;
			
		case MSG_ACTIVE:
			break;

		case MSG_SHOWWINDOW:
			if (wParam == SW_SHOWNORMAL)
			{
				if (g_pData.Mode != MSG_QUERY)
				{
					if (g_pData.ID != IDC_SEARCH_LIST)
					{
						SetTimer(hDlg, GUI_TIMER_ID, TIMEOUT*50);
					}
				}
			}
			else if (wParam == SW_HIDE)
			{
				if (g_pData.Mode == MSG_QUERY)
				{
					SendMessage(g_pData.parent,	WM_Change_RightKey, g_pData.ID, 0);
				}
				else
				{
					KillTimer(hDlg, GUI_TIMER_ID);
				}
				form_close(&FrmMsgCtrl);
			}
			break;
			
		case MSG_PAINT:
			ui_msgctrl_paint(hDlg, wParam, lParam);
			return 0;
			
       	#ifdef _ENABLE_TOUCH_
		case MSG_LBUTTONDOWN:
    		get_key_down(hDlg, LOWORD(lParam), HIWORD(lParam));
   			break;
   			
	    case MSG_LBUTTONUP:
	        get_key_up(hDlg, LOWORD(lParam), HIWORD(lParam));
	        break;
        #endif
		
	    case MSG_KEYDOWN:
        	break;

		case MSG_KEYUP:
			KeyCommand(hDlg, wParam, lParam);
			break;
			
		case MSG_COMMAND:
			break;
			
		case MSG_TIMER:	
			msg_tick_proc(hDlg, wParam, lParam);
			break;

		case WM_MSG_Close:
			//KillTimer(hDlg, GUI_TIMER_ID);
			if (g_pData.Mode == MSG_QUERY)
			{
				SendMessage(g_pData.parent,	WM_Change_RightKey, g_pData.ID, 0);
			}
			form_close(&FrmMsgCtrl);
			break;
		
		case MSG_CLOSE:
			DestroyMainWindow(hDlg);
			PostQuitMessage(hDlg);
			return 0;
		
		case MSG_DESTROY:
			if (hDlg)
			{
				KillTimer(hDlg, GUI_TIMER_ID);
			}
			return 0;
	}
	
	return DefaultMsgProc(self, hDlg, message, wParam, lParam);
}

/*************************************************
  Function:		ui_msg_win
  Description: 	��Ϣ�����
  Input:			
  	1.parten	������
  	2.style		��Ϣ���
  Output:		��
  Return:		��	
  Others:		
*************************************************/
void ui_msg_win(PMSG_INFO info)
{
	memset(&g_pData, 0, sizeof(MSG_INFO));
	memcpy(&g_pData, info, sizeof(MSG_INFO));
	//form_show(&FrmMsgCtrl);
	SendMessage(FrmMain.hWnd, WM_FORM_SHOW, 0, (PGUI_FORM)&FrmMsgCtrl);

	if (g_pData.ID == IDC_SEARCH_LIST)
	{
		ui_msgctrl_paint(g_MsgWin, 0, 0);
		usleep(500*1000);
		form_close(&FrmMsgCtrl);
	}
}

/*************************************************
  Function:		ui_msg_reboot
  Description: 	��Ϣ��ʧ������
  Input:		��
  Output:		��
  Return:		��	
  Others:		
*************************************************/
void ui_msg_reboot(void)
{
	g_RebootFlag = 1;
}
