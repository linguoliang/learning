// DialogStudentInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogStudentInfo.h"
#include "afxdialogex.h"


// DialogStudentInfo 对话框

IMPLEMENT_DYNAMIC(DialogStudentInfo, CDialogEx)

DialogStudentInfo::DialogStudentInfo(CWnd* pParent /*=NULL*/)
    : CDialogEx(DialogStudentInfo::IDD, pParent)
{
    cParent = pParent;
}

DialogStudentInfo::~DialogStudentInfo()
{
}

void DialogStudentInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ID, m_editControlId);
    DDX_Control(pDX, IDC_EDIT_LASTNAME, m_editControlLastName);
    DDX_Control(pDX, IDC_EDIT_FIRSTNAME, m_editControlFirstName);
    DDX_Control(pDX, IDC_CHECK_M, m_checkBoxMan);
    DDX_Control(pDX, IDC_CHECK_F, m_checkBoxWoman);
    DDX_Control(pDX, IDC_EDIT_SCHOOL, m_editControlSchool);
    DDX_Control(pDX, IDC_EDIT_CAMPUSADDRESS, m_editControlCampusAddress);
    DDX_Control(pDX, IDC_EDIT_HOMEADDRESS, m_editControlHomeAddress);
    DDX_Control(pDX, IDC_EDIT_PC, m_editControlPC);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ADMISSIONTIME, m_dateTimeCtrlAdmissionTime);
    DDX_Control(pDX, IDC_CHECK_UG, m_checkBoxUG);
    DDX_Control(pDX, IDC_CHECK_G, m_checkBoxG);
    DDX_Control(pDX, IDOK, m_buttonOK);
}

