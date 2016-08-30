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
#define __CLOG_DEFAULT__	(__CLOG_BASE_0 + 0) /*<默认设置>*/
#define __CLOG_SUCCESS__	(__CLOG_BASE_0 + 1)	/*<操作成功>*/
#define __CLOG_UNACTIVE__   (__CLOG_BASE_0 + 6)/*<trace功能未开启>*/
#define __CLOG_CLOSE__      (__CLOG_BASE_0 + 7)/*<日志类型为0>*/
//错误宏定义;
#define __CLOG_ERR_EX__     (__CLOG_BASE_0 + 3) /*<异常错误>*/
#define __CLOG_ERR_IO__		(__CLOG_BASE_0 + 2) /*<IO错误>*/
#define __CLOG_ERR_VF__     (__CLOG_BASE_0 + 4) /*<调用vfprintf()出错>*/
#define __CLOG_ERR_CF__		(__CLOG_BASE_0 + 5) /*<配置文件错误>*/

typedef struct err_msg
{
	int code;
	const TCHAR* msg;
}err_msg;

//const TCHAR* GetLogErrorInfo(int code);

#endif 
