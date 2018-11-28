
// AutoBackupDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ATLComTime.h"

#define CUSTOM_UPDATEDATA WM_USER

// CAutoBackupDlg 대화 상자
class CAutoBackupDlg : public CDialogEx
{
// 생성입니다.
public:
	CAutoBackupDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTOBACKUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CString m_strSRCPath;	// 원본경로
	CString m_strBackupPath;	// 백업경로
	CString m_strRelPath;	// 릴리즈경로
	CEdit m_EditState;	// 리스트 컨트롤
	CEdit m_EditCtrlRelPath;// 릴리즈 에디트 컨트롤
	CString m_strEditstate;	// 리스트뷰 상태 출력
	CProgressCtrl m_ProgressCtrl;	// 프로그레스 표시
	BOOL m_bCheckAllData;	// 전체 파일백업 여부
	BOOL m_bCheckToday;	// 오늘자 생성및 릴리즈복사 여부
	

	CString m_strCompileDate;	//컴파일 날짜
	int nFilecount;		//파일 개수 카운트(리스트 뷰 표시용)
	int nStrLenghCheck; //리스트 뷰 스트링 길이 표시용

	CString m_strTodayDate;	//오늘날짜 저장

	CMapStringToString	m_strStartFileDlgMap;	//소스
	CMapStringToString	m_strEndFileDlgMap;		//대상
	CMapStringToString	m_strReleaseFileDlgMap;	//릴리즈

	static UINT ThreadAllData(LPVOID lParam);
	static UINT ThreadSubData(LPVOID lParam);
	static UINT ThreadMakeTodayData(LPVOID lParam);
	static UINT ThreadUIListEditCtrl(LPVOID lParam);	//리스트 에디트박스
	static UINT CAutoBackupDlg::ThreadSimple(LPVOID lParam);	//20160131 수정본

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
	
	// 컴파일 날짜 컨트롤
	COleDateTime m_CompileDate;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnUpdateEditRelpath();
	afx_msg void OnBnClickedFilecopyseetbtn();
	afx_msg void OnBnClickedCompilesetbtn();
};
