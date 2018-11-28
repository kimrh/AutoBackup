
// AutoBackupDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "AutoBackupDlg.h"
#include "FileCopysetDlg.h"
#include "CompileSetDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoBackupDlg 대화 상자



CAutoBackupDlg::CAutoBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoBackupDlg::IDD, pParent)
	, m_strSRCPath(_T(""))
	, m_strBackupPath(_T(""))
	, m_strRelPath(_T(""))
	, m_bCheckAllData(FALSE)
	, m_bCheckToday(FALSE)
	, m_strEditstate(_T(""))
	, m_CompileDate(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRCPATH, m_strSRCPath);
	DDX_Text(pDX, IDC_EDIT_BACKUPPATH, m_strBackupPath);
	DDX_Text(pDX, IDC_EDIT_RELPATH, m_strRelPath);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_EditState);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	DDX_Check(pDX, IDC_CHECK_ALLDATA, m_bCheckAllData);
	DDX_Check(pDX, IDC_CHECK_TODAY, m_bCheckToday);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strEditstate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_CompileDate);
	DDX_Control(pDX, IDC_EDIT_RELPATH, m_EditCtrlRelPath);
}

BEGIN_MESSAGE_MAP(CAutoBackupDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(CUSTOM_UPDATEDATA, ForCustomMessageFromThread)
	ON_BN_CLICKED(IDC_BUTTON_SRC, &CAutoBackupDlg::OnBnClickedButtonSrc)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CAutoBackupDlg::OnBnClickedButtonBackup)
	ON_BN_CLICKED(IDC_BUTTON_REL, &CAutoBackupDlg::OnBnClickedButtonRel)
	ON_BN_CLICKED(IDC_BUTTON_AUTOBACKUP, &CAutoBackupDlg::OnBnClickedButtonAutobackup)
	ON_BN_CLICKED(IDC_CHECK_TODAY, &CAutoBackupDlg::OnBnClickedCheckToday)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CAutoBackupDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDOK, &CAutoBackupDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAutoBackupDlg::OnBnClickedCancel)
	ON_EN_UPDATE(IDC_EDIT_RELPATH, &CAutoBackupDlg::OnEnUpdateEditRelpath)
	ON_BN_CLICKED(IDC_FILECOPYSEETBTN, &CAutoBackupDlg::OnBnClickedFilecopyseetbtn)
	ON_BN_CLICKED(IDC_COMPILESETBTN, &CAutoBackupDlg::OnBnClickedCompilesetbtn)
END_MESSAGE_MAP()


// CAutoBackupDlg 메시지 처리기

BOOL CAutoBackupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	//krh
	pThreadDlg = NULL;
	m_strCompileDate = "";
	m_strStartFileDlgMap.RemoveAll();

	char szPath[MAX_PATH];
	::GetModuleFileName(AfxGetInstanceHandle(), szPath, MAX_PATH);
	*strrchr(szPath, '\\') = '\0';
	theApp.m_sAppPath = szPath;

	CString strDebugIniFileName;
	strDebugIniFileName = theApp.m_sAppPath + _T("\\Setting.ini");

	char	szBuffer[600];
	memset(szBuffer, 0, 600);
	GetPrivateProfileString("Start", "PATH", "", szBuffer, 600, strDebugIniFileName);
	m_strSRCPath = szBuffer;

	memset(szBuffer, 0, 600);
	GetPrivateProfileString("End", "PATH", "", szBuffer, 600, strDebugIniFileName);
	m_strBackupPath = szBuffer;

	memset(szBuffer, 0, 600);
	GetPrivateProfileString("Release", "PATH", "", szBuffer, 600, strDebugIniFileName);
	m_strRelPath = szBuffer;


	int nVal = GetPrivateProfileInt("AllCheck", "VALUE", 0, strDebugIniFileName);
	if (nVal == 0)
	{
		theApp.m_bCheckAllData = FALSE;
		m_bCheckAllData = FALSE;

	}
	else
	{
		theApp.m_bCheckAllData = TRUE;
		m_bCheckAllData = TRUE;

	}


	nVal = GetPrivateProfileInt("TodayCheck", "VALUE", 0, strDebugIniFileName);
	//20160131 기능 일시 블록
