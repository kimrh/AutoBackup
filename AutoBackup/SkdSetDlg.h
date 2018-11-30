#pragma once


// CSkdSetDlg 대화 상자입니다.

class CSkdSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSkdSetDlg)

public:
	CSkdSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSkdSetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SKDSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
