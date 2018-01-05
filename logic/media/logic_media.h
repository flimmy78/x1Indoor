/*************************************************
  Copyright (C), 2006-2010, Aurine
  File name: 	logic_media.h
  Author:   	�±���
  Version:  	2.0
  Date: 		2014-12-11
  Description:  ��ý��ӿں���
				
  History:        
    1. Date:
       Author:
       Modification:
    2. ...
*************************************************/
#include "logic_media_core.h"
#include "logic_include.h"
#include "logic_video.h"
#include "logic_audio.h"

#ifndef _LOGIC_MEDIA_H_
#define _LOGIC_MEDIA_H_


typedef void (*PMEDIA_CALLBACK)(uint32 cmd, uint32 time, uint32 percent);

#ifdef _AU_PROTOCOL_
#define MEDIA_AUDIO_PORT		24020				// ��Ƶ�˿�
#define MEDIA_VIDEO_PORT		24010				// ��Ƶ�˿�
#else
#define MEDIA_AUDIO_PORT		31420				// ��Ƶ�˿�
#define MEDIA_VIDEO_PORT		31410				// ��Ƶ�˿�
#endif
#define MEDIA_VIDEOL_PORT		31430

#define AUDIO_REC_PT			PT_G711A			// ������Ƶ¼�Ƹ�ʽ(��˼)
#define VIDEO_REC_PT			PT_H264				// ������Ƶ¼�Ƹ�ʽ(��˼)

#define BYTES_PER_PACKET_SHORT 	160

typedef struct 
{
	MSMediaDesc* System;
	MSMediaDesc* VideoEnc;
	MSMediaDesc* VideoDec;
	MSMediaDesc* VideoRtpSend;
	MSMediaDesc* VideoRtpRecv;
	MSMediaDesc* AudioDec;
	MSMediaDesc* AudioAI;
	MSMediaDesc* AudioAo;	
	MSMediaDesc* AudioSfEnc;
	MSMediaDesc* AudioRtpSend;
	MSMediaDesc* AudioRtpRecv;
	MSMediaDesc* FilePlayer;
	MSMediaDesc* JpegDec;
	MSMediaDesc* JpegEnc;
	MSMediaDesc* AlawAgc;	
    MSMediaDesc* Speex; 
	MSMediaDesc* AviPlay; 
	MSMediaDesc* AviRecord; 
	MSMediaDesc* Mp3Play; 
	MSMediaDesc* RtspPlay;
	MSMediaDesc* LylyFilePlayer;
}MediaStream, * PMediaStream;

// ͷ�ļ����治���ж���
extern MediaStream mMediaStream;

// ����Ƶ�ĸ�ʽ
typedef enum
{
	/* audio & voice payload type */
	PT_PCMU = 0,
	PT_1016 = 1, 
	PT_G721 = 2,     
	PT_GSM = 3,
	PT_G723 = 4,
	PT_DVI4_8K = 5,     							// clock rate=8,000Hz, channels=1
	PT_DVI4_16K = 6,    							// clock rate=16,000Hz, channels=1 
	PT_LPC = 7,
	PT_PCMA = 8,
	PT_G722 = 9,
	PT_S16BE_STEREO = 10,     						// clock rate=44,100Hz, channels=2
	PT_S16BE_MONO = 11,       						// clock rate=44,100Hz, channels=1
	PT_QCELP = 12,
	PT_CN = 13,
	PT_MPEGAUDIO = 14,
	PT_G728 = 15,
	PT_DVI4_3 = 16,    								// clock rate=11,025Hz, channels=1
	PT_DVI4_4 = 17,    								// clock rate=22,050Hz, channels=1
	PT_G729 = 18,

	/* user-defined */
	PT_G711A    = 19,
	PT_G711U    = 20,
	PT_G726     = 21,
	PT_G729A    = 22,   							// w54130 defined
    PT_LPCM     = 23,
    PT_ILBC     = 24,   							// added by ghtao, 2007-06-21

	/* video payload type */
	PT_CelB = 25,
	PT_JPEG = 26,
	PT_CUSM = 27, 
	PT_NV = 28, 
	PT_PICW = 29, 
	PT_CPV = 30,     
	PT_H261 = 31,
	PT_MPEGVIDEO = 32,
	PT_MPEG2TS = 33,
	PT_H263 = 34,
	PT_SPEG = 35, 

	/* user-defined */
	PT_MPEG2VIDEO = 36,
	PT_AAC = 37,
	PT_WMA9STD = 38,
	PT_HEAAC = 39,
	PT_PCM_VOICE = 40,                         		// (PCM data replay), mono audio channel, low sampling rate.
	PT_PCM_AUDIO = 41,                         		// (PCM data replay), multi audio channels, high sampling rate.
	
    PT_AACLC   = 42,
    PT_MP3     = 43,
    PT_AMR      = 44,
    PT_AMRDTX   = 45, 
    PT_ADPCMA   = 49,
    PT_AEC      = 50,
    
    PT_X_LD = 95, 
	PT_H264 = 96,
	PT_D_GSM_HR = 200, 
	PT_D_GSM_EFR = 201, 
	PT_D_L8 = 202, 
	PT_D_RED = 203, 
	PT_D_VDVI = 204, 
	PT_D_BT656 = 220, 
	PT_D_H263_1998 = 221, 
	PT_D_MP1S = 222, 
	PT_D_MP2P = 223, 
	PT_D_BMPEG = 224, 
	PT_MP4VIDEO = 230,
	PT_MP4AUDIO = 237, 
	PT_VC1 = 238,
	PT_JVC_ASF = 255, 
	PT_D_AVI = 256, 
	PT_MAX = 257
}PAYLOAD_TYPE_E;

