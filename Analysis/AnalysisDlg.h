
// AnalysisDlg.h : 헤더 파일
//

#pragma once
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "CvvImage.h"
#include "afxwin.h"

// CAnalysisDlg 대화 상자
class CAnalysisDlg : public CDialogEx
{
	// 생성입니다.
public:
	CAnalysisDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ANALYSIS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual BOOL OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int maxFileNum;	// 전체 파일 개수
	CvvImage	m_cImage;
	CvvImage    r_cImage;

	CStatic m_PicSrc;
	CStatic r_PicSrc;

	CEdit original_path;
	CEdit second_path;
	CEdit final_time;

	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnAn();
	afx_msg void OnBnClickedBtnOk();

	BOOL A, B = false;//비교이미지가 선택되어 졌는지 확인 하여주는 변수.
	CString final_original_file_path; //출력 이미지 경로
	CString		pathName;		// 현재 폴더 경로
	CString Original_RGB[100]; // 비교 대상 이미지의 RGB값

	IplImage*   r_pImage; // 최종 출력 이미지를 받는 변수.
	IplImage*   m_pImage; // 비교 이미지 값 설정.
	int image_number; // 몇번째 이미지인지를 나타낸다.
};
