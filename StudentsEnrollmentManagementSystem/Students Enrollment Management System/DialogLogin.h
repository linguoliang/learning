#pragma once
#include "afxwin.h"
#include "Students Enrollment Management SystemDlg.h"


// CDialogLogin 对话框

class CDialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogin)

public:
	CDialogLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
    HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
    // 指向Control
    AppControl* pAppControl;

    CEdit m_editControlUserName;
    CEdit m_editControlPassword;
public:
    afx_msg void OnBnClickedLogin();
};
