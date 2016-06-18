#pragma once
#include "afxwin.h"


// DB_Analysis 대화 상자입니다.

class DB_Analysis : public CDialogEx
{
	DECLARE_DYNAMIC(DB_Analysis)

public:
	DB_Analysis(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~DB_Analysis();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnSpilt();
	afx_msg void OnBnClickedBtnSame();
	afx_msg void OnBnClickedBtnHash();

	CEdit C_vidieo_name;
	CEdit C_state;
	CEdit Same_count;
	CEdit C_time;

	typedef struct ListNode{
		int image_name;
		ListNode *next;
		ListNode(int value)
		{
			image_name = value;
			next = NULL;
		}
	}ListNode;

	CString MoviePath; //동영상의 경로
	int Count_File; // 파일의 개수
};