/*	if (nVal == 0)
	{
		theApp.m_bCheckToday = FALSE;
		m_bCheckToday = FALSE;
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(FALSE);

	}
	else
	{
		theApp.m_bCheckToday = TRUE;
		m_bCheckToday = TRUE;
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
	}
	
*/
	theApp.m_strSRCPath = m_strSRCPath;
	theApp.m_strBackupPath = m_strBackupPath;
	theApp.m_strRelPath = m_strRelPath;

	GetDlgItem(IDC_EDIT_SRCPATH)->SetWindowText(m_strSRCPath);
	GetDlgItem(IDC_EDIT_BACKUPPATH)->SetWindowText(m_strBackupPath);
	GetDlgItem(IDC_EDIT_RELPATH)->SetWindowText(m_strRelPath);

	pfir = (CAutoBackupDlg *)AfxGetApp()->m_pMainWnd;

	m_ProgressCtrl.SetRange(0, 30000);
	m_ProgressCtrl.SetPos(0);

	UpdateData(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAutoBackupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAutoBackupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAutoBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CAutoBackupDlg::ForCustomMessageFromThread(WPARAM wParam, LPARAM lParam)
{
	BOOL bChk = IsDlgButtonChecked(IDC_CHECK_ALLDATA);
	if (bChk == FALSE)
	{

		m_bCheckAllData = FALSE;
		theApp.m_bCheckAllData = FALSE;
	}
	else
	{
		m_bCheckAllData = TRUE;
		theApp.m_bCheckAllData = TRUE;
	}
	BOOL bToayChk = IsDlgButtonChecked(IDC_CHECK_TODAY);
	if (bToayChk == FALSE)
	{
		m_bCheckToday = FALSE;
		theApp.m_bCheckToday = FALSE;
	}
	else
	{
		m_bCheckToday = TRUE;
		theApp.m_bCheckToday = TRUE;
	}
	m_ProgressCtrl.SetPos(nFilecount);

	UpdateData(FALSE);
	m_EditState.LineScroll(m_EditState.GetLineCount());
	return 0;
}

void CAutoBackupDlg::OnBnClickedButtonSrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(FALSE);
		BROWSEINFO bInfo;
		bInfo.hwndOwner = GetSafeHwnd();
		bInfo.pidlRoot = NULL;
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
		memset(&bInfo, 0, sizeof(bInfo));

		LPITEMIDLIST path;
		path = SHBrowseForFolder(&bInfo);

		TCHAR szpathName[300];
		SHGetPathFromIDList(path, szpathName);
		CString strtmp = szpathName;
		if (strtmp != "")
			theApp.m_strSRCPath = szpathName;

		GetDlgItem(IDC_EDIT_SRCPATH)->SetWindowText(theApp.m_strSRCPath);
		m_strSRCPath = theApp.m_strSRCPath;
		GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("경로가 잘못되었습니다 다시 선택하세요."));
		theApp.m_strSRCPath = "";
		UpdateData(FALSE);
	}
}


void CAutoBackupDlg::OnBnClickedButtonBackup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(FALSE);
		BROWSEINFO bInfo;
		bInfo.hwndOwner = GetSafeHwnd();
		bInfo.pidlRoot = NULL;
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
		memset(&bInfo, 0, sizeof(bInfo));

		LPITEMIDLIST path;
		path = SHBrowseForFolder(&bInfo);

		TCHAR szpathName[300];
		SHGetPathFromIDList(path, szpathName);

		CString strtmp = szpathName;
		if (strtmp != "")
			theApp.m_strBackupPath = szpathName;

		GetDlgItem(IDC_EDIT_BACKUPPATH)->SetWindowText(theApp.m_strBackupPath);
		m_strBackupPath = theApp.m_strBackupPath;
		GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("경로가 잘못되었습니다 다시 선택하세요."));
		theApp.m_strBackupPath = "";
		UpdateData(FALSE);
	}
}


void CAutoBackupDlg::OnBnClickedButtonRel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
		BROWSEINFO bInfo;
		bInfo.hwndOwner = GetSafeHwnd();
		bInfo.pidlRoot = NULL;
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
		memset(&bInfo, 0, sizeof(bInfo));

		LPITEMIDLIST path;
		path = SHBrowseForFolder(&bInfo);

		TCHAR szpathName[300];
		SHGetPathFromIDList(path, szpathName);

		CString strtmp = szpathName;
		if (strtmp != "")
			theApp.m_strRelPath = szpathName;

		GetDlgItem(IDC_EDIT_RELPATH)->SetWindowText(theApp.m_strRelPath);
		m_strRelPath = theApp.m_strRelPath;
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("경로가 잘못되었습니다 다시 선택하세요."));
		theApp.m_strRelPath = "";
		UpdateData(FALSE);
	}
}


