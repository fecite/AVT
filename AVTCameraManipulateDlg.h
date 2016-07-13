
// AVTCameraManipulateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <fstream>

using namespace std;


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
	VmbFeatureInfo_t *pFeatures;
	VmbInt64_t nWidth;
	VmbInt64_t nPLS;
	afx_msg void OnBnClickedBtnDisconnectCamera();
};

void VMB_CALL FrameDoneCallback( const VmbHandle_t hCamera, VmbFrame_t *pFrame );

CONST char *VmbFeatureDataTypeTransfer (int nType);