#ifndef _MEND_DEFINES_H_
#define _MEND_DEFINES_H_

// �ű��ļ���Ԫ�����Գ���
#define SCRIPTSTAGEELENAME 32
#define SCRIPTSTAGEELEPATH 100
#define SCRIPTSTAGEPATH 100

// �ű��﷨���ֳ���
#define SCRIPTGRAMANAME 20

#ifdef _UNICODE
// �ű��﷨�ļ���
#define SCRIPTGRAMEFILE L"G:/git/OurGame/OurDream/2D��Ϸ/2D���ɽ�1��Ϸ/�ĵ�/ScriptGrama.txt"
// ��ʼ�ű�·������
#define SCRIPTFILEPATH L""
#else
#define SCRIPTGRAMEFILE "G:/git/OurGame/OurDream/2D��Ϸ/2D���ɽ�1��Ϸ/�ĵ�/ScriptGrama.txt"
// ��ʼ�ű�·������
#define SCRIPTFILEPATH ""
#endif



// ��ʼ���ڴ����ģ��ʱ������ڴ��С����λMB
#define MEMORYSIZE  100	

#define _MEND_DEBUG_

#endif