// ���ŵ���Ƶ��ʽ
typedef enum
{
	PLAY_AUDIO_TYPE_WAV,
	PLAY_AUDIO_TYPE_MP3,
	PLAY_AUDIO_TYPE_NONE
}PLAY_AUDIO_TYPE_E;

// ��Ӱ����ģʽ
typedef enum
{
	LWM_AUDIO = 0,									// ����Ƶģʽ
	LWM_AUDIO_PIC,									// ��Ƶ+ͼƬģʽ
	LWM_AUDIO_VIDEO,								// ����Ƶģʽ
	LWM_NONE										// ������
}LEAVE_WORD_MODE_E;	

typedef struct 
{
	uint32 ip;
	uint16 port;
}RTP_ADDRESS, * PRTP_ADDRESS;

// ý���ļ�ͷ�ṹ
typedef struct
{
    uint8 RecFlag;		                            // ������: bit0 ��Ƶ   bit1 ��Ƶ
    uint8 AudioFormat;	                            // ��Ƶ��ʽ
    uint8 VideoFormat;	                            // ��Ƶ��ʽ
    uint8 reserved;		                            // ����, ��0xFF
    uint32 time;		                            // ¼��ʱ��
}MEDIA_FILE_HEAD, * PMEDIA_FILE_HEAD;

typedef struct
{
    uint8 reserved;	                                // ����, ��0xFF
    uint8 flag;		                                // 0-��Ƶ, 1-��Ƶ
    uint16 size;	                           		// ����
    uint32 ts;		                                // ʱ���
}MEDIA_HEAD, * PMEDIA_HEAD;

// ����Ƶͬ����ʱ��
typedef struct
{
    uint32 current;
	uint32 redress;
	uint32 ts0;
} SYNC_TIME;

typedef struct _MEDIA_LYLY_CTRL
{
	FILE 			* FileHald;						// �ļ�ָ��
	char			FileName[50];					// �ļ���
	uint32 			FileSize;						// �ļ���С
	MEDIA_FILE_HEAD FileHead;						// �ļ�ͷ,ֻ�а���HI�ļ�ͷ���ļ�������
	uint8			* data;							// �ļ�����
	LEAVE_WORD_MODE_E mode;							// ��Ӱ�������� 1����Ƶ  2����Ƶ  3����Ƶ
	SYNC_TIME		TimeA;							// ��Ƶʱ���
	SYNC_TIME		TimeV;							// ��Ƶʱ���
	uint8			state;							// 0-���� 1-���� 2-¼��
	uint8			issave;							// 0:no 1:yes
	PMEDIA_CALLBACK callback;						// �ص�
}MEDIA_LYLY_CTRL, * PMEDIA_LYLY_CTRL;

