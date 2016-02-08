// DialogCourseInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogCourseInfo.h"
#include "afxdialogex.h"


// DialogCourseInfo 对话框

IMPLEMENT_DYNAMIC(DialogCourseInfo, CDialogEx)

DialogCourseInfo::DialogCourseInfo(CWnd* pParent /*=NULL*/)
    : CDialogEx(DialogCourseInfo::IDD, pParent)
{
    cParent = pParent;
}

DialogCourseInfo::~DialogCourseInfo()
{
}

void DialogCourseInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ID, m_editControlId);
    DDX_Control(pDX, IDC_EDIT_NAME, m_editControlName);
    DDX_Control(pDX, IDC_EDIT_NUMBER, m_editControlNumber);
    DDX_Control(pDX, IDC_EDIT_SCHOOL, m_editControlSchool);
    DDX_Control(pDX, IDOK, m_buttonOK);
}

BOOL DialogCourseInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //View or Editing
    if (viewInfo.mode == Viewing || viewInfo.mode == Editing)
    {

        m_editControlId.SetReadOnly(TRUE);

        //Load data
        m_editControlId.SetWindowTextW(stringToLPWSTR(std::to_string(courseItem.getId())));
        m_editControlName.SetWindowTextW(stringToLPWSTR(courseItem.getName()));
        m_editControlNumber.SetWindowTextW(stringToLPWSTR(std::to_string(courseItem.getNumberOfPeople())));
        m_editControlSchool.SetWindowTextW(stringToLPWSTR(courseItem.getSchool()));

        //prepare
        //forbid updating Id,
        //in order to prevent Id collision when having a lots of data.
        m_editControlId.SetReadOnly(TRUE);

        //setup controls viewing mode
        if (viewInfo.mode == Viewing)
        {
            m_editControlName.SetReadOnly(TRUE);
            m_editControlNumber.SetReadOnly(TRUE);
            m_editControlSchool.SetReadOnly(TRUE);
            m_buttonOK.ShowWindow(SW_HIDE);
        }
        //setup controls editing mode
        else if (viewInfo.mode == Editing)
        {

        }
    }
    //todo Updating
    else
    {

    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(DialogCourseInfo, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogCourseInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogCourseInfo 消息处理程序


void DialogCourseInfo::OnBnClickedOk()
{
    CString cstringBuf;

    m_editControlId.GetWindowTextW(cstringBuf);
    int id;
    std::stringstream(CStringTostring(cstringBuf)) >> id;

    m_editControlName.GetWindowTextW(cstringBuf);
    std::string  name = CStringTostring(cstringBuf);

    m_editControlNumber.GetWindowTextW(cstringBuf);
    int number;
    std::stringstream(CStringTostring(cstringBuf)) >> number;

    m_editControlSchool.GetWindowTextW(cstringBuf);
    std::string school = CStringTostring(cstringBuf);
    
    courseItem.setId(id);
    courseItem.setName(name);
    courseItem.setNumberOfPeople(number);
    courseItem.setSchool(school);

    ::SendMessage(cParent->GetSafeHwnd(), WM_Update_CourseInfo, reinterpret_cast<WPARAM>(&viewInfo), reinterpret_cast<LPARAM>(&courseItem));

    CDialogEx::OnOK();
}
