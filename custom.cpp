#include "custom.h"

err_msg ergv[] = {
	{__CLOG_SUCCESS__, _T("操作成功")},
	{ __CLOG_ERR_IO__, _T("日志IO错误")},
	{ __CLOG_ERR_EX__, _T("日志等级与设置不匹配")},
	{ __CLOG_ERR_VF__, _T("写入日志时发生异常") },
	{ __CLOG_DEFAULT__, _T("日志设置为默认") },
	{ __CLOG_UNACTIVE__, _T("记录功能设置为不启用") },
	{__CLOG_ERR_CF__, _T("配置文件错误")},
	{ __CLOG_CLOSE__, _T("日志类型为0,功能被关闭") }
};

const TCHAR* GetLogErrorInfo(int code)
{
	int size = sizeof(ergv) / sizeof(err_msg);
	int i = 0;
	for (; i < size; i++)
	{
		if (ergv[i].code == code)
		{
			return ergv[i].msg;
		}
	}

	return _T("该错误信息未知");
}