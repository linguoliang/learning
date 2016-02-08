
// Students Enrollment Management SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "Students Enrollment Management SystemDlg.h"
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
public:
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


// CStudentsEnrollmentManagementSystemDlg 对话框



CStudentsEnrollmentManagementSystemDlg::CStudentsEnrollmentManagementSystemDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CStudentsEnrollmentManagementSystemDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CStudentsEnrollmentManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_tabctrl);
}

BEGIN_MESSAGE_MAP(CStudentsEnrollmentManagementSystemDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_COMMAND(ID_32776_About, &CStudentsEnrollmentManagementSystemDlg::On32776About)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CStudentsEnrollmentManagementSystemDlg::OnTcnSelchangeTab1)
    ON_COMMAND(ID_32772_Exit, &CStudentsEnrollmentManagementSystemDlg::On32772Exit)
END_MESSAGE_MAP()


// CStudentsEnrollmentManagementSystemDlg 消息处理程序

BOOL CStudentsEnrollmentManagementSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。
    CMenu* cMenu = new CMenu;
    cMenu->LoadMenu(MAKEINTRESOURCE(IDR_MENU1));
    this->SetMenu(cMenu);

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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO:  在此添加额外的初始化代码
    m_tabctrl.InsertItem(0, L"学生管理");
    m_tabctrl.InsertItem(1, L"课程管理");
    m_tabctrl.InsertItem(2, L"班级管理");

    m_page_students.Create(IDD_DIALOG_STUDENTS, &m_tabctrl);
    m_page_courses.Create(IDD_DIALOG_COURSES, &m_tabctrl);
    m_page_classes.Create(IDD_DIALOG_CLASSES, &m_tabctrl);

    CRect rc;
    m_tabctrl.GetClientRect(rc);
    rc.top += 22;
    rc.bottom -= 2;
    rc.left += 0;
    rc.right -= 0;
    m_page_students.MoveWindow(&rc);
    m_page_courses.MoveWindow(&rc);
    m_page_classes.MoveWindow(&rc);

    pDialog[0] = &m_page_students;
    pDialog[1] = &m_page_courses;
    pDialog[2] = &m_page_classes;

    //显示初始页面
    pDialog[0]->ShowWindow(SW_SHOW);
    pDialog[1]->ShowWindow(SW_HIDE);
    pDialog[2]->ShowWindow(SW_HIDE);

    //保存当前选择
    m_CurSelTab = 0;

    DoDataInit();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentsEnrollmentManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentsEnrollmentManagementSystemDlg::OnPaint()
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
HCURSOR CStudentsEnrollmentManagementSystemDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CStudentsEnrollmentManagementSystemDlg::On32776About()
{
    CAboutDlg dlg;
    dlg.DoModal();
}


void CStudentsEnrollmentManagementSystemDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    m_CurSelTab = m_tabctrl.GetCurSel();
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
    *pResult = 0;
}


void CStudentsEnrollmentManagementSystemDlg::On32772Exit()
{
    this->SendMessage(WM_CLOSE);
}

void CStudentsEnrollmentManagementSystemDlg::DoDataInit()
{
    //If you want to send message to another object, HWND must be defined.
    ::SendMessage(m_page_students, WM_Students_Data_Init, 0, reinterpret_cast<LPARAM>(&control));
    ::SendMessage(m_page_courses, WM_Courses_Data_Init, 0, reinterpret_cast<LPARAM>(&control));
    ::SendMessage(m_page_classes, WM_Classes_Data_Init, 0, reinterpret_cast<LPARAM>(&control));
}
