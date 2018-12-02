// CompileSetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "CompileSetDlg.h"
#include "afxdialogex.h"


// CCompileSetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCompileSetDlg, CDialog)

BEGIN_MESSAGE_MAP(CCompileSetDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECKEXCEPT, &CCompileSetDlg::OnBnClickedCheckexcept)
	ON_BN_CLICKED(IDC_CHECKEXT, &CCompileSetDlg::OnBnClickedCheckext)
	ON_BN_CLICKED(IDC_CHECKDATE, &CCompileSetDlg::OnBnClickedCheckdate)
	ON_BN_CLICKED(IDC_RGST_COMPILESET_BTN, &CCompileSetDlg::OnBnClickedRgstCompilesetBtn)
	ON_CBN_SELCHANGE(IDC_COMBO_LIST, &CCompileSetDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_COMPILESRC, &CCompileSetDlg::OnBnClickedButtonCompilesrc)
	ON_BN_CLICKED(IDC_BUTTON_COMPILEDESC, &CCompileSetDlg::OnBnClickedButtonCompiledesc)

END_MESSAGE_MAP()


// CCompileSetDlg �޽��� ó�����Դϴ�.

CCompileSetDlg::CCompileSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompileSetDlg::IDD, pParent)
{
	

}

CCompileSetDlg::~CCompileSetDlg()
{
}

BOOL CCompileSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetcomboboxData();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCompileSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPILESRCPATH, m_EditSRCPath);
	DDX_Control(pDX, IDC_EDIT_COMPILECOPYPATH, m_EditDestPath);
	DDX_Control(pDX, IDC_BUTTON_COMPILESRC, m_BtnSrcPath);
	DDX_Control(pDX, IDC_BUTTON_COMPILEDESC, m_BtnDestPath);
	DDX_Control(pDX, IDC_RGST_COMPILESET_BTN, m_BtnRegst);
	DDX_Control(pDX, IDC_RGST_COMPILSET_BUTTON, m_BtnDelete);
	DDX_Control(pDX, IDC_EDIT_LIST_NM, m_EditListInput);
	DDX_Control(pDX, IDC_COMBO_LIST, m_ComboCompileCopyList);
	DDX_Control(pDX, IDC_BUTTON_COMPILE_EXT, m_BtnExtensionList);
	DDX_Control(pDX, IDC_BUTTON_COMPILE_EXCEPT, m_BtnExceptList);
	DDX_Control(pDX, IDC_DATETIMEPICKER_COMPILE_DATE, m_DateCompileDate);
	DDX_Control(pDX, IDC_CHECK_COMPILE_DATE, m_ChkComplieDate);
	DDX_Control(pDX, IDC_CHECK_COMPILE_EXT, m_ChkExtList);
	DDX_Control(pDX, IDC_CHECK_COMPILE_EXCEPT, m_ChkExceptList);
	DDX_Control(pDX, IDC_EDIT_COMPILE_LOG, m_EditCompileLog);
	DDX_Control(pDX, IDC_CHECK_COMPILE_ACPT, m_CheckListAcceptYN);
}


BOOL CCompileSetDlg::PreTranslateMessage(MSG* pMsg)

{

	switch (pMsg->message)

	{

		// Ű�� ��������

	case WM_KEYDOWN:

		switch (pMsg->wParam)

		{

			// ����Ű\tab

		case VK_RETURN:

			return TRUE;

			// ESCŰ

		case VK_ESCAPE:

			return TRUE;

		}

	}

	return CDialog::PreTranslateMessage(pMsg);

}