void CAutoBackupDlg::OnBnClickedButtonAutobackup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	오늘자 백업 선택 시
	1. 백업 경로에 오늘자 폴더 생성
	2. 릴리즈 경로에서 백업 경로의 오늘자 폴더에 복사
	3. 원본경로에서 백업 경로의 오늘자 폴더에 복사

	오늘자 백업 미선택 시
	2,3 작업 수행
	*/
	UpdateData(TRUE);

	m_strEditstate = "";
	BOOL bChk = IsDlgButtonChecked(IDC_CHECK_TODAY);
	GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(FALSE);
	
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SRCPATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_BACKUPPATH)->EnableWindow(FALSE);

	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);

	//20160131 수정본 START
	if (m_strSRCPath.Compare(m_strBackupPath) == 0 || m_strSRCPath.Compare(m_strRelPath) == 0 || m_strRelPath.Compare(m_strBackupPath) == 0 )
	{
		AfxMessageBox("중복되는 경로가 있습니다. 경로 재설정 바랍니다.");
		GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SRCPATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACKUPPATH)->EnableWindow(FALSE);

		return;
	}
	if (m_strRelPath != ""  && m_strSRCPath != "" && m_strBackupPath != "")
	{
		pThreadDlg = AfxBeginThread(ThreadSimple, this);

		if (pThreadDlg == NULL)
		{
			GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);

			GetDlgItem(IDOK)->EnableWindow(TRUE);

			GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);

			GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SRCPATH)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_BACKUPPATH)->EnableWindow(FALSE);
			return;
		}


		CloseHandle(pThreadDlg->m_hThread);
		pThreadDlg->m_hThread = NULL;



	}
	else
		AfxMessageBox("소스,백업,릴리즈 경로 입력하세요");

	//20160131 수정본 <-END

	/*
	if (bChk == TRUE)
	{
		if (m_strRelPath != ""  && m_strSRCPath != "" && m_strBackupPath != "")
		{
			theApp.m_bCheckToday = bChk;
			pThreadDlg = AfxBeginThread(ThreadMakeTodayData, this);

			if (pThreadDlg == NULL)
			{
				GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);

				GetDlgItem(IDOK)->EnableWindow(TRUE);

				GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);

				GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_SRCPATH)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_BACKUPPATH)->EnableWindow(TRUE);
				return;

			}

			CloseHandle(pThreadDlg->m_hThread);
			pThreadDlg->m_hThread = NULL;


			GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
			m_ProgressCtrl.SetPos(0);
			m_strEditstate = "";
			//KRH
			BOOL bAllChk = IsDlgButtonChecked(IDC_CHECK_ALLDATA);
			theApp.m_bCheckAllData = bAllChk;
			GetDlgItem(IDC_CHECK_ALLDATA)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_TODAY)->EnableWindow(FALSE);
			if (bAllChk == FALSE)
				pThreadDlg = AfxBeginThread(ThreadAllData, this);	//전체 파일
			else
				pThreadDlg = AfxBeginThread(ThreadSubData, this);	//동일 파일

			if (pThreadDlg == NULL)
			{
				GetDlgItem(IDC_CHECK_ALLDATA)->EnableWindow(TRUE);
				GetDlgItem(IDC_CHECK_TODAY)->EnableWindow(TRUE);
				return;

			}
			CloseHandle(pThreadDlg->m_hThread);
			pThreadDlg->m_hThread = NULL;
		}
		else
			AfxMessageBox("소스,백업,릴리즈 경로 입력하세요");

	}
	else
	{
		if (m_strSRCPath != "" && m_strBackupPath != "")
		{
			GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
			m_ProgressCtrl.SetPos(0);
			m_strEditstate = "";
			//KRH
			BOOL bChk = IsDlgButtonChecked(IDC_CHECK_ALLDATA);
			theApp.m_bCheckAllData = bChk;
			if (bChk == FALSE)
				pThreadDlg = AfxBeginThread(ThreadAllData, this);	//전체 파일
			else
				pThreadDlg = AfxBeginThread(ThreadSubData, this);	//동일 파일

			if (pThreadDlg == NULL)
			{
				return;

			}
			CloseHandle(pThreadDlg->m_hThread);
			pThreadDlg->m_hThread = NULL;
		}
		else
			AfxMessageBox(_T("파일 경로가 비어있습니다. 다시 선택하세요."));
	}*/
}


