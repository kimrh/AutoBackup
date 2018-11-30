#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CCompileSetDlg 대화 상자입니다.

class CCompileSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompileSetDlg)

public:
	CCompileSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCompileSetDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMPILESET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditSRCPath;
	CEdit m_EditDestPath;
	CButton m_BtnSrcPath;
	CButton m_BtnDestPath;
	CButton m_BtnRegst;
	CButton m_BtnDelete;
	CEdit m_EditListInput;
	CComboBox m_ComboCompileCopyList;
	CButton m_BtnExtensionList;
	CButton m_BtnExceptList;
	CDateTimeCtrl m_DateCompileDate;
	CButton m_ChkComplieDate;
	CButton m_ChkExtList;
	CButton m_ChkExceptList;
	
	CEdit m_EditCompileLog;


	afx_msg void OnBnClickedCheckexcept();
	afx_msg void OnBnClickedCheckext();
	afx_msg void OnBnClickedCheckdate();
};
