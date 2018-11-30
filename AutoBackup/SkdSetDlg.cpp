// SkdSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "SkdSetDlg.h"


// CSkdSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSkdSetDlg, CDialog)

CSkdSetDlg::CSkdSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkdSetDlg::IDD, pParent)
{

}

CSkdSetDlg::~CSkdSetDlg()
{
}

void CSkdSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkdSetDlg, CDialog)
END_MESSAGE_MAP()


// CSkdSetDlg 메시지 처리기입니다.