/*************************************************
  Function:			media_stop_rtsp
  Description:		�ر�rtsp
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
int media_stop_rtsp(void);

/*************************************************
  Function:			media_start_rtsp
  Description:		����rtsp
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
//int media_start_rtsp(char *Url, void *callback_func);

/*************************************************
  Function:			media_get_v4l_addr
  Description:		
  Input:
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
void media_get_v4l_addr(uint8 **addr);

/*************************************************
  Function:			media_start_analog_video
  Description:		����ģ����ƵԤ��
  Input:
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_start_analog_video(void);

/*************************************************
  Function:			media_stop_net_video
  Description:		ֹͣģ����ƵԤ��
  Input: 			��
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_stop_analog_video(void);

/*************************************************
  Function:			media_set_analog_output_volume
  Description:		������Ƶcodec�������
  Input: 
  	vol				�����ȼ�(0���� - 8���)
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_set_analog_output_volume(uint32 vol);

/*************************************************
  Function:			media_play_lyly
  Description:		
  Input: 
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_play_lyly (char *filename, void * proc);

/*************************************************
  Function:			media_stop_lyly
  Description:		
  Input: 
  	vol				�����ȼ�
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
void media_stop_lyly (void);

/*************************************************
  Function:			media_set_output_volume_high
  Description:		������Ƶcodec�������
  Input: 
  	vol				�����ȼ�
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_set_output_volume_high(uint32 vol);

/*************************************************
  Function:			media_set_device
  Description:		�����豸����
  Input: 
  	dev				�豸����
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
void media_set_device(DEVICE_TYPE_E dev);

/*************************************************
  Function:			media_fill_audio_data
  Description:		��������Ƶ�����buf
  Input: 
  	1.data			����ָ��
  	2.len			���ݳ���
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_fill_audio_data(uint8 *data, uint32 len, uint32 time);

/*************************************************
  Function:			media_fill_video_data
  Description:		��������Ƶ�����buf
  Input: 
  	1.data			����ָ��
  	2.len			���ݳ���
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_fill_video_data(uint8 *data, uint32 len, uint32 time);

/*************************************************
  Function:			media_full_dispaly_video
  Description:		ȫ����ʾ��Ƶ
  Input: 			��
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_full_dispaly_video(DEVICE_TYPE_E devtype, uint8 flg);

/*************************************************
  Function:			media_enable_audio_aec
  Description:		ʹ���������ӿ�
  Input: 			
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
int media_enable_audio_aec(void);

/*************************************************
  Function:			media_disable_audio_aec
  Description:		ʹ���������ӿ�
  Input: 			
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
int media_disable_audio_aec(void);

// ץ��
uint32 media_snapshot(char *filename, uint32 dstW, uint32 dstH, DEVICE_TYPE_E DevType);

// ��������
uint32 media_play_sound(char *filename, uint8 IsRepeat, void * proc);

// ֹͣ����
void media_stop_sound (void);

/*************************************************
  Function:			media_start_local_record
  Description:		��������¼��
  Input: 			
  	1.filename		�ļ���
  	2.maxtime		¼�Ƶ��ʱ��
  	3.proc			�ص�
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_start_local_record(char *filename);

/*************************************************
  Function:			media_stop_local_record
  Description:		ֹͣ����¼��
  Input: 			��
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
void media_stop_local_record(void);

/*************************************************
  Function:			media_start_net_video
  Description:		����������Ƶ����
  Input: 	
  	1.addres		�Զ˵�ַ
  	2.vorect		��Ƶ���λ��
  	3.flag			��Ƶģʽ ���͡�����
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_start_net_video(uint32 address, uint8 mode);

/*************************************************
  Function:			media_stop_net_video
  Description:		ֹͣ������Ƶ����
  Input: 			��
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_stop_net_video(uint8 mode);

/*************************************************
  Function:			media_start_raw_video_file
  Description:		��������H264�������ļ�
  Input: 	
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_start_raw_video_file(char * filename);

void media_stop_raw_video_file(void);

/*************************************************
  Function:			media_start_net_audio
  Description:		����������Ƶ����
  Input: 			
  	1.tp			��Ƶ��ʽ
  	2.proc			�ص�
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_start_net_audio(int address, int len);

/*************************************************
  Function:			media_stop_net_audio
  Description:		ֹͣ������Ƶ����
  Input: 			��
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_stop_net_audio(void);

/*************************************************
  Function:			meida_start_net_hint
  Description:		����������ʾ������
  Input: 			
  	1.tp			���͵ĸ�ʽ
  	2.filename		��ʾ���ļ�
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 meida_start_net_hint(uint8 RemoteDeviceType, char *filename, void * proc);

/*************************************************
  Function:			meida_stop_net_hint
  Description:		ֹͣ��ʾ������
  Input: 			��
  Output:			��
  Return:			��
  Others:
*************************************************/
uint32 meida_stop_net_hint(void);

/*************************************************
  Function:			meida_start_net_leave_rec
  Description:		������������¼��
  Input: 			
  	1.mode			¼�Ƶ�ģʽ
  	2.atp			��Ƶ��ʽ
  	3.vtp			��Ƶ��ʽ
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 meida_start_net_leave_rec(LEAVE_WORD_MODE_E mode,
						PAYLOAD_TYPE_E atp, PAYLOAD_TYPE_E vtp, char * filename);

/*************************************************
  Function:			stop_leave_word_net
  Description:		ֹͣ¼��
  Input: 			
  	1.issave		�Ƿ񱣴�(1����, 0������)
  	2.filename		������ļ���
  Output:			��
  Return:			��
  Others:
*************************************************/
uint32 media_stop_net_leave_rec(uint8 issave);

/*************************************************
  Function:			meida_set_audio_send_addr
  Description:		������Ƶ�ķ��͵�ַ�Ͷ˿�
  Input: 			
  	1.ip			IP��ַ
  	2.port			�˿�
  Output:			��
  Return:			��
  Others:
*************************************************/
void meida_set_audio_send_addr(uint32 ip, uint16 port);

