
// AutoBackup.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CAutoBackupApp 생성

CAutoBackupApp::CAutoBackupApp()
{
	// 다시 시작 관리자 지원
//	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_strSRCPath = "";	// 원본경로
	m_strBackupPath = "";	// 백업경로
	m_strBackupPathSrc = "";	// 백업경로 원본 저장
	m_strRelPath = "";	// 릴리즈경로
	BOOL m_bCheckAllData = FALSE;	// 전체 파일백업 여부	
	BOOL m_bCheckToday = FALSE;	// 오늘자 생성및 릴리즈복사 여부

/****************************************************************************/

	//컴파일 복사 설정
	m_strCompileSRCPath = "";	//원본경로
	m_strCompileDestPath = "";	//복사할경로
	m_CompileExceptExtensionsMap.RemoveAll();	//예외확장자 리스트
	m_CompileExceptFilesMap.RemoveAll();	//예외파일 리스트
	m_CompileListMap.RemoveAll();	//컴파일 대상 리스트
	m_CompileCheckListMap.RemoveAll();	//컴파일 적용 리스트
	m_strComileDate = "";	//컴파일 날짜 설정

	//스케쥴 설정
	//체크박스 값 저장
	m_strSKDFileCopyExecYN= "";
	m_strSKDCompileExecYN= "";
	m_strSKDBatchExecYN= "";
	//분 저장
	m_strSKDFileCopyMinute=0;
	m_strSKDCompileMinute= 0;
	m_strSKDBatchMinute = 0;
	//시간 저장
	m_strSKDFileCopyTime= "";
	m_strSKDCompileTime= "";

	//timer
	m_SystemTimerID = 0;
	m_FilecopyTimerID = 0;
	m_CompileTimerID = 0;
	m_BatchTimerID = 0;

}


// 유일한 CAutoBackupApp 개체입니다.

CAutoBackupApp theApp;


// CAutoBackupApp 초기화

BOOL CAutoBackupApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CAutoBackupDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
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
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

