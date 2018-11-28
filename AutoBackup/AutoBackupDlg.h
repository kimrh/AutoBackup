
// AutoBackupDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ATLComTime.h"

#define CUSTOM_UPDATEDATA WM_USER

// CAutoBackupDlg ��ȭ ����
class CAutoBackupDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAutoBackupDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTOBACKUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CString m_strSRCPath;	// �������
	CString m_strBackupPath;	// ������
	CString m_strRelPath;	// ��������
	CEdit m_EditState;	// ����Ʈ ��Ʈ��
	CEdit m_EditCtrlRelPath;// ������ ����Ʈ ��Ʈ��
	CString m_strEditstate;	// ����Ʈ�� ���� ���
	CProgressCtrl m_ProgressCtrl;	// ���α׷��� ǥ��
	BOOL m_bCheckAllData;	// ��ü ���Ϲ�� ����
	BOOL m_bCheckToday;	// ������ ������ ������� ����
	

	CString m_strCompileDate;	//������ ��¥
	int nFilecount;		//���� ���� ī��Ʈ(����Ʈ �� ǥ�ÿ�)
	int nStrLenghCheck; //����Ʈ �� ��Ʈ�� ���� ǥ�ÿ�

	CString m_strTodayDate;	//���ó�¥ ����

	CMapStringToString	m_strStartFileDlgMap;	//�ҽ�
	CMapStringToString	m_strEndFileDlgMap;		//���
	CMapStringToString	m_strReleaseFileDlgMap;	//������

	static UINT ThreadAllData(LPVOID lParam);
	static UINT ThreadSubData(LPVOID lParam);
	static UINT ThreadMakeTodayData(LPVOID lParam);
	static UINT ThreadUIListEditCtrl(LPVOID lParam);	//����Ʈ ����Ʈ�ڽ�
	static UINT CAutoBackupDlg::ThreadSimple(LPVOID lParam);	//20160131 ������

	CWinThread *pThreadDlg;
	CAutoBackupDlg *pfir;
	
	void	FileCompareFirst(CString strFolderPath, CString strFolderPathsub, int nSrc);
	void	CopyFromToFileALL(CString szFrom, CString szFromRoot, CString szTo, int nSrc);
	void	FileReleaseMove(CString strFolderPath, CString strFolderPathsub);
	BOOL	DeleteEmptyFolder(CString strPath);
	
	afx_msg LRESULT ForCustomMessageFromThread(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonSrc();
	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonRel();
	afx_msg void OnBnClickedButtonAutobackup();
	afx_msg void OnBnClickedCheckToday();
	
	// ������ ��¥ ��Ʈ��
	COleDateTime m_CompileDate;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnUpdateEditRelpath();
	afx_msg void OnBnClickedFilecopyseetbtn();
	afx_msg void OnBnClickedCompilesetbtn();
};