/*************************************************
  Function:			media_del_audio_send_addr
  Description:		ɾ����Ƶ�ķ��͵�ַ�Ͷ˿�
  Input: 
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_del_audio_send_addr(uint32 IP, uint16 AudioPort);

/*************************************************
  Function:    		media_add_audio_sendaddr
  Description: 		������Ƶ���͵�ַ
  Input: 			
  	1.IP			IP��ַ
  	2.AudioPort		��Ƶ�˿�
  Output:			��
  Return:			�ɹ����true/false
  Others:
*************************************************/
int32 media_add_audio_sendaddr(uint32 IP, uint16 AudioPort);

/*************************************************
  Function:			media_set_dec_enable
  Description:		����Ƶ�������
  Input: 
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_set_dec_enable(void);

/*************************************************
  Function:			media_set_dec_disable
  Description:		�ر���Ƶ�������
  Input: 
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_set_dec_disable(void);

/*************************************************
  Function:			media_set_video_send_addr
  Description:		������Ƶ�ķ��͵�ַ�Ͷ˿�
  Input: 			
  	1.ip			IP��ַ
  	2.port			�˿�
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_set_video_send_addr(uint32 ip, uint16 port);

/*************************************************
  Function:			media_del_video_send_addr
  Description:		ɾ����Ƶ�ķ��͵�ַ�Ͷ˿�
  Input: 
  Output:			��
  Return:			��
  Others:
*************************************************/
void media_del_video_send_addr(void);

/*************************************************
  Function:			media_set_output_volume
  Description:		������Ƶcodec�������
  Input: 
  	vol				�����ȼ�
  Output:			��
  Return:			�ɹ���ʧ��
  Others:
*************************************************/
uint32 media_set_output_volume(uint32 vol);

/*************************************************
  Function:			media_set_talk_volume
  Description:		����ͨ������
  Input: 
  	vol				�����ȼ�(0���� - 8���)
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_set_talk_volume(DEVICE_TYPE_E devtype, uint32 vol);

/*************************************************
  Function:			media_get_total_time
  Description:		��ȡý���ļ�����ʱ��
  Input: 			��
  Output:			��
  Return:			��ʱ�� ��λ:s
  Others:			�����Ӱ������:����Ƶģʽ�Ļ�
  					������ȡ������ȷ��ʱ��
  					��ʱû������ģʽ
*************************************************/
uint32 media_get_total_time(void);

/*************************************************
  Function:		media_clear_fb
  Description: 	���fb
  Input: 		��
  Output:		��
  Return:		��
  Others:
*************************************************/
int32 media_clear_fb(void);

/*************************************************
  Function:		init_media
  Description: 	ý���ʼ��
  Input: 		��
  Output:		��
  Return:		��
  Others:
*************************************************/
void media_init(void);

/*************************************************
  Function:		media_play_video_test
  Description: 	���Բ����ļ�
  Input: 		��
  Output:		��
  Return:		��
  Others:
*************************************************/
void media_play_video_test(void);

/*************************************************
  Function:			media_show_pict
  Description:		JPGͼƬ��ʾ
  Input: 			
  	1.filename		ͼ�񱣴���ļ���
  					���>1ʱ�ļ����Զ����ϱ��
	2.pos_x			Ŀ��ͼƬ��ʾX ����
	3.pos_y			Ŀ��ͼƬ��ʾY ����
	4.with			Ŀ��ͼƬ��ʾ����
	5.heigh			Ŀ��ͼƬ��ʾ����
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
int32 media_start_show_pict(char *filename, uint16 pos_x, uint16 pos_y, uint16 with, uint16 heigh);

/*************************************************
  Function:			media_stop_show_pict
  Description:		�ر�ͼƬ��ʾ
  Input: 			
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
void media_stop_show_pict(void);

/*************************************************
  Function:			media_pause_lyly
  Description:		��ͣ/�����л�
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
uint32 media_pause_lyly (void);

/*************************************************
  Function:			media_pause_mp3
  Description:		��ͣ/�����л�
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
void media_pause_mp3 (void);

/*************************************************
  Function:			media_play_mp3
  Description:		����MP3�ļ�
  Input: 			
  	1.filename		�ļ���
  	2.proc			�ص�
  Output:			��
  Return:			TRUE/FALSE
  Others:
*************************************************/
uint32 media_play_mp3 (char *filename, void * proc);

/*************************************************
  Function:			media_stop_lyly
  Description:		ֹͣ��Ӱ���Բ���
  Input: 			��
  Output:			��
  Return:			
  Others:
*************************************************/
void media_stop_mp3 (void);

/*************************************************
  Function:    	media_w_close
  Description: 		
  Input:		��
  Output:		��
  Return:		��
  Others:
*************************************************/
void media_w_close(void);

#endif
