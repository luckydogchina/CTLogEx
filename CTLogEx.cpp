// CTLogEx.cpp : ???? DLL ??¨®?????????????
//

//#include "stdafx.h"
#include "CTLogEx.h"
#include <stdarg.h>

#ifdef UNIX
//#define  _MSC_VER
#endif

#include "tinyxml2.h"
#include <sys/stat.h>


#include <fcntl.h>
#include <string.h>

#ifdef WIN32
#include <io.h>
#include <Windows.h>
//typedef void *HANDLE;
static HANDLE _htrace, _hwarn;

static int _fwarn, _ftrace;
#endif

#ifdef UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define _O_RDONLY 0x000

#endif // UNIX

using namespace tinyxml2;
/*<??????¦Ë??,?????????????,_swarn = stderr??_strace = stdout;>*/

static FILE *_strace=stdout, *_swarn=stderr;

static bool  _default = true;/*<???????????,??????????;>*/

static int   _type = 1;/*<???????,0????????,1?????????????,2???????????;>*/

static int   _level = 3; /*<??????,???????0~6????,?????0??;>*/

static bool _traceIsActive = true; /*<?????TRCE>*/

static long size_log; /*<??????§³????M???¦Ë>*/

static char _pwarn[256];

static char _ptrace[256];

/*<log????;>*/
int  cwarn(unsigned short level, const char *format, ...)
{
	int _ret;
	va_list arglist;
	char buffer[2048] = { 0 };

	if (!_default && _type == 0)
	{
		return __CLOG_CLOSE__;
	}


	//?????????????
	if (level < 0 || level > _level)
	{
		return __CLOG_ERR_EX__;
	}

	//??????????

	if (_type == 2)
	{
#ifdef WIN32
		va_start(arglist, format);
		vsprintf(buffer, format, arglist);
		_ret = write(_fwarn, buffer, strlen(buffer));
		va_end(arglist);
#endif
	}
	
	if (_type == 1)
	{
		va_start(arglist, format);
		_ret = vfprintf(_swarn, format, arglist);
		va_end(arglist);
	}
	
	if (_ret < 0)
	{
		return __CLOG_ERR_VF__;
	}

	return __CLOG_SUCCESS__;
}

int ctrace(const char *format, ...)
{
	int _ret;
	va_list arglist;
	char buffer[2048] = { 0 };

	//??????????????????????0
	if (!_default && _type == 0)
	{
		return __CLOG_CLOSE__;
	}

	//?§Ø????????????
	if (!_traceIsActive)
	{
		return __CLOG_UNACTIVE__;
	}


	if (_type == 2)
	{
#ifdef WIN32
		//?????????
		va_start(arglist, format);
		_ret = vsprintf(buffer, format, arglist);
		_ret = write(_ftrace, buffer, strlen(buffer));
		va_end(arglist);
#endif // WIN32
	}

	if (_type == 1)
	{
		//?????????
		va_start(arglist, format);
		_ret = vfprintf(_strace, format, arglist);
		//printf("%d", GetLastError());
		va_end(arglist);
	}

	if (_ret < 0)
	{
		return __CLOG_ERR_VF__;
	}

	return __CLOG_SUCCESS__;
}


/*<???¨²???>*/
#define MAX_SIZE (1024L*1024L) 
#ifdef UNIX
unsigned long getfilesize(const char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;
	if (stat(path, &statbuff) < 0){
		return filesize;
	}
	else{
		filesize = statbuff.st_size;
	}
	return filesize;
}
#endif


#ifdef WIN32
unsigned long getfilesize(const char* path)
{
	int fp;
	long len;
	fp = open(path, _O_RDONLY);
	if (fp == -1)
	{
		return -1;
	}

	len = _filelength(fp);
	close(fp);
	return len;
}
#endif // WIN32

int renamefile(const char* path)
{
	char _rename[256] = { 0 };
	char* sub = strstr((char*)path, ".log");

	if (sub == NULL)
	{
		return -1;
	}

	memcpy(_rename, path, (sub - path) / sizeof(char));
	sprintf(_rename, "%s%s%s.log", _rename,__DATE__, __TIME__);
	return rename(path, _rename);
}

