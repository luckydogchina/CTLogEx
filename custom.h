#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <stdio.h>
#ifdef WIN32
#include <tchar.h>
#else 
typedef char TCHAR;
#define _T
#endif

#define __CLOG_BASE_0		0x777
#define __CLOG_DEFAULT__	(__CLOG_BASE_0 + 0) /*<Ĭ������>*/
#define __CLOG_SUCCESS__	(__CLOG_BASE_0 + 1)	/*<�����ɹ�>*/
#define __CLOG_UNACTIVE__   (__CLOG_BASE_0 + 6)/*<trace����δ����>*/
#define __CLOG_CLOSE__      (__CLOG_BASE_0 + 7)/*<��־����Ϊ0>*/
//����궨��;
#define __CLOG_ERR_EX__     (__CLOG_BASE_0 + 3) /*<�쳣����>*/
#define __CLOG_ERR_IO__		(__CLOG_BASE_0 + 2) /*<IO����>*/
#define __CLOG_ERR_VF__     (__CLOG_BASE_0 + 4) /*<����vfprintf()����>*/
#define __CLOG_ERR_CF__		(__CLOG_BASE_0 + 5) /*<�����ļ�����>*/

typedef struct err_msg
{
	int code;
	const TCHAR* msg;
}err_msg;

//const TCHAR* GetLogErrorInfo(int code);

#endif 