//20160131 수정본
UINT CAutoBackupDlg::ThreadSimple(LPVOID lParam)
{
	CAutoBackupDlg *pfir = (CAutoBackupDlg*)lParam;
	CString strFilecnt;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;
	pfir->m_strEditstate = "";
	pDlg->nFilecount = 0;

	//원본에서 릴리즈 파일 복사를 위해 릴리즈 리스트 생성
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "compile list  start. REL PATH : " + pDlg->m_strRelPath;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->FileCompareFirst(pDlg->m_strRelPath, pDlg->m_strRelPath, 0);
	pDlg->m_ProgressCtrl.SetRange(0, pDlg->nFilecount);
	pDlg->m_ProgressCtrl.SetPos(0);


	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "compile list  END . FILE COUNT : " + strFilecnt;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);


	
	//원본과 릴리즈 비교해서 릴리즈 리스트와 동일한 원본 리스트 생성(파일 복사 리스트)
	pDlg->nFilecount = 0;
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "src compare list  start. SRC PATH : " + pDlg->m_strSRCPath;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->FileCompareFirst(pDlg->m_strSRCPath, pDlg->m_strSRCPath, 1);

	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "src compare list END . FILE COUNT : " + strFilecnt;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);


	//원본 리스트를 참고하여 백업 경로에 복사
	pDlg->nFilecount = 0;
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "backup file copy start. BAK PATH : " + pDlg->m_strBackupPath;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->CopyFromToFileALL(pDlg->m_strSRCPath, pDlg->m_strSRCPath, pDlg->m_strBackupPath, 9);
	pDlg->DeleteEmptyFolder(pDlg->m_strBackupPath);

	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "Complete... file copy count : " + strFilecnt;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);


	pDlg->GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);

	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);

	pDlg->GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);

	return 0;
}


//오늘자 폴더 생성 및 릴리즈 복사
UINT CAutoBackupDlg::ThreadMakeTodayData(LPVOID lParam)
{
	CAutoBackupDlg *pfir = (CAutoBackupDlg*)lParam;
	CString strFilecnt;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;
	pfir->m_strEditstate = "";
	pfir->m_strEditstate = "Make TodayDir.";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->nFilecount = 0;

	if (pDlg->m_strTodayDate == "")
	{
		COleDateTime tToday = COleDateTime::GetCurrentTime();
		//m_strTodayDate = tToday.Format(_T("%Y-%m-%d %H:%M:%S"));
		CString strTemp = tToday.Format(_T("%Y%m%d"));
		//AfxMessageBox(_T("ThreadMakeTodayData  : ") + strTemp);
		
		if (strTemp.GetLength() == 6)
			pDlg->m_strTodayDate = strTemp;
		if (strTemp.GetLength() == 8)
			pDlg->m_strTodayDate = strTemp.Mid(2);

		else
			AfxMessageBox("오늘날짜를 가져오지 못했습니다.");
		//AfxMessageBox(m_strTodayDate);
	}

	//백업 경로에 오늘자 폴더 생성
	CString temp = pDlg->m_strBackupPath + "\\" + pDlg->m_strTodayDate;
	CreateDirectory(pDlg->m_strBackupPath + "\\" + pDlg->m_strTodayDate, NULL);

	//릴리즈 경로에서 오늘자 생성, 수정 파일 리스트 저장
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "compile list  start. REL PATH : " + pDlg->m_strRelPath ;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->FileReleaseMove(pDlg->m_strRelPath, pDlg->m_strRelPath);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n compile list end.";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);


	//릴리즈 경로->목적대상 오늘자 폴더로 파일 복사
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n compile copy  start(R->B).\r\n REL PATH :  " + pDlg->m_strRelPath + "\r\n BACKUP PATH : " + pDlg->m_strBackupPath + "\\" + pDlg->m_strTodayDate;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);

	pDlg->nStrLenghCheck = pfir->m_strEditstate.GetLength();
	pDlg->CopyFromToFileALL(pDlg->m_strRelPath, pDlg->m_strRelPath, pDlg->m_strBackupPath + "\\" + pDlg->m_strTodayDate, 2);

	pDlg->m_strBackupPath = pDlg->m_strBackupPath + "\\" + pDlg->m_strTodayDate;
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "compile copy  End(R->B).";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	return 0;
}