void checkfile(const char* path)
{
	if (getfilesize(path) > size_log*MAX_SIZE)
	{
		if (renamefile(path) < 0)
		{
			return;
		}
	}

	return;
}

#ifdef WIN32
bool createlog(HANDLE& handle, int& fd, const char* path)
{
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;

	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	handle = CreateFile(
		path,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		&sa,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if (INVALID_HANDLE_VALUE == handle)
	{
		return false;
	}

	//0x8?????????¦Â???????, _O_APPEND ,fcntl.h;
	fd = _open_osfhandle((intptr_t)handle, _O_APPEND | _O_BINARY |_O_CREAT);

	if (fd < 0)
	{
		return false;
	}
	return true;
}
#endif // WIN32

int LoadConfig(const char* xmlfile)
{
	int i,j;
	char itoc[32] = {0};
	tinyxml2::XMLDocument     xml;
	XMLElement	*xRoot, *xNode, *xChild;
	
	if (xmlfile == NULL)
	{
		return __CLOG_ERR_CF__;
	}

	xml.LoadFile(xmlfile);
	xRoot = xml.RootElement();
	if (xRoot == NULL)
	{
		return __CLOG_ERR_CF__;
	}

	
	xNode = xRoot->FirstChildElement("default");
	if (xNode)
	{
		_default = *(xNode->GetText()) - '0';
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	xNode = xRoot->FirstChildElement("type");
	if (xNode)
	{
		_type = *(xNode->GetText()) - '0';
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	xNode = xRoot->FirstChildElement("level");
	if (xNode)
	{
		_level = *(xNode->GetText()) - '0';
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	xNode = xRoot->FirstChildElement("switch");;
	if (xNode)
	{
		_traceIsActive = *(xNode->GetText()) - '0';
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	xNode = xRoot->FirstChildElement("path");

	if (xNode)
	{
		xChild = xNode->FirstChildElement("warn");
		if (xChild)
		{
			memcpy(_pwarn, xChild->GetText(), strlen(xChild->GetText()));
		}
		else
		{
			return __CLOG_ERR_CF__;
		}

		xChild = xNode->FirstChildElement("trace");
		if (xChild)
		{
			memcpy(_ptrace, xChild->GetText(), strlen(xChild->GetText()));
		}
		else
		{
			return __CLOG_ERR_CF__;
		}
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	xNode = xRoot->FirstChildElement("size");
	if (xNode)
	{
		size_log = 0;
		
		memcpy(itoc, xNode->GetText(), strlen(xNode->GetText()));
		j = strlen(itoc);

		for (i = 0; i < j; i++)
		{
			size_log *= 10;
			size_log +=(itoc[i] - '0');
		}
	}
	else
	{
		return __CLOG_ERR_CF__;
	}

	return __CLOG_SUCCESS__;
}

int Init()
{
	if (_default)
	{
		//?????????????????,??????3????????????;
		_strace = stdout;
		_swarn = stderr;
		_type = 1;
		_level = 3;
		_traceIsActive = 0;
		return __CLOG_DEFAULT__;
	}

	switch (_type)
	{
	case 0:
	{
		return __CLOG_CLOSE__;
	}
	case 1:
	{
		_strace = stdout;
		_swarn = stderr;
	}
	break;
	case 2:
	{
#ifdef WIN32
		checkfile(_pwarn);

		createlog(_hwarn, _fwarn, _pwarn);

		if (!strcmp(_ptrace, _pwarn))
		{
			_ftrace = _fwarn;
		}
		else
		{
			checkfile(_ptrace);

			createlog(_htrace, _ftrace, _ptrace);
// WIN32
		}
#endif 
	}
	break;
	default:
		return __CLOG_ERR_CF__;
	}

	return __CLOG_SUCCESS__;
}

void Release()
{
#ifdef WIN32
	if (_fwarn > 0)
	{
		CloseHandle(_hwarn);
	}

	if (strcmp(_ptrace, _pwarn) && _ftrace > 0)
	{
		CloseHandle(_htrace);
	}
#endif // WIN32
	return;
}
