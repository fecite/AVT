
// AVTCameraManipulateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CAVTCameraManipulateDlg �Ի���
class CAVTCameraManipulateDlg : public CDialogEx
{
// ����
public:
	CAVTCameraManipulateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AVTCAMERAMANIPULATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
