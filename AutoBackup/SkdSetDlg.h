#pragma once


// CSkdSetDlg ��ȭ �����Դϴ�.

class CSkdSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSkdSetDlg)

public:
	CSkdSetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSkdSetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SKDSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
