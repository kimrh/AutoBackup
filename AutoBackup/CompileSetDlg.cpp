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
END_MESSAGE_MAP()


// CCompileSetDlg �޽��� ó�����Դϴ�.

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
