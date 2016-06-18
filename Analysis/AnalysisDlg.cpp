// AnalysisDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Analysis.h"
#include "AnalysisDlg.h"
#include "afxdialogex.h"
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include"CvvImage.h"
#include<opencv\cxcore.h>
#include"DB_Analysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int number_array;
extern CString **DB_array; // DB�� �迭 ����.
extern  DB_Analysis::ListNode *Hash_table[256][100];

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	Invalidate(false);
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnalysisDlg ��ȭ ����



CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CAnalysisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX) //dialog�� ������ �����ϴ� ����!!!!
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_SRC, m_PicSrc);
	DDX_Control(pDX, IDC_PIC_RRC, r_PicSrc);
	DDX_Control(pDX, IDC_Path, original_path);
	DDX_Control(pDX, IDC_Path2, second_path);
	DDX_Control(pDX, IDC_time, final_time);
}

BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CAnalysisDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_An, &CAnalysisDlg::OnBnClickedBtnAn)
	ON_BN_CLICKED(IDC_BTN_OK, &CAnalysisDlg::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CAnalysisDlg �޽��� ó����

BOOL CAnalysisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

	r_pImage;
}

void CAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == SC_CLOSE){
		EndDialog(IDCANCEL);
		if (m_pImage != NULL) cvReleaseImage(&m_pImage);
		if (r_pImage != NULL) cvReleaseImage(&r_pImage);
		remove("c:\\test.mp4");
		return;
	}
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAnalysisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		if (m_pImage)
		{
			CDC*	pDC;
			CRect	rect;

			pDC = m_PicSrc.GetDC();
			m_PicSrc.GetClientRect(&rect);
			m_cImage.CopyOf(m_pImage);
			m_cImage.DrawToHDC(pDC->m_hDC, &rect);
			cvReleaseImage(&m_pImage);
			ReleaseDC(pDC);
		}
		if (r_pImage)
		{
			CDC*	pDC;
			CRect	rect;
			pDC = r_PicSrc.GetDC();
			r_PicSrc.GetClientRect(&rect);
			r_cImage.CopyOf(r_pImage);
			r_cImage.DrawToHDC(pDC->m_hDC, &rect);
			ReleaseDC(pDC);
			cvReleaseImage(&r_pImage);
		}
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAnalysisDlg::OnBnClickedBtnOpen()
{

	CFileDialog fd(TRUE);
	if (fd.DoModal() == IDOK)
		pathName = fd.GetPathName();// ���� ������ ������ ���

	if (pathName.GetLength() > 0)
	{
		if (m_pImage != NULL){
			cvReleaseImage(&m_pImage);
			m_pImage = cvLoadImage(pathName, 1);
			original_path.SetWindowTextA(pathName);
		}
		else{
			m_pImage = cvLoadImage(pathName, 1);
			original_path.SetWindowTextA(pathName);
		}

		A = TRUE;
		Invalidate(false);
		UpdateData(true);
	}

	IplImage *R_image = cvCreateImage(cv::Size(640, 480), m_pImage->depth, m_pImage->nChannels);
	cvResize(m_pImage, R_image, 1);
	///////////////////////////////////////////////////////////////////////���� �̹��� RGB�� ����////////////////////////////////////////////////////////////
	
	int real_width, real_height;
	CvScalar temp_scalar;
	int orignal_temp_sum[100] = { 0 };  // �ӽ� RGB���� ���.
	
	if (m_pImage)
	{
		//first_image�� 10x10���� �ɰ��� pixel���� ����.
		for (int y_block = 0; y_block < 10; y_block++)
		{
			for (int x_block = 0; x_block < 10; x_block++)
			{
				for (int col = 0; col < 64; col++)
				{
					for (int row = 0; row < 48; row++)
					{
						real_width = x_block * 64 + col;
						real_height = y_block * 48 + row;
						temp_scalar = cvGet2D(R_image, real_height, real_width);
						orignal_temp_sum[x_block + 10 * y_block] += (temp_scalar.val[0] + temp_scalar.val[1] + temp_scalar.val[2]) / 3.0f;
					}
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			orignal_temp_sum[i] = orignal_temp_sum[i] / 3185;
			Original_RGB[i].Format("%d", orignal_temp_sum[i]);
		}
	}

	cvReleaseImage(&R_image);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAnalysisDlg::OnBnClickedBtnAn()
{
	if (A == TRUE)
	{
		DB_Analysis dlg;
		dlg.DoModal();
		B = TRUE;
	}
	else{
		B = FALSE;
		::AfxMessageBox(_T("���̹����� ������ �ּ���."));
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CAnalysisDlg::OnDestroy()
{
	if (m_pImage != NULL) cvReleaseImage(&m_pImage);
	if (r_pImage != NULL) cvReleaseImage(&r_pImage);
	delete Hash_table[256][100];
	remove("c:\\test.mp4");
	return true;
}


void CAnalysisDlg::OnBnClickedBtnOk()
{
	if (B == TRUE)
	{
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		int count = 0,max = 0; // �ִ밪 ����
		for (int i = 0; i <= number_array; i++)
		{
			DB_array[i][102].Format("%d", 0);
		}
		int key;
		for (int RGB_AREA = 0; RGB_AREA < 100; RGB_AREA++)
		{
			key = atoi(Original_RGB[RGB_AREA]);
			DB_Analysis::ListNode *Node = Hash_table[key][RGB_AREA];
			while (Node != NULL){
				image_number = Node->image_name;
				count = atoi(DB_array[image_number][102]) + 1;
				DB_array[image_number][102].Format("%d", count);
				Node = Node->next;
			}
			delete Node;
		}

		CString result_time;
		for (int i = 0; i <= number_array; i++)
		{
			if (max < atoi(DB_array[i][102]))
			{
				max = atoi(DB_array[i][102]);
				final_original_file_path.Format(DB_array[i][0]);
				result_time.Format(_T("%.02f"), (float)atoi(DB_array[i][1])*(float)0.0667);
			}
		}

		r_pImage = cvLoadImage(final_original_file_path, 1);
		second_path.SetWindowText(final_original_file_path);
		final_time.SetWindowTextA(result_time + "��");
		Invalidate(false);
		UpdateData(false);
	}
	else{
		::AfxMessageBox(_T("���̹����� �������ּ���."));
	}
}
