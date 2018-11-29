// CompileSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "CompileSetDlg.h"
#include "afxdialogex.h"


// CCompileSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompileSetDlg, CDialog)

BEGIN_MESSAGE_MAP(CCompileSetDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECKEXCEPT, &CCompileSetDlg::OnBnClickedCheckexcept)
	ON_BN_CLICKED(IDC_CHECKEXT, &CCompileSetDlg::OnBnClickedCheckext)
	ON_BN_CLICKED(IDC_CHECKDATE, &CCompileSetDlg::OnBnClickedCheckdate)
	ON_BN_CLICKED(IDC_BUTTON_COMPILESRC, &CCompileSetDlg::OnBnClickedButtonCompilesrc)
	ON_BN_CLICKED(IDC_BUTTON_COMPILECOPYSRC, &CCompileSetDlg::OnBnClickedButtonCompilecopysrc)
	ON_BN_CLICKED(IDC_RGST_COMPILESET_BTN, &CCompileSetDlg::OnBnClickedRgstCompilesetBtn)
END_MESSAGE_MAP()


// CCompileSetDlg 메시지 처리기입니다.

CCompileSetDlg::CCompileSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompileSetDlg::IDD, pParent)
{

}

CCompileSetDlg::~CCompileSetDlg()
{
}

void CCompileSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPILESRCPATH, m_EditSRCPath);
	DDX_Control(pDX, IDC_EDIT_COMPILECOPYPATH, m_EditDestPath);
	DDX_Control(pDX, IDC_BUTTON_COMPILESRC, m_BtnSrcPath);
	DDX_Control(pDX, IDC_BUTTON_COMPILECOPYSRC, m_BtnDestPath);
	DDX_Control(pDX, IDC_RGST_COMPILESET_BTN, m_BtnRegst);
	DDX_Control(pDX, IDC_RGST_COMPILSET_BUTTON, m_BtnDelete);
	DDX_Control(pDX, IDC_EDIT1, m_EditListInput);
	DDX_Control(pDX, IDC_COMBO1, m_ComboCompileCopyList);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnExtensionList);
	DDX_Control(pDX, IDC_BUTTON2, m_BtnExceptList);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_DateCompileDate);
	DDX_Control(pDX, IDC_CHECKDATE, m_ChkComplieDate);
	DDX_Control(pDX, IDC_CHECKEXT, m_ChkExtList);
	DDX_Control(pDX, IDC_CHECKEXCEPT, m_ChkExceptList);
	DDX_Control(pDX, IDC_EDIT_COMPILE_LOG, m_EditCompileLog);
}


BOOL CCompileSetDlg::PreTranslateMessage(MSG* pMsg)

{

	switch (pMsg->message)

	{

		// 키가 눌렸을때

	case WM_KEYDOWN:

		switch (pMsg->wParam)

		{

			// 리턴키\tab

		case VK_RETURN:

			return TRUE;

			// ESC키

		case VK_ESCAPE:

			return TRUE;

		}

	}

	return CDialog::PreTranslateMessage(pMsg);

}




void CCompileSetDlg::OnBnClickedCheckexcept()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCompileSetDlg::OnBnClickedCheckext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCompileSetDlg::OnBnClickedCheckdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCompileSetDlg::OnBnClickedButtonCompilesrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			m_strEditSRCPath = szpathName;
		else
			m_strEditSRCPath = "";

		GetDlgItem(IDC_EDIT_SRCPATH)->SetWindowText(m_strEditSRCPath);
		GetDlgItem(IDC_BUTTON_COMPILESRC)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("경로가 잘못되었습니다 다시 선택하세요."));
		UpdateData(FALSE);
	}
}


void CCompileSetDlg::OnBnClickedButtonCompilecopysrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		GetDlgItem(IDC_BUTTON_COMPILECOPYSRC)->EnableWindow(FALSE);
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
			m_strEditDestPath = szpathName;
		else
			m_strEditDestPath = "";

		GetDlgItem(IDC_EDIT_SRCPATH)->SetWindowText(m_strEditDestPath);
		GetDlgItem(IDC_BUTTON_COMPILECOPYSRC)->EnableWindow(TRUE);
	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("경로가 잘못되었습니다 다시 선택하세요."));
	}
}

//컴파일 복사 대상 등록
void CCompileSetDlg::OnBnClickedRgstCompilesetBtn()
{
	try{
		CString strListNm = "";
		CString strSrcPath;
		CString strDesPath;

		m_EditListInput.GetWindowTextA(strListNm);
		if (strListNm.GetLength() == 0)
		{
			AfxMessageBox(_T("리스트명 입력바랍니다."));
			return;
		}
		
		m_EditSRCPath.GetWindowTextA(strSrcPath);
		if (strSrcPath.GetLength() == 0)
		{
			AfxMessageBox(_T("원본경로 입력바랍니다."));
			return;
		}

		m_EditDestPath.GetWindowTextA(strDesPath);
		if (strDesPath.GetLength() == 0)
		{
			AfxMessageBox(_T("원본경로 입력바랍니다."));
			return;
		}

		CString strVal = strSrcPath + "," + strDesPath;
		theApp.m_CompileListMap.SetAt(strListNm, strVal);
		m_ComboCompileCopyList.AddString(strListNm);

	}
	catch (CException *e)
	{
		e->Delete();
		AfxMessageBox(_T("처리중 오류가 발생했습니다. 재등록 바랍니다."));
	}
}
