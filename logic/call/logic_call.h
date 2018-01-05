/*************************************************
  Copyright (C), 2006-2016, Aurine
  File name:  	logic_call.h
  Author:     	chenbh
  Version:    	2.0
  Date: 		2014-12-11
  Description:  �����߼�ͷ�ļ�
  
  History:        
    1. Date:
       Author:
       Modification:
    2. ...
*************************************************/
#ifndef _LOGIC_CALL_H_
#define _LOGIC_CALL_H_


// �Խ�ҳ��GUI�ص�����
typedef void (*PFGuiNotify)(uint32 param1, uint32 param2);
extern void request_callno_addr_callbak(uint32 param1, uint32 param2);
extern void callout_state_callbak(uint32 param1, uint32 param2);

#define MANAGER_COUNTS_MAX		8					// ������������
extern uint32 g_Manager_IP[];
extern uint32 g_Manager_Index[];

// �Խ�����
typedef enum
{
	INTER_CALLOUT_E, 								// ����
	INTER_CALLIN_E,									// ����
	INTER_MONITOR_E									// ����
}INTER_OPER_TYPE;

typedef enum
{
	END_BY_OTHER_SIDE,								// �Է��Ҷ�
	END_BY_USER_HANDDOW,							// ���عҶ�
	END_BY_CALL_BUSY, 								// �Է�æ
	END_BY_CALL_TIMEOUT, 							// ����/ͨ��/����¼�Ƴ�ʱ
	END_BY_COMM_TIMEOUT,							// ������ʱ
	END_BY_REQUESET_ERR,							// ���Ӵ���, ��������IP
	END_BY_SELF_ERR									// ��������
}CALL_END_TYPE_E;

typedef enum
{
	CALL_STATE_NONE,		  						// ��
	CALL_STATE_CALLING,								// ������
	CALL_STATE_RECORDHINT,							// ����ģʽ��ʾ��
	CALL_STATE_RECORDING,							// ����ģʽ¼��
	CALL_STATE_TALK,								// ͨ��״̬
	CALL_STATE_END,									// ͨ������
	CALL_STATE_REQUEST,								// ������
	CALL_NEW_CALLING,								// ������
	CALL_FORMSHOW_CALLING,							// ��ʾ���д���
	CALL_STATE_MOVETEMP								// ��ʱת����
}CALL_STATE_E;

#define CALL_TIMER		(CALL_STATE_END+10) 		// �Խ���ʱ

typedef struct
{
	uint8 InterType;
	uint8 DevType;
	char DevStr[30];
}INTER_INFO_S, *PINTER_INFO_S;

struct ThreadInfo
{
	uint8 running;
	pthread_t thread;	
	int (*exit)(struct ThreadInfo *thread);
	void *private;
};

/*************************************************
  Function:			StartThread
  Description:		
  Input:	
  Output:
  Return:
  Others:
*************************************************/
int inter_start_thread(struct ThreadInfo* thread, void* proc, void* param, int ID);

/*************************************************
  Function:				inter_call_resident
  Description:			����ס��
  Input: 	
  	1.mode				0 ���� 1 ����
  	2.InPutNo			�������
  Output:				��
  Return:				0 �ɹ�
  Others:
*************************************************/
int32 inter_call_resident(int32 mode, char * InPutNo);

/*************************************************
  Function:				inter_call_sub_terminal
  Description:			���зֻ�
  Input: 	
  	1.InPutNo			�������
  Output:				��
  Return:				0 �ɹ�
  Others:
*************************************************/
int32 inter_call_sub_terminal(char *InputNo);

/*************************************************
  Function:				inter_call_manager
  Description:			���й���Ա��
  Input: 	
  	1.InPutNo			�������
  Output:				��
  Return:				0 �ɹ�
  Others:
*************************************************/
int32 inter_call_manager(char *InputNo);

/*************************************************
  Function:				inter_answer_call
  Description:			���н���
  Input: 			
  	1.VideoSendrecv		��Ƶ
  Output:				��
  Return:				�ɹ���� TRUE/FALSE
  Others:	
*************************************************/
int32 inter_answer_call(int32 * VideoSendrecv);

/*************************************************
  Function:			inter_hand_down
  Description:		�Ҷ�
  Input: 			��
  Output:			��
  Return:			�ɹ���� TRUE/FALSE
  Others:
*************************************************/
void inter_hand_down(void);

/*************************************************
  Function:			phone_hand_down
  Description:		�ſڹҶ�����
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
void phone_hand_down(void);

/*************************************************
  Function:				phone_call_in
  Description:			ģ����ǰ������
  Input: 	
  	1.index				��ǰ������ 1��2
  Output:				��
  Return:				0 �ɹ�
  Others:
*************************************************/
int32 phone_call_in(uint8 index);

/*************************************************
  Function:				inter_call_ini
  Description:			�Խ���ʼ��
  Input: 	
  	1.CallGuiNotify		����GUI�ص�����
  	2.BeCallGuiNotify	����GUI�ص�����
  Output:				��
  Return:				
  Others:
*************************************************/
void inter_call_ini(PFGuiNotify CallGuiNotify, PFGuiNotify BeCallGuiNotify);

/*************************************************
  Function:			inter_video_snap
  Description:		ץ��
  Input: 	
  Output:			��
  Return:			�ɹ����, TRUE/FALSE
  Others:	
*************************************************/
int32 inter_video_snap(void);

#ifdef _OTHER_ELEVATOR_
/*************************************************
  Function:		other_dianti_set_cmd
  Description:	������������������ݿ�����
  Input:
  	cmd			����ֵ
  	callno		���к���
  Output:		��
  Return:		TRUE/FALSE
  Others:		01-���� 02-���� 03-�ٻ����ݵ�һ¥,Ȼ��
  				���е���¥	
*************************************************/
int32 other_dianti_send_cmd(uint8 cmd);
#endif

/*************************************************
  Function:			inter_call_distribute
  Description:		�Խ������෢�Ͱ����������
  Input: 	
  	1.recPacket		���հ�
  Output:			��
  Return:			�ɹ����, TRUE/FALSE
  Others:	
*************************************************/
int32 inter_call_distribute(const PRECIVE_PACKET recPacket);

/*************************************************
  Function:			inter_call_responsion
  Description:		�Խ�������Ӧ������������
  Input: 	
  	1.recPacket		Ӧ���
  	2.SendPacket	���Ͱ�
  Output:			��
  Return:			��
  Others:
*************************************************/
void inter_call_responsion(const PRECIVE_PACKET recPacket, const PSEND_PACKET SendPacket);

/*************************************************
  Function:			get_callout_type
  Description: 		��ȡ��������
  Output:			��
  Return:			
  Others:		
*************************************************/
uint8 get_callout_type(void);

/*************************************************
  Function:			inter_unlock
  Description:		���ڻ�����
  Input: 			��
  Output:			��
  Return:			TRUE / FALSE
  Others:
*************************************************/
int32 inter_unlock(void);

/*************************************************
  Function:			call_out
  Description:		��ʼ����,���в����������ٵ��øú��������߳�
  Input: 	
  Output:			��
  Return:			��
  Others:
*************************************************/
int32 call_out(void);
#endif
