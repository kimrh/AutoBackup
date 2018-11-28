// FileCopysetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "FileCopysetDlg.h"
#include "afxdialogex.h"


// CFileCopysetDlg 대화 상자입니다.

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

BEGIN_MESSAGE_MAP(CFileCopysetDlg, CDialog)
END_MESSAGE_MAP()


// CFileCopysetDlg 메시지 처리기입니다.
