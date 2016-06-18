// DB_Analysis.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "Analysis.h"
#include "DB_Analysis.h"
#include "afxdialogex.h"
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<string>

CString **DB_array; // DB�� �迭 ����.
DB_Analysis::ListNode *Hash_table[256][100] = { NULL };
int number_array = 0; // DB_array�� ���� ��.

IMPLEMENT_DYNAMIC(DB_Analysis, CDialogEx)

DB_Analysis::DB_Analysis(CWnd* pParent /*=NULL*/)
: CDialogEx(DB_Analysis::IDD, pParent)
{

}

DB_Analysis::~DB_Analysis()
{
}

void DB_Analysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, C_vidieo_name);
	DDX_Control(pDX, IDC_EDIT3, C_state);
	DDX_Control(pDX, IDC_EDIT2, Same_count);
	DDX_Control(pDX, IDC_EDIT4, C_time);
}


BEGIN_MESSAGE_MAP(DB_Analysis, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPEN, &DB_Analysis::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_SPILT, &DB_Analysis::OnBnClickedBtnSpilt)
	ON_BN_CLICKED(IDC_BTN_SAME, &DB_Analysis::OnBnClickedBtnSame)
	ON_BN_CLICKED(IDC_BTN_HASH, &DB_Analysis::OnBnClickedBtnHash)
END_MESSAGE_MAP()
// DB_Analysis �޽��� ó�����Դϴ�.

void DB_Analysis::OnBnClickedBtnOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog fd(TRUE);
	if (fd.DoModal() == IDOK)
	{
		MoviePath = fd.GetPathName();// ���� ������ ������ ���
		CString movie_new_path(_T("c:\\test.mp4"));
		BOOL copyfile = CopyFile(MoviePath, movie_new_path, FALSE);
		C_vidieo_name.SetWindowTextA(_T(MoviePath));
		UpdateData(false);
	}
}


void DB_Analysis::OnBnClickedBtnSpilt()
{
	system("extract.bat");
	C_state.SetWindowTextA(_T("�̹��� �и� �Ϸ�"));
	UpdateData(false);
}


void DB_Analysis::OnBnClickedBtnSame()
{
	Count_File = 0;
	C_state.SetWindowTextA(_T("�ߺ�ó�� ������..."));
	UpdateData(false);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(_T("C:\\output\\*.bmp"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;
		Count_File++;
	}
	finder.Close();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString first[103]; // ó�� �̹��� ���� �迭
	CString second[103]; // �� �̹��� ���� �迭
	IplImage *src_image;// �̹��� �ҷ� �ð�.
	int temp_sum[100] = { 0, }; //�Ͻ��� ��հ� ���� ���.

	CString new_image_path("C:\\output\\");
	char cut_file_name[13];
	sprintf(cut_file_name, "%05d.bmp", 1);
	DB_array = new CString*[Count_File];
	for (int i = 0; i < Count_File; i++)
	{
		DB_array[i] = new CString[103];
	}
	first[0] = new_image_path + cut_file_name;
	first[1].Format("%d", 1);

	src_image = cvLoadImage(first[0]);

	///������ 10 x 10���� ���� �� ��ĭ�� ������ ��հ� ����.
	int real_width, real_height;
	CvScalar temp_scalar;

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
					temp_scalar = cvGet2D(src_image, real_height, real_width);
					temp_sum[x_block + 10 * y_block] += (temp_scalar.val[0] + temp_scalar.val[1] + temp_scalar.val[2]) / 3.0f;
				}
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		temp_sum[i] = temp_sum[i] / 3185;
		first[i + 2].Format("%d", temp_sum[i]);
	}
	for (int i = 0; i < 102; i++)
	{
		DB_array[0][i].Format(first[i]);
	}
	cvReleaseImage(&src_image);

	for (int j = 2; j <= Count_File; j++)
	{
		sprintf(cut_file_name, "%05d.bmp", j);
		second[0] = new_image_path + cut_file_name;
		second[1].Format("%d", j);
		src_image = cvLoadImage(second[0]);
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
					    temp_scalar = cvGet2D(src_image, real_height, real_width);
						temp_sum[x_block + 10 * y_block] += (temp_scalar.val[0] + temp_scalar.val[1] + temp_scalar.val[2]) / 3.0f;
					}
				}
			}
		}
		for (int i = 0; i < 100; i++)
		{
			temp_sum[i] = temp_sum[i] / 3185;
			second[i + 2].Format("%d", temp_sum[i]);
		}
		cvReleaseImage(&src_image);

		int count_differnet = 0;
		for (int count = 0; count < 100; count++)
		{
			if (atoi(first[2 + count]) != temp_sum[count])
				count_differnet++;
			if (count_differnet>5) break;
		}

		if (count_differnet > 5)
		{
			number_array++;
			for (int i = 0; i < 102; i++)
			{
				DB_array[number_array][i].Format(second[i]);
				first[i].Format(second[i]);
			}
		}
	}
	C_state.SetWindowTextA("�ߺ�ó�� �Ϸ�");
	CString count, time;
	count.Format("%d ��", Count_File - number_array);
	time.Format("%f ��", (float)(Count_File*0.06667));
	Same_count.SetWindowTextA(count);
	C_time.SetWindowTextA(time);
	UpdateData(false);
}


void DB_Analysis::OnBnClickedBtnHash()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j <= number_array; j++)
		{
			int key = atoi(DB_array[j][2 + i]);
			if (Hash_table[key][i] == NULL)
			{
				Hash_table[key][i] = new ListNode(j);
			}
			else{
				ListNode *ptr = Hash_table[key][i];
				while (ptr->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = new ListNode(j);
			}
		}
	}
	C_state.SetWindowTextA("��� �Ϸ�");
	UpdateData(false);
}
