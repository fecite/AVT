
// AVTCameraManipulateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CAVTCameraManipulateDlg 对话框
class CAVTCameraManipulateDlg : public CDialogEx
{
// 构造
public:
	CAVTCameraManipulateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AVTCAMERAMANIPULATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnInitCamera();
	afx_msg void OnBnClickedBtnSnap();
	CListBox m_ctlListBox;

	CComboBox m_comboCameraList;
	CString m_strComboCameraList;
	VmbError_t vmbErr;
	VmbUint32_t nCameraCount;
	VmbCameraInfo_t *pCameras;
	VmbHandle_t hCamera;
	afx_msg void OnBnClickedBtnConnectCamera();
};
