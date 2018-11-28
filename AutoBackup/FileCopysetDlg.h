#pragma once


// CFileCopysetDlg 대화 상자입니다.

class CFileCopysetDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileCopysetDlg)

public:
	CFileCopysetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileCopysetDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FILECOPYSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
