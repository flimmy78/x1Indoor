/*************************************************
  Copyright (C), 2006-2016, Aurine
  File name: 	storage_message.h
  Author:    	luofl
  Version:   	2.0
  Date: 		2014-11-06
  Description:	��Ϣ�洢
  
  History:                    
    1. Date:		 
       Author:		 
       Modification: 
    2. ...
*********************************************************/
#ifndef _STORAGE_MESSAGE_H_
#define _STORAGE_MESSAGE_H_

//#include "include.h"
//#include "storage_types.h"
#include "storage_include.h"
//#include "logic_include.h"
//#include "logic_timer.h"

#define MAX_MSG_NUM				10					// ��Ϣ������10��

// ���Ž��ո�ʽ
typedef struct
{
	DATE_TIME	SendTime;							// ����ʱ��
	uint8		level;								// ���� 0-һ��, 1-����, 2���ؼ�
	char		SendNo[20];							// ���ͺ���
	char		Content[200];						// ����, һ����Ź涨Ӣ��160���ַ�������70��
}REC_SHORT_MSG;

// ���ŷ��͸�ʽ
typedef struct
{
	uint8		level;								// ���� 0-һ��, 1-����, 2���ؼ�
	char		ReceiveNo[20];						// ���պ���
	char		Content[200];						// ����, һ����Ź涨Ӣ��160���ַ�������70��
}SEND_SHORT_MSG;

// ������Ϣͷ
typedef struct
{
	uint32		ID;									// ��ϢID�� 
	uint8		BulletinType;						// ���� 0-����  1��ͼƬ 2������ 3������.���� 4��ͼƬ.����
	char		title[40];							// ����
	uint32		CharLen;							// ���ֲ��ֳ���
	uint32		ImageLen;							// ͼƬ���ֳ���
	uint32		VoiceLen;							// �������ֳ���
}REC_BULLETIN_HEAD;

// ��Ϣ�ṹ��
typedef struct
{
	uint8 is_unread;								// 0 - �Ѷ���1 - δ����־	
	uint8 voice_type;								// 0x20:mp3 0x21:wav
	ZONE_DATE_TIME time;							// ��Ϣ���յ���ʱ��
	uint8 des[14];									// ִ���ߵ��������ߵ绰����
	REC_BULLETIN_HEAD Head;							// ��Ϣͷ
}MSGDATA, * PMSGDATA;

// ��Ϣ�б�
typedef struct
{
	uint8 ncount;
	MSGDATA pinfo_data[MAX_MSG_NUM];
}MSGLIST, * PMSGLIST;

/*************************************************
  Function:			storage_read_msg_voice_path
  Description: 		��ȡ��Ϣ����·��
  Input:
  	1.pmsg_data		��Ϣ�ṹ��
  Output:		
  Return:			���ֵ�Ϊ��Ϣ������,ͼƬ������ͼƬ�ļ���
  Others:
*************************************************/ 
void storage_read_msg_voice_path(MSGDATA *pmsg_data, uint8 path[50]);

/*************************************************
  Function:			storage_read_msg_voice_path
  Description: 		��ȡ��Ϣ����·��
  Input:
  	1.pmsg_data		��Ϣ�ṹ��
  Output:		
  Return:			���ֵ�Ϊ��Ϣ������,ͼƬ������ͼƬ�ļ���
  Others:
*************************************************/ 
void storage_read_msg_voice_path(MSGDATA *pmsg_data, uint8 path[50]);

/*************************************************
  Function:			storage_read_msg_data
  Description: 		��ȡ��Ϣ����
  Input:
  	1.pmsg_data		��Ϣ�ṹ��
  	2.index			��Ϣ������
  Output:		
  Return:			��Ϣ������
  Others:
*************************************************/ 
char * storage_read_msg_data(MSGDATA *pmsg_data, uint8 index);

/*************************************************
  Function:			storage_read_msg_list
  Description: 		��ȡ��Ϣ�б�
  Input:		
  Output:		
  Return:			MSGLIST	�ṹ
  Others:
*************************************************/ 
MSGLIST *storage_read_msg_list(void);

/*************************************************
  Function:			storage_write_msg
  Description: 		д����Ϣ
  Input:		
  	1.pHead			��Ϣͷ
  	2.data			����
  	3.des			ִ���ߵ��������߶��ŵĵ绰����
  Output:		   
  Return:		    
  Others:
*************************************************/
ECHO_STORAGE storage_write_msg(const REC_BULLETIN_HEAD *pHead,uint8 *data,uint8 des[14]);

/*************************************************
  Function:    		storage_delete_msg
  Description:		ɾ��ĳ����Ϣ
  Input:
  	1.index			��Ϣ����
  Output:			
  Return:			���óɹ�TRUE,ʧ��FALSE
  Others:			
*************************************************/
ECHO_STORAGE storage_delete_msg(uint8 index);

/*************************************************
  Function:			storage_clear_msg
  Description: 		�����Ϣ
  Input:		
  Output:		 
  Return:			TRUE:�ɹ�
  Others:
*************************************************/
ECHO_STORAGE storage_clear_msg (void);

/*************************************************
  Function:    		storage_set_msg_readed
  Description:		������Ϣ�Ѷ�������δ����־
  Input:
  	1.index			��Ϣ����
  Output:			
  Return:			���óɹ�TRUE,ʧ��FALSE
  Others:			
*************************************************/
ECHO_STORAGE storage_set_msg_readed(uint8 index);

/*************************************************
  Function:			storage_get_msg_state
  Description: 		��ȡ��Ϣ�Ƿ� ��δ����ʾ
  Input:		
  Output:		
  Return:			TRUE:��δ�� FALSE:��δ��
  Others:
*************************************************/
uint8 storage_get_msg_state(void);

/*************************************************
  Function:			storage_get_msg_size
  Description: 		�����Ϣ�Ĵ�С
  Input:		
  Output:		 
  Return:			TRUE:�ɹ�
  Others:
*************************************************/
int storage_get_msg_allsize(void);
#endif
