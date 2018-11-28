
// AutoBackup.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CAutoBackupApp:
// 이 클래스의 구현에 대해서는 AutoBackup.cpp을 참조하십시오.
//

class CAutoBackupApp : public CWinApp
{
public:
	CAutoBackupApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
public:
	
	CString	m_sAppPath;		// 실행 파일 경로
	CString m_strSRCPath;	// 원본경로
	CString m_strBackupPath;	// 백업경로
	CString m_strBackupPathSrc;	// 백업경로 원본 저장
	CString m_strRelPath;	// 릴리즈경로
	BOOL m_bCheckAllData;	// 전체 파일백업 여부	
	BOOL m_bCheckToday;	// 오늘자 생성및 릴리즈복사 여부
	//메인 파일 설정
	CEdit m_EditState;	// 리스트 컨트롤
	CProgressCtrl m_ProgressCtrl;	// 프로그레스 표시
	


	//컴파일 복사 설정
	CString m_strCompileSRCPath;	//원본경로
	CString m_strCompileDestPath;	//복사할경로
	CMapStringToString m_CompileExceptExtensionsMap;	//예외확장자 리스트
	CMapStringToString m_CompileExceptFilesMap;	//예외파일 리스트
	CMapStringToString m_CompileListMap;	//컴파일 대상 리스트
	CString m_strComileDate;	//컴파일 날짜 설정



	DECLARE_MESSAGE_MAP()
};

extern CAutoBackupApp theApp;