//KRH 전체 데이터 백업
UINT CAutoBackupDlg::ThreadAllData(LPVOID lParam)
{

	CAutoBackupDlg *pfir = (CAutoBackupDlg*)lParam;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;
	CString strFilecnt;

	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "file compare start(S). \r\n SRC PATH  : " + pDlg->m_strSRCPath;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);

	pDlg->nFilecount = 0;
	pDlg->FileCompareFirst(pDlg->m_strSRCPath, pDlg->m_strSRCPath, 0);
	pDlg->m_ProgressCtrl.SetPos(15000);
	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilecnt + "file compare complete(S).";
	pDlg->m_ProgressCtrl.SetPos(30000);

	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	
	int nCnt = pDlg->nFilecount;
	if(nCnt>32000)
		nCnt = 32000;

	pDlg->m_ProgressCtrl.SetRange(0,nCnt);
	pDlg->m_ProgressCtrl.SetPos(0);
	pDlg->nFilecount = 0;
	pDlg->nStrLenghCheck = pfir->m_strEditstate.GetLength();
	CString strDirObjTemp = "";
	strDirObjTemp = pDlg->m_strSRCPath.Mid(pDlg->m_strSRCPath.ReverseFind('\\'));
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "file copy start(S->B). \r\n BACKUP PATH : " + pDlg->m_strBackupPath + strDirObjTemp;
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n Copying................ \r\n";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->m_ProgressCtrl.SetPos(50);
	pDlg->CopyFromToFileALL(pDlg->m_strSRCPath, pDlg->m_strSRCPath, pDlg->m_strBackupPath + strDirObjTemp, 0);

	pDlg->m_ProgressCtrl.SetPos(nCnt);

	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilecnt + "file copy complete(S->B).";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);

	pDlg->GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);

	pDlg->GetDlgItem(IDC_CHECK_TODAY)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_CHECK_ALLDATA)->EnableWindow(TRUE);

	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);

	BOOL bChk = pDlg->IsDlgButtonChecked(IDC_CHECK_TODAY);
	if(bChk ==FALSE)
	{
		pDlg->GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
		pDlg->GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(FALSE);
		pDlg->GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);
	}
	else
	{
		
		pDlg->GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
		pDlg->GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
		pDlg->GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
	}

	AfxMessageBox("백업이 완료되었습니다.");
	return 0;
}

//KRH 비교된 동일 부분만 백업
UINT CAutoBackupDlg::ThreadSubData(LPVOID lParam)
{
	CAutoBackupDlg *pfir = (CAutoBackupDlg*)lParam;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;
	CString strFilecnt;

	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "file compare start. \r\n SRC PATH : "+pDlg->m_strSRCPath +"\r\n BACKUP PATH : " + pDlg->m_strBackupPath + "\r\n"  ;
	pfir->PostMessage(CUSTOM_UPDATEDATA, 0, 0);

	//pDlg->FileCompareFirst(pDlg->m_strSRCPath, pDlg->m_strSRCPath, 0);	//소스 전체 파일 리스트
	pDlg->FileCompareFirst(pDlg->m_strBackupPath, pDlg->m_strBackupPath, 0);	//소스 전체 파일 리스트
	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilecnt + "file SRC compared.";

	pDlg->nFilecount = 0;
	pDlg->FileCompareFirst(pDlg->m_strSRCPath, pDlg->m_strSRCPath, 1);		//동일 파일 리스트(대상)
	pDlg->m_ProgressCtrl.SetPos(15000);
	pfir->PostMessage(CUSTOM_UPDATEDATA, 0, 0);
	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilecnt + "file compare complete.";
	pDlg->m_ProgressCtrl.SetPos(30000);
	pfir->PostMessage(CUSTOM_UPDATEDATA, 0, 0);

	int nCnt = pDlg->nFilecount;
	if(nCnt>32000)
		nCnt = 32000;

	pDlg->m_ProgressCtrl.SetRange(0,nCnt);
	pDlg->nFilecount = 0;
	CString strDirObjTemp = "";
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + "file copy start. \r\n SRC PATH : " + pDlg->m_strSRCPath +"\r\n BACKUP PATH : "+ pDlg->m_strBackupPath + strDirObjTemp;
	pfir->PostMessage(CUSTOM_UPDATEDATA, 0, 0);
	pDlg->nStrLenghCheck = pfir->m_strEditstate.GetLength();
	strDirObjTemp = pDlg->m_strSRCPath.Mid(pDlg->m_strSRCPath.ReverseFind('\\'));
	pDlg->CopyFromToFileALL(pDlg->m_strSRCPath, pDlg->m_strSRCPath, pDlg->m_strBackupPath + strDirObjTemp, 1);

	//	pDlg->PostMessage(CUSTOM_UPDATEDATA , 0 , 0);
	pDlg->m_ProgressCtrl.SetPos(nCnt);


	strFilecnt.Format(_T("%d"), pDlg->nFilecount);
	pfir->DeleteEmptyFolder(pDlg->m_strBackupPath);
	pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilecnt + "file copy complete.";
	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);

	pDlg->GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_AUTOBACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_SRC)->EnableWindow(TRUE);

	return 0;
}