BOOL DialogStudentInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //Viewing or Editing
    if (viewInfo.mode == Viewing || viewInfo.mode == Editing)
    {
        //Load data
        m_editControlId.SetWindowTextW(stringToLPWSTR(std::to_string(student.getId())));
        m_editControlLastName.SetWindowTextW(stringToLPWSTR(student.getLastName()));
        m_editControlFirstName.SetWindowTextW(stringToLPWSTR(student.getFirstName()));
        if (student.getSex() == Man)
        {
            m_checkBoxMan.SetCheck(BST_CHECKED);
            m_checkBoxWoman.SetCheck(BST_UNCHECKED);
        }
        else
        {
            m_checkBoxMan.SetCheck(BST_UNCHECKED);
            m_checkBoxWoman.SetCheck(BST_CHECKED);
        }
        m_editControlSchool.SetWindowTextW(stringToLPWSTR(student.getSchool()));
        m_editControlCampusAddress.SetWindowTextW(stringToLPWSTR(student.getCampusAddress()));
        m_editControlHomeAddress.SetWindowTextW(stringToLPWSTR(student.getHomeAddress()));
        m_editControlPC.SetWindowTextW(stringToLPWSTR(student.getProvinceCity()));
        SYSTEMTIME lpTime = tmToSYSTEMTIME(student.getAdmissionTime());
        m_dateTimeCtrlAdmissionTime.SetTime(&lpTime);
        std::string studentType = getStudentType(&student);
        if (studentType == GStudent)
        {
            m_checkBoxG.SetCheck(BST_CHECKED);
            m_checkBoxUG.SetCheck(BST_UNCHECKED);
        }
        else if (studentType == UGStuednt)
        {
            m_checkBoxG.SetCheck(BST_UNCHECKED);
            m_checkBoxUG.SetCheck(BST_CHECKED);
        }

        //prepare
        //forbid updating Id,
        //in order to prevent Id collision when having a lots of data.
        m_editControlId.SetReadOnly(TRUE);

        //setup controls viewing mode
        if (viewInfo.mode == Viewing)
        {
            m_editControlLastName.SetReadOnly(TRUE);
            m_editControlFirstName.SetReadOnly(TRUE);
            m_checkBoxMan.EnableWindow(FALSE);
            m_checkBoxWoman.EnableWindow(FALSE);
            m_editControlSchool.SetReadOnly(TRUE);
            m_editControlCampusAddress.SetReadOnly(TRUE);
            m_editControlHomeAddress.SetReadOnly(TRUE);
            m_editControlPC.SetReadOnly(TRUE);
            m_dateTimeCtrlAdmissionTime.EnableWindow(FALSE);
            m_checkBoxG.EnableWindow(FALSE);
            m_checkBoxUG.EnableWindow(FALSE);
            m_buttonOK.ShowWindow(SW_HIDE);
        }
        //setup controls editing mode
        else if (viewInfo.mode == Editing)
        {
            //todo initializing setting for editing
            //maybe nothing to here?
        }
    }
    else
    {
        //prepare
        m_checkBoxMan.SetCheck(BST_CHECKED);
        m_checkBoxUG.SetCheck(BST_CHECKED);
    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(DialogStudentInfo, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogStudentInfo::OnBnClickedOk)
    ON_BN_CLICKED(IDC_CHECK_M, &DialogStudentInfo::OnClickedCheckM)
    ON_BN_CLICKED(IDC_CHECK_F, &DialogStudentInfo::OnClickedCheckF)
    ON_BN_CLICKED(IDC_CHECK_UG, &DialogStudentInfo::OnClickedCheckUG)
    ON_BN_CLICKED(IDC_CHECK_G, &DialogStudentInfo::OnClickedCheckG)
END_MESSAGE_MAP()


// DialogStudentInfo 消息处理程序



void DialogStudentInfo::OnBnClickedOk()
{
    CString cstringBuf;
    
    m_editControlId.GetWindowTextW(cstringBuf);
    int id;
    std::stringstream(CStringTostring(cstringBuf)) >> id;

    m_editControlFirstName.GetWindowTextW(cstringBuf);
    std::string firstName = CStringTostring(cstringBuf);

    m_editControlLastName.GetWindowTextW(cstringBuf);
    std::string lastName = CStringTostring(cstringBuf);

    std::string sex;
    int checkBoxMan = m_checkBoxMan.GetCheck();
    int checkBoxWoman = m_checkBoxWoman.GetCheck();
    if ((checkBoxMan == BST_CHECKED) && (checkBoxWoman == BST_UNCHECKED))
    {
        sex = Man;
    }
    else if ((checkBoxMan == BST_UNCHECKED) && (checkBoxWoman == BST_CHECKED))
    {
        sex = Woman;
    }

    m_editControlSchool.GetWindowTextW(cstringBuf);
    std::string school = CStringTostring(cstringBuf);

    m_editControlCampusAddress.GetWindowTextW(cstringBuf);
    std::string campusAddress = CStringTostring(cstringBuf);

    m_editControlHomeAddress.GetWindowTextW(cstringBuf);
    std::string homeAddress = CStringTostring(cstringBuf);

    m_editControlPC.GetWindowTextW(cstringBuf);
    std::string provinceCity = CStringTostring(cstringBuf);

    SYSTEMTIME ctrlTime;
    m_dateTimeCtrlAdmissionTime.GetTime(&ctrlTime);
    std::tm admissionTime = SYSTEMTIMETotm(ctrlTime);

    std::string studentType;
    int checkBoxG = m_checkBoxG.GetCheck();
    int checkBoxUG = m_checkBoxUG.GetCheck();
    if ((checkBoxG == BST_CHECKED) && (checkBoxUG == BST_UNCHECKED))
    {
        studentType == GStudent;

        GraduateStudent gs;
        gs.setId(id);
        gs.setFirstName(firstName);
        gs.setLastName(lastName);
        gs.setSex(sex);
        gs.setSchool(school);
        gs.setCampusAddress(campusAddress);
        gs.setHomeAddress(homeAddress);
        gs.setProvinceCity(provinceCity);
        gs.setAdmissionTime(admissionTime);

        ::SendMessage(cParent->GetSafeHwnd(), WM_Update_StudentInfo, reinterpret_cast<WPARAM>(&viewInfo), reinterpret_cast<LPARAM>(&gs));
    }
    else if ((checkBoxG == BST_UNCHECKED) && (checkBoxUG == BST_CHECKED))
    {
        studentType == UGStuednt;

        UndergraduateStudent ugs;
        ugs.setId(id);
        ugs.setFirstName(firstName);
        ugs.setLastName(lastName);
        ugs.setSex(sex);
        ugs.setSchool(school);
        ugs.setCampusAddress(campusAddress);
        ugs.setHomeAddress(homeAddress);
        ugs.setProvinceCity(provinceCity);
        ugs.setAdmissionTime(admissionTime);

        ::SendMessage(cParent->GetSafeHwnd(), WM_Update_StudentInfo, reinterpret_cast<WPARAM>(&viewInfo), reinterpret_cast<LPARAM>(&ugs));
    }

    CDialogEx::OnOK();
}



void DialogStudentInfo::OnClickedCheckM()
{
    m_checkBoxWoman.SetCheck(BST_UNCHECKED);
}


void DialogStudentInfo::OnClickedCheckF()
{
    m_checkBoxMan.SetCheck(BST_UNCHECKED);
}


void DialogStudentInfo::OnClickedCheckUG()
{
    m_checkBoxG.SetCheck(BST_UNCHECKED);
}


void DialogStudentInfo::OnClickedCheckG()
{
    m_checkBoxUG.SetCheck(BST_UNCHECKED);
}
