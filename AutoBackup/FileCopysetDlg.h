#pragma once


// CFileCopysetDlg ��ȭ �����Դϴ�.

class CFileCopysetDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileCopysetDlg)

public:
	CFileCopysetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileCopysetDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILECOPYSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