//릴리즈 백업 리스트
void CAutoBackupDlg::FileReleaseMove(CString strFolderPath, CString strFolderPathsub)
{
	CFileFind cFind;
	BOOL bFindType = cFind.FindFile(strFolderPath + _T("\\*.*"));
	//CString strFilter = ".mrd"	//예외 필터
	CString strFolderItem, strFileExt, strTemp;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;

	while (bFindType)
	{
		bFindType = cFind.FindNextFile();
		if (cFind.IsDirectory() && !cFind.IsDots())
		{
			strFolderItem = cFind.GetFilePath();

			FileReleaseMove(strFolderItem, strFolderPathsub);	//하위폴더 검색
			//AfxMessageBox(strFolderItem);

		}
		strFolderItem = cFind.GetFilePath();
		strFileExt = strFolderItem.Mid(strFolderItem.ReverseFind('.'));	//확장자 추출

		if (!cFind.IsDots())
		{
			strFileExt.MakeUpper();
			if (cFind.IsDirectory())
				continue;

			strTemp = strFolderItem;
			strTemp.Replace(strFolderPathsub + "\\", "");
			//			AfxMessageBox(strFolderItem +" : " + strTemp);

			CTime cTimeTemp;
			cFind.GetCreationTime(cTimeTemp);		//파일 생성 시간
			CString strCreate = cTimeTemp.Format("%y%m%d");
			cFind.GetLastWriteTime(cTimeTemp);		//파일 수정 시간
			CString strLastWrite = cTimeTemp.Format("%y%m%d");
			//AfxMessageBox(tCReate + ":::" + tLastWrite);
			CString strdateCompare;

			//컴파일 날짜와 비교해서 컴파일 날짜 없으면 오늘날짜로 삽입
			if (pDlg->m_strCompileDate == "")
				pDlg->m_strCompileDate = pDlg->m_strTodayDate;
		//	AfxMessageBox(_T("FileReleaseMove : ")+ pDlg->m_strCompileDate);
			if (pDlg->m_strCompileDate.GetLength() == 6)
				strdateCompare = pDlg->m_strCompileDate;
			else if (pDlg->m_strCompileDate.GetLength() == 8)
				strdateCompare = pDlg->m_strCompileDate.Mid(2);
			else
				AfxMessageBox("오늘날짜를 가져오지 못했습니다." + pDlg->m_strCompileDate);

			if (strdateCompare.Compare(strCreate) == 0 || strdateCompare.Compare(strLastWrite) == 0)
			{
				m_strReleaseFileDlgMap.SetAt(strTemp, strFolderItem);
				pDlg->nFilecount++;
			}
			//	pfir->m_strState = pfir->m_strState + "\r\n" + strFolderItem;
			//	pfir->SendMessage(CUSTOM_UPDATEDATA,0,0);
		}
	}

}


//nSrc = 0 : 전체백업, 1 : 동일한 파일 백업
void CAutoBackupDlg::FileCompareFirst(CString strFolderPath, CString strFolderPathsub, int nSrc)
{
	CFileFind cFind;
	BOOL bFindType = cFind.FindFile(strFolderPath + _T("\\*.*"));
	//CString strFilter = ".mrd"	//예외 필터
	CString strFolderItem, strFileExt, strTemp;
	CAutoBackupDlg *pDlg = (CAutoBackupDlg*)AfxGetApp()->m_pMainWnd;

	while (bFindType)
	{
		bFindType = cFind.FindNextFile();
		if (cFind.IsDirectory() && !cFind.IsDots())
		{
			strFolderItem = cFind.GetFilePath();

			FileCompareFirst(strFolderItem, strFolderPathsub, nSrc);	//하위폴더 검색
			//AfxMessageBox(strFolderItem);

		}
		strFolderItem = cFind.GetFilePath();
		strFileExt = strFolderItem.Mid(strFolderItem.ReverseFind('.'));	//확장자 추출

		if (!cFind.IsDots())
		{
			strFileExt.MakeUpper();
			if (cFind.IsDirectory())
				continue;

			strTemp = strFolderItem;
			strTemp.Replace(strFolderPathsub + "\\", "");
			//			AfxMessageBox(strFolderItem +" : " + strTemp);
			if (nSrc == 0)	//소스 전체백업 리스트		//20160131 수정본은 릴리즈경로 리스트
			{
				m_strStartFileDlgMap.SetAt(strTemp, strFolderItem);
				pDlg->nFilecount++;
				//	pfir->m_strState = pfir->m_strState + "\r\n" + strFolderItem;
				//	pfir->SendMessage(CUSTOM_UPDATEDATA,0,0);
			}
			else		//전체 파일 중 동일한 파일백업 리스트	////20160131 수정본은 원본리스트 중 릴리즈 경로 리스트와 동일한 것만 백업
			{
				CString strReturnValTmp = "";
				m_strStartFileDlgMap.Lookup(strTemp, strReturnValTmp);
				if (strReturnValTmp != "")
				{
					m_strEndFileDlgMap.SetAt(strTemp, strFolderItem);
					pDlg->nFilecount++;
					pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strTemp + "***" + strFolderItem;
					pfir->PostMessage(CUSTOM_UPDATEDATA,0,0);
					//AfxMessageBox(strFolderItem +" : " + strTemp);
				}
			}

		}
	}
}


