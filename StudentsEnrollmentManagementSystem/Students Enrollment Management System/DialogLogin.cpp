// DialogLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogLogin.h"
#include "afxdialogex.h"


// CDialogLogin 对话框

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLogin::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIconW(IDI_ICON1);
}

CDialogLogin::~CDialogLogin()
{
}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_USERNAME, m_editControlUserName);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editControlPassword);
}

BOOL CDialogLogin::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDialogLogin, CDialogEx)
    ON_BN_CLICKED(ID_LOGIN, &CDialogLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CDialogLogin 消息处理程序


void CDialogLogin::OnBnClickedLogin()
{
    //todo finish login
    CString cstringBuf;
    m_editControlUserName.GetWindowTextW(cstringBuf);
    std::string name = CStringTostring(cstringBuf);

    m_editControlPassword.GetWindowTextW(cstringBuf);
    std::string password = CStringTostring(cstringBuf);

    //User user;
    //user.setName(name);
    //user.setPassword(password);

    //if (pAppControl->verifyUser(user))
    //{
    //    AfxGetMainWnd()->SendMessage(WM_CLOSE);

    //    CStudentsEnrollmentManagementSystemDlg dlg;
    //    dlg.DoModal();
    //}
    //else
    //{
    //    MessageBox(L"用户名或密码错误！");
    //}
}
