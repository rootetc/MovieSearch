
// AnalysisDlg.h : ��� ����
//

#pragma once
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "CvvImage.h"
#include "afxwin.h"

// CAnalysisDlg ��ȭ ����
class CAnalysisDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CAnalysisDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ANALYSIS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	virtual BOOL OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int maxFileNum;	// ��ü ���� ����
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

	BOOL A, B = false;//���̹����� ���õǾ� ������ Ȯ�� �Ͽ��ִ� ����.
	CString final_original_file_path; //��� �̹��� ���
	CString		pathName;		// ���� ���� ���
	CString Original_RGB[100]; // �� ��� �̹����� RGB��

	IplImage*   r_pImage; // ���� ��� �̹����� �޴� ����.
	IplImage*   m_pImage; // �� �̹��� �� ����.
	int image_number; // ���° �̹��������� ��Ÿ����.
};