void CCompileSetDlg::OnBnClickedCheckexcept()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCompileSetDlg::OnBnClickedCheckext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCompileSetDlg::OnBnClickedCheckdate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCompileSetDlg::OnBnClickedRgstCompilesetBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bDuplecheck = FALSE;
	CString strVal = "";
	m_EditListInput.GetWindowText(strVal);

	if (strVal.GetLength() == 0)
	{
		AfxMessageBox(_T("������ ����Ʈ�� �Է��ϼ���."));
		return;
	}

	int findIdx = m_ComboCompileCopyList.FindStringExact(-1, strVal);
	if (findIdx > -1)
	{
		int ret = AfxMessageBox(_T("�ߺ��� �̸��� �ֽ��ϴ�. OVERWRITE?"), MB_YESNO);
		if (ret == IDCANCEL)
			return;
		bDuplecheck = TRUE;
	}
	CString strSRC = "";
	CString strDest = "";

	m_EditSRCPath.GetWindowText(strSRC);
	m_EditDestPath.GetWindowText(strDest);

	CString sIniFilePath;
	sIniFilePath = theApp.m_sAppPath + "\\Setting.ini";
	int nCount = GetPrivateProfileInt("CompileCopySet", "count", 0, sIniFilePath);
	memset(szBuffer, 0, 600);

	if (bDuplecheck== FALSE)
		++nCount;

	sprintf(szBuffer, "%d", nCount);
	WritePrivateProfileString("CompileCopySet", _T("count"), szBuffer, sIniFilePath);

	if (bDuplecheck == FALSE)
		WritePrivateProfileString(_T("CompileCopySet"), szBuffer, strVal + _T(";") + strSRC + _T(";") + strDest, sIniFilePath);
	else
	{
		int Idx = m_ComboCompileCopyList.GetCurSel();
		memset(szBuffer, 0, 600);
		sprintf(szBuffer, "%d", Idx+1);
		WritePrivateProfileString(_T("CompileCopySet"), szBuffer, strVal + _T(";") + strSRC + _T(";") + strDest, sIniFilePath);
	}

	if (IsDlgButtonChecked(IDC_CHECK_COMPILE_ACPT) == TRUE)
	{
		WritePrivateProfileString(_T("CompileCopySet"), strVal, "Y", sIniFilePath);
		theApp.m_CompileCheckListMap.SetAt(strVal, "Y");
	}
	else
	{
		WritePrivateProfileString(_T("CompileCopySet"), strVal, "N", sIniFilePath);
		theApp.m_CompileCheckListMap.SetAt(strVal, "N");
	}
	


	//�����Ϻ��� ��� ����Ʈ �ҷ�����
	CString strKey, strTotPth;
	theApp.m_CompileListMap.RemoveAll();
	nCount = GetPrivateProfileInt("CompileCopySet", "count", 0, sIniFilePath);
	int i = 0;
	if (nCount > 0)
	{
		for (i = 1; i < nCount + 1; i++)
		{
			strKey.Format("%d", i);
			memset(szBuffer, 0, 600);
			::GetPrivateProfileString("CompileCopySet", strKey, "", szBuffer, 600, sIniFilePath);

			strTotPth = szBuffer;
			int nToken = strTotPth.Find(';');
			strKey = strTotPth.Left(nToken);
			strVal = strTotPth.Mid(nToken + 1);
			theApp.m_CompileListMap.SetAt(strKey, strVal);
		}
	}
	SetcomboboxData();
	m_EditListInput.SetWindowText(_T(""));


	AfxMessageBox(_T("��ϵǾ����ϴ�."));
}


void CCompileSetDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strKey, strsrc, strDest, strTotPth;;
	CString strAcceptYN;

	int cnt = m_ComboCompileCopyList.GetCurSel();
	//m_ComboCompileCopyList.GetWindowTextA(strKey);
	m_ComboCompileCopyList.GetLBText(cnt, strKey);
	theApp.m_CompileListMap.Lookup(strKey, strTotPth);
	theApp.m_CompileCheckListMap.Lookup(strKey, strAcceptYN);
	int nToken = strTotPth.Find(';');
	strsrc = strTotPth.Left(nToken);
	strDest = strTotPth.Mid(nToken + 1);

	GetDlgItem(IDC_EDIT_COMPILESRCPATH)->SetWindowText(strsrc);
	GetDlgItem(IDC_EDIT_COMPILECOPYPATH)->SetWindowText(strDest);
	
	if (strAcceptYN == "Y")
		CheckDlgButton(IDC_CHECK_COMPILE_ACPT, TRUE);
	else
		CheckDlgButton(IDC_CHECK_COMPILE_ACPT, FALSE);


}


void CCompileSetDlg::OnBnClickedButtonCompilesrc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	try
	{
		GetDlgItem(IDC_BUTTON_COMPILESRC)->EnableWindow(FALSE);
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
			theApp.m_strCompileSRCPath = szpathName;

		GetDlgItem(IDC_EDIT_COMPILESRCPATH)->SetWindowText(theApp.m_strCompileSRCPath);
		m_strCompileSRCPath = theApp.m_strCompileSRCPath;
		GetDlgItem(IDC_BUTTON_COMPILESRC)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("��ΰ� �߸��Ǿ����ϴ� �ٽ� �����ϼ���."));
		theApp.m_strCompileSRCPath = "";
		UpdateData(FALSE);
	}
}



void CCompileSetDlg::OnBnClickedButtonCompiledesc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	try
	{
		GetDlgItem(IDC_BUTTON_COMPILEDESC)->EnableWindow(FALSE);
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
			theApp.m_strCompileDestPath = szpathName;

		GetDlgItem(IDC_EDIT_COMPILECOPYPATH)->SetWindowText(theApp.m_strCompileDestPath);
		m_strCompileDestPath = theApp.m_strCompileDestPath;
		GetDlgItem(IDC_BUTTON_COMPILEDESC)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("��ΰ� �߸��Ǿ����ϴ� �ٽ� �����ϼ���."));
		theApp.m_strCompileDestPath = "";
		UpdateData(FALSE);
	}
}


void CCompileSetDlg::SetcomboboxData()
{
	CString strKey, strTotPth;

	m_ComboCompileCopyList.ResetContent();

	POSITION pos = theApp.m_CompileListMap.GetStartPosition();
	while (pos)
	{
		theApp.m_CompileListMap.GetNextAssoc(pos, strKey, strTotPth);
		m_ComboCompileCopyList.AddString(_T(strKey));

	}
	int cnt = theApp.m_CompileListMap.GetCount();
	if (cnt > 0)
	{
		m_ComboCompileCopyList.SetCurSel(0);
		OnCbnSelchangeCombo1();
	}
}