//파일 복사 0: 전체 복사, 1: 동일파일, 2:오늘날짜 수정/생성 파일만, 9:하위트리까지 복사 가능
void CAutoBackupDlg::CopyFromToFileALL(CString szFrom, CString szFromRoot, CString szTo, int nSrc)
{
	CFileFind cFileFinder;
	BOOL bResult;
	bResult = cFileFinder.FindFile(szFrom + _T("\\*.*"));
	//if(!cFileFinder.FindFile(szTo+ _T("\\*.*")))
	CreateDirectory(szTo, NULL);

	while (bResult)
	{
		bResult = cFileFinder.FindNextFile();
		CString strFName = cFileFinder.GetFileName();

		if (strFName.Compare(_T(".")) == 0 || strFName.Compare(_T("..")) == 0 || strFName.Compare(_T("Thumbs.db")) == 0)
			continue;

		if (cFileFinder.IsDirectory() == TRUE)
		{
			CreateDirectory(szTo + _T("\\") + strFName, NULL);
			pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + szTo + _T("-->\\") + strFName + " ::CopyFromToFileALL ";
			pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
			CopyFromToFileALL(szFrom + _T("\\") + strFName, szFromRoot, szTo + _T("\\") + strFName, nSrc);	//하위폴더
		}
		else //if(cFileFinder.IsArchived())
		{
			if (nSrc == 0)	//전체 백업 대상
			{
				::CopyFile(szFrom + _T("\\") + strFName, szTo + _T("\\") + strFName, FALSE);
				pfir->nFilecount++;
				//	pfir->m_strState = pfir->m_strState + "\r\n" + strFName, szTo + _T("\\") + strFName;
				//	pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
			}
			else if (nSrc == 1 || nSrc == 2 || nSrc == 9)	//동일 파일 , 오늘날짜 생성/수정 파일, 20160131 수정본
			{

				pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + szFrom + "-->" + szTo + " :: File 9 ";
				pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);

				CString strReturnValTmp = "";
				CString strFilePath ="";
				if (szFrom.GetLength() > szFromRoot.GetLength())
					strFilePath = szFrom.Mid(szFromRoot.GetLength() + 1);
				else
					strFilePath = "";

				pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFilePath + " :: strFilePath ";
				pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
				
				//1 : 동일파일, 2 :오늘날짜 생성/수정 파일
				if (nSrc == 1)
				{
					//Root check
					CString strRootCheck = szFromRoot.Mid(szFromRoot.ReverseFind('\\'));
					if (strFilePath.Compare(strRootCheck) == 0)
						strFilePath = "\\" + strFName;
					else
						strFilePath = strFilePath + _T("\\") + strFName;

					int nIdx = strFilePath.Find('\\');
					if (nIdx != -1)
					{
						strFilePath = strFilePath.Mid(1);
					}
					m_strEndFileDlgMap.Lookup(strFilePath, strReturnValTmp);
				}
				else if (nSrc == 2)
				{
					//Root check
					CString strRootCheck = szFromRoot.Mid(szFromRoot.ReverseFind('\\'));
					if (strFilePath.Compare(strRootCheck) == 0)
						strFilePath = "\\" + strFName;
					else
						strFilePath = strFilePath + _T("\\") + strFName;

					int nIdx = strFilePath.Find('\\');
					if (nIdx != -1)
					{
						strFilePath = strFilePath.Mid(1);
					}

					m_strReleaseFileDlgMap.Lookup(strFilePath, strReturnValTmp);
				}
				else if (nSrc == 9)
				{

					//Root check
					CString strRootCheck = szFromRoot.Mid(szFromRoot.ReverseFind('\\'));

					CString strFindFile = "";
					if (strFilePath == "")
						strFindFile = strFName;
					else
						strFindFile = strFilePath + "\\" + strFName;

					m_strEndFileDlgMap.Lookup(strFindFile, strReturnValTmp);
					pfir->m_strEditstate = pfir->m_strEditstate + "\r\n" + strFindFile + " File find list";
					pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
				}

				if (strReturnValTmp != "")
				{
					::CopyFile(szFrom + _T("\\") + strFName, szTo + _T("\\") + strFName, FALSE);
					pfir->nFilecount++;
					if(nFilecount%100 == 0 )
						pfir->PostMessage(CUSTOM_UPDATEDATA, 0, 0);
					CString strCnt;
					CString strTmp = pfir->m_strEditstate;
					
					strTmp.Delete(pfir->nStrLenghCheck, pfir->m_strEditstate.GetLength());
					
					strCnt.Format(_T("%d"), pfir->nFilecount);

					pfir->m_strEditstate = pfir->m_strEditstate +"\r\n"+ strFName + ":::"+strTmp + strCnt + " File Copying";
					pfir->SendMessage(CUSTOM_UPDATEDATA, 0, 0);
				}
			}
		}
	}
}


