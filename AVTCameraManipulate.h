
// AVTCameraManipulate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAVTCameraManipulateApp:
// �йش����ʵ�֣������ AVTCameraManipulate.cpp
//

class CAVTCameraManipulateApp : public CWinApp
{
public:
	CAVTCameraManipulateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
private:
	VmbError_t vmbError;
};

extern CAVTCameraManipulateApp theApp;