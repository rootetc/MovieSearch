#pragma once
#include "afxwin.h"


// DB_Analysis ��ȭ �����Դϴ�.

class DB_Analysis : public CDialogEx
{
	DECLARE_DYNAMIC(DB_Analysis)

public:
	DB_Analysis(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DB_Analysis();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

	CString MoviePath; //�������� ���
	int Count_File; // ������ ����
};


