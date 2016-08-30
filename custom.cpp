#include "custom.h"

err_msg ergv[] = {
	{__CLOG_SUCCESS__, _T("�����ɹ�")},
	{ __CLOG_ERR_IO__, _T("��־IO����")},
	{ __CLOG_ERR_EX__, _T("��־�ȼ������ò�ƥ��")},
	{ __CLOG_ERR_VF__, _T("д����־ʱ�����쳣") },
	{ __CLOG_DEFAULT__, _T("��־����ΪĬ��") },
	{ __CLOG_UNACTIVE__, _T("��¼��������Ϊ������") },
	{__CLOG_ERR_CF__, _T("�����ļ�����")},
	{ __CLOG_CLOSE__, _T("��־����Ϊ0,���ܱ��ر�") }
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

	return _T("�ô�����Ϣδ֪");
}