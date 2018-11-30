
// AutoBackup.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAutoBackupApp:
// �� Ŭ������ ������ ���ؼ��� AutoBackup.cpp�� �����Ͻʽÿ�.
//

class CAutoBackupApp : public CWinApp
{
public:
	CAutoBackupApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
public:
	
	CString	m_sAppPath;		// ���� ���� ���
	CString m_strSRCPath;	// �������
	CString m_strBackupPath;	// ������
	CString m_strBackupPathSrc;	// ������ ���� ����
	CString m_strRelPath;	// ��������
	BOOL m_bCheckAllData;	// ��ü ���Ϲ�� ����	
	BOOL m_bCheckToday;	// ������ ������ ������� ����
	//���� ���� ����
	CEdit m_EditState;	// ����Ʈ ��Ʈ��
	CProgressCtrl m_ProgressCtrl;	// ���α׷��� ǥ��
	


	//������ ���� ����
	CString m_strCompileSRCPath;	//�������
	CString m_strCompileDestPath;	//�����Ұ��
	CMapStringToString m_CompileExceptExtensionsMap;	//����Ȯ���� ����Ʈ
	CMapStringToString m_CompileExceptFilesMap;	//�������� ����Ʈ
	CMapStringToString m_CompileListMap;	//������ ��� ����Ʈ
	CString m_strComileDate;	//������ ��¥ ����

	//������ ����
	//üũ�ڽ� �� ����
	CString m_strSKDFileCopyExecYN;
	CString m_strSKDCompileExecYN;
	CString m_strSKDBatchExecYN;
	//�� ����
	int m_strSKDFileCopyMinute;
	int m_strSKDCompileMinute;
	int m_strSKDBatchMinute;
	//�ð� ����
	CString m_strSKDFileCopyTime;
	CString m_strSKDCompileTime;

	//timer
	int m_SystemTimerID;
	int m_FilecopyTimerID;
	int m_CompileTimerID;
	int m_BatchTimerID;

	//ƽ �����
	long  m_nSKDFileCopyExecIdleTime;
	long  m_nSKDCompileExecIdleTime;
	long  m_nSKDBatchExecIdleTime;
	

	DECLARE_MESSAGE_MAP()
};

extern CAutoBackupApp theApp;