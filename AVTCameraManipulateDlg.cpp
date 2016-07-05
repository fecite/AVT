
// AVTCameraManipulateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AVTCameraManipulate.h"
#include "AVTCameraManipulateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAVTCameraManipulateDlg 对话框




CAVTCameraManipulateDlg::CAVTCameraManipulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAVTCameraManipulateDlg::IDD, pParent)
	, m_strComboCameraList(_T(""))
	, nCameraCount(0)
	, pCameras(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVTCameraManipulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctlListBox);
	DDX_Control(pDX, IDC_COMBO_CAMERA_LIST, m_comboCameraList);
	DDX_CBString(pDX, IDC_COMBO_CAMERA_LIST, m_strComboCameraList);
}

BEGIN_MESSAGE_MAP(CAVTCameraManipulateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INIT_CAMERA, &CAVTCameraManipulateDlg::OnBnClickedBtnInitCamera)
	ON_BN_CLICKED(IDC_BTN_SNAP, &CAVTCameraManipulateDlg::OnBnClickedBtnSnap)
END_MESSAGE_MAP()


// CAVTCameraManipulateDlg 消息处理程序

BOOL CAVTCameraManipulateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CenterWindow();
	ShowWindow(SW_NORMAL);

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAVTCameraManipulateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAVTCameraManipulateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAVTCameraManipulateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAVTCameraManipulateDlg::OnBnClickedBtnInitCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	bool bGige;
	vmbErr = VmbFeatureBoolGet(gVimbaHandle, "GeVTLIsPresent", &bGige);
	if (VmbErrorSuccess == vmbErr)
	{
		if (true == bGige)
		{
			vmbErr = VmbFeatureCommandRun(gVimbaHandle, "GevDiscoveryAllOnce");
		}
	}
	if (VmbErrorSuccess == vmbErr)
	{
		vmbErr = VmbCamerasList(NULL, 0, &nCameraCount, sizeof(*pCameras));

		if (VmbErrorSuccess == vmbErr)
		{
			pCameras = (VmbCameraInfo_t *)malloc(nCameraCount*sizeof(*pCameras));
			vmbErr = VmbCamerasList(pCameras, nCameraCount, &nCameraCount, sizeof(*pCameras));
			for (VmbUint32_t i=0; i<nCameraCount; ++i)
			{
				//printf("%s\n", pCameras[i].cameraName);
				m_comboCameraList.AddString(pCameras[i].cameraIdString);
			}
		}
	}
}


void CAVTCameraManipulateDlg::OnBnClickedBtnSnap()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int nSel = m_comboCameraList.GetCurSel();
	m_comboCameraList.GetLBText(nSel, (LPTSTR)&m_strComboCameraList);
	if (VmbErrorSuccess == VmbCameraOpen(m_strComboCameraList, VmbAccessModeFull, &hCamera))
	{
		m_ctlListBox.AddString("Camera opened!");
	}
}
