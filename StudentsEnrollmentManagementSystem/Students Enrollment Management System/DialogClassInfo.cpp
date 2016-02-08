// DialogClassInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogClassInfo.h"
#include "afxdialogex.h"


// DialogClassInfo 对话框

IMPLEMENT_DYNAMIC(DialogClassInfo, CDialogEx)

DialogClassInfo::DialogClassInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogClassInfo::IDD, pParent)
{
    cParent = pParent;
}

DialogClassInfo::~DialogClassInfo()
{
}

void DialogClassInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ID, m_editControlId);
    DDX_Control(pDX, IDC_EDIT_NAME, m_editControlName);
    DDX_Control(pDX, IDC_EDIT_NUMBER, m_editControlNumber);
    DDX_Control(pDX, IDC_EDIT_SCHOOL, m_editControlSchool);
    DDX_Control(pDX, IDOK, m_buttonOK);
}

BOOL DialogClassInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //View or Editing
    if (viewInfo.mode == Viewing || viewInfo.mode == Editing)
    {
        //Load data
        m_editControlId.SetWindowTextW(stringToLPWSTR(std::to_string(classItem.getId())));
        m_editControlName.SetWindowTextW(stringToLPWSTR(classItem.getName()));
        m_editControlNumber.SetWindowTextW(stringToLPWSTR(std::to_string(classItem.getNumberOfPeople())));
        m_editControlSchool.SetWindowTextW(stringToLPWSTR(classItem.getSchool()));

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

BEGIN_MESSAGE_MAP(DialogClassInfo, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogClassInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogClassInfo 消息处理程序


void DialogClassInfo::OnBnClickedOk()
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

    classItem.setId(id);
    classItem.setName(name);
    classItem.setNumberOfPeople(number);
    classItem.setSchool(school);

    ::SendMessage(cParent->GetSafeHwnd(), WM_Update_ClassInfo, reinterpret_cast<WPARAM>(&viewInfo), reinterpret_cast<LPARAM>(&classItem));
    CDialogEx::OnOK();
}
