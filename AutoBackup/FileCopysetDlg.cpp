// FileCopysetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "FileCopysetDlg.h"
#include "afxdialogex.h"


// CFileCopysetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFileCopysetDlg, CDialog)

CFileCopysetDlg::CFileCopysetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileCopysetDlg::IDD, pParent)
{

}

CFileCopysetDlg::~CFileCopysetDlg()
{
}

void CFileCopysetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL CFileCopysetDlg::PreTranslateMessage(MSG* pMsg)

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

BEGIN_MESSAGE_MAP(CFileCopysetDlg, CDialog)
END_MESSAGE_MAP()


// CFileCopysetDlg �޽��� ó�����Դϴ�.
