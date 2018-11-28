
// AutoBackup.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "AutoBackupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoBackupApp

BEGIN_MESSAGE_MAP(CAutoBackupApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAutoBackupApp ����

CAutoBackupApp::CAutoBackupApp()
{
	// �ٽ� ���� ������ ����
//	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
	m_strSRCPath = "";	// �������
	m_strBackupPath = "";	// ������
	m_strBackupPathSrc = "";	// ������ ���� ����
	m_strRelPath = "";	// ��������
	BOOL m_bCheckAllData = FALSE;	// ��ü ���Ϲ�� ����	
	BOOL m_bCheckToday = FALSE;	// ������ ������ ������� ����

	m_strCompileSRCPath = "";	//�������
	m_strCompileDestPath = "";	//�����Ұ��
	m_CompileExceptExtensionsMap.RemoveAll();	//����Ȯ���� ����Ʈ
	m_CompileExceptFilesMap.RemoveAll();	//�������� ����Ʈ
	m_CompileListMap.RemoveAll();	//������ ��� ����Ʈ
	m_strComileDate = "";	//������ ��¥ ����

}


// ������ CAutoBackupApp ��ü�Դϴ�.

CAutoBackupApp theApp;


// CAutoBackupApp �ʱ�ȭ

BOOL CAutoBackupApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CAutoBackupDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		CString strIniFilePath = m_sAppPath + "\\Setting.ini";
		WritePrivateProfileString(_T("Start"), _T("PATH"), m_strSRCPath, strIniFilePath);
		WritePrivateProfileString(_T("End"), _T("PATH"), m_strBackupPath, strIniFilePath);
		WritePrivateProfileString(_T("Release"), _T("PATH"), m_strRelPath, strIniFilePath);

		if (m_bCheckAllData == FALSE)
			WritePrivateProfileString(_T("AllCheck"), _T("VALUE"), "0", strIniFilePath);
		else
			WritePrivateProfileString(_T("AllCheck"), _T("VALUE"), "1", strIniFilePath);

		if (m_bCheckToday == FALSE)
			WritePrivateProfileString(_T("TodayCheck"), _T("VALUE"), "0", strIniFilePath);
		else
			WritePrivateProfileString(_T("TodayCheck"), _T("VALUE"), "1", strIniFilePath);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

