#ifdef  WIN32

#ifdef CTLOGEX_EXPORTS
#define CTLOGEX_API __declspec(dllexport)
#else
#define CTLOGEX_API __declspec(dllimport)
#endif

#endif //  WIN32

#ifdef  UNIX
#define CTLOGEX_API
#endif //  UNIX



#ifndef __CTLOGEX_H__
#define __CTLOGEX_H__

#include "custom.h"

#ifndef __cplusplus
extern "C"{
#endif

/*<����XML�����ļ�;>*/
CTLOGEX_API int LoadConfig(const char* xmlfile);

/*<��ʼ��log����;>*/
CTLOGEX_API int Init();

/*<�ͷ�log��Դ;>*/
CTLOGEX_API void Release();

CTLOGEX_API int cwarn(unsigned short level, const char *format, ...);

CTLOGEX_API int ctrace(const char *format, ...);

/*<��ȡ������Ϣ>*/
CTLOGEX_API extern const TCHAR* GetLogErrorInfo(int code);

//CTLOGEX_API extern  FILE* _strace, *_swarn;;

#ifndef __cplusplus
};
#endif

#endif // !__CTLOGEX_H__