//빈폴더 삭제
BOOL CAutoBackupDlg::DeleteEmptyFolder(CString strPath)
{
	CFileFind finder;
	int nValidCnt = 0;

	BOOL bWorking = finder.FindFile(strPath + "\\*.*");


	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots()) continue;
		else if (finder.IsDirectory())
		{
			if (DeleteEmptyFolder(finder.GetFilePath()) == TRUE)
				nValidCnt++;
		}
		else
			nValidCnt++;
	}

	if (nValidCnt == 0)
	{
		RemoveDirectory(strPath);
		TRACE("Del : %s\n", (LPCTSTR)strPath);
		return FALSE;
	}

	return TRUE;
}

void CAutoBackupDlg::OnBnClickedCheckToday()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	COleDateTime tToday = COleDateTime::GetCurrentTime();
	//m_strTodayDate = tToday.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString strTemp = tToday.Format(_T("%Y%m%d"));
//	AfxMessageBox(_T("OnBnClickedCheckToday :  ") + strTemp );
	if (strTemp.GetLength() == 8)
		m_strTodayDate = strTemp.Mid(2);
	else if (strTemp.GetLength() == 6)
		m_strTodayDate = strTemp;
	else
		AfxMessageBox("오늘날짜를 가져오지 못했습니다. : " + m_strTodayDate );

	BOOL bChk = IsDlgButtonChecked(IDC_CHECK_TODAY);
	if (bChk == FALSE)
	{
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_REL)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RELPATH)->EnableWindow(TRUE);
	}
}


void CAutoBackupDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDTChange->st.wYear;
	CString strYear, strMonth, strDay;
	strYear.Format("%4d", pDTChange->st.wYear);
	strMonth.Format("%d", pDTChange->st.wMonth);
	strDay.Format("%d", pDTChange->st.wDay);

	if (strMonth.GetLength() < 2)
		strMonth = "0" + strMonth;
	if (strDay.GetLength() < 2)
		strDay = "0" + strDay;

	CString strDate = strYear + strMonth + strDay;
	m_strCompileDate = strDate;
	m_CompileDate.SetDate(_ttoi(strYear), _ttoi(strMonth), _ttoi(strDay));
	*pResult = 0;
}


void CAutoBackupDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	AfxMessageBox("경로 저장되었습니다");
	CDialogEx::OnOK();
}


void CAutoBackupDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox("경로 저장 취소 되었습니다");
	CDialogEx::OnCancel();
}

void CAutoBackupDlg::OnEnUpdateEditRelpath()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


void CAutoBackupDlg::OnBnClickedFilecopyseetbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileCopysetDlg Dlg;
	INT_PTR nResult = Dlg.DoModal();
	if (nResult == IDOK)
	{
		AfxMessageBox("파일복사 설정 저장 되었습니다");
	}
}


void CAutoBackupDlg::OnBnClickedCompilesetbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCompileSetDlg Dlg;
	INT_PTR nResult = Dlg.DoModal();
	if (nResult == IDOK)
	{
		AfxMessageBox("컴파일 복사 설정 저장 되었습니다");
	}
}
