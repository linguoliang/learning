// DialogStudents.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogStudents.h"
#include "afxdialogex.h"


// CDialogStudents 对话框

IMPLEMENT_DYNAMIC(CDialogStudents, CDialogEx)

CDialogStudents::CDialogStudents(CWnd* pParent /*=NULL*/)
: CDialogEx(CDialogStudents::IDD, pParent)
{
    pAppControl = nullptr;
}

CDialogStudents::~CDialogStudents()
{
}

void CDialogStudents::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BOOL CDialogStudents::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CRect rc;
    GetClientRect(rc);
    rc.top += 45;
    rc.left += 5;
    rc.right -= 5;
    rc.bottom -= 45;
    m_listctrl.MoveWindow(&rc);

    m_listctrl.InsertColumn(0, L"学号");
    m_listctrl.SetColumnWidth(0, 60);

    m_listctrl.InsertColumn(1, L"姓名");
    m_listctrl.SetColumnWidth(1, 80);

    m_listctrl.InsertColumn(2, L"性别");
    m_listctrl.SetColumnWidth(2, 50);

    m_listctrl.InsertColumn(3, L"学院");
    m_listctrl.SetColumnWidth(3, 60);

    m_listctrl.InsertColumn(4, L"类型");
    m_listctrl.SetColumnWidth(4, 50);

    m_listctrl.InsertColumn(5, L"学校住址");
    m_listctrl.SetColumnWidth(5, 200);

    m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDialogStudents, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_STUDENTS_ADD, &CDialogStudents::OnBnClickedButtonStudentsAdd)
    ON_BN_CLICKED(IDC_BUTTON_STUDENTS_INFO, &CDialogStudents::OnBnClickedButtonStudentsInfo)
    ON_BN_CLICKED(IDC_BUTTON_STUDENTS_DELETESELCET, &CDialogStudents::OnBnClickedButtonStudentsDeleteSelcet)
    ON_BN_CLICKED(IDC_BUTTON_STUDENTS_UPDATE, &CDialogStudents::OnBnClickedButtonStudentsUpdate)
    ON_MESSAGE(WM_Update_StudentInfo, &CDialogStudents::OnUpdateStudentinfo)
    ON_MESSAGE(WM_Students_Data_Init, &CDialogStudents::OnStudentsDataInit)
END_MESSAGE_MAP()

// CDialogStudents 消息处理程序


void CDialogStudents::DoDataInit()
{
    m_listctrl.DeleteAllItems();

    AllStudents& students = pAppControl->getStudents();
    for (Student student : students.getSet())
    {
        AddItem(m_listctrl, student);
    }
}

void CDialogStudents::AddItem(CListCtrl &ctrl, Student student)
{
    int row = ctrl.GetItemCount();
    int column = 0;

    LVITEM lvItem_Id;
    lvItem_Id.iItem = row;
    lvItem_Id.iSubItem = column;
    lvItem_Id.pszText = stringToLPWSTR(std::to_string(student.getId()));
    lvItem_Id.mask = LVFIF_TEXT;
    ctrl.InsertItem(&lvItem_Id);

    column++;
    LVITEM lvItem_Name;
    lvItem_Name.iItem = row;
    lvItem_Name.iSubItem = column;
    lvItem_Name.pszText = stringToLPWSTR(student.getLastName() + student.getFirstName());
    lvItem_Name.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_Name);

    column++;
    LVITEM lvItem_Sex;
    lvItem_Sex.iItem = row;
    lvItem_Sex.iSubItem = column;
    lvItem_Sex.pszText = stringToLPWSTR(student.getSex());
    lvItem_Sex.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_Sex);

    column++;
    LVITEM lvItem_School;
    lvItem_School.iItem = row;
    lvItem_School.iSubItem = column;
    lvItem_School.pszText = stringToLPWSTR(student.getSchool());
    lvItem_School.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_School);

    //todo doesn't work
    std::string studentType = getStudentType(&student);
    column++;
    LVITEM lvItem_Type;
    lvItem_Type.iItem = row;
    lvItem_Type.iSubItem = column;
    lvItem_Type.pszText = stringToLPWSTR(studentType);
    lvItem_Type.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_Type);

    column++;
    LVITEM lvItem_CampusAddress;
    lvItem_CampusAddress.iItem = row;
    lvItem_CampusAddress.iSubItem = column;
    lvItem_CampusAddress.pszText = stringToLPWSTR(student.getCampusAddress());
    lvItem_CampusAddress.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_CampusAddress);
}

void CDialogStudents::AdjustColumnWidth()
{
    // update control
    CHeaderCtrl* pHeaderCtrl = m_listctrl.GetHeaderCtrl();

    int nColumnCount = pHeaderCtrl->GetItemCount();

    for (int i = 0; i < nColumnCount; i++)
    {
        m_listctrl.SetColumnWidth(i, LVSCW_AUTOSIZE);
        int nColumnWidth = m_listctrl.GetColumnWidth(i);
        m_listctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        int nHeaderWidth = m_listctrl.GetColumnWidth(i);
        m_listctrl.SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
    }

    m_listctrl.Invalidate();
}

int CDialogStudents::getSelectedItemIndex()
{
    if (m_listctrl.GetItemCount() == 0)
    {
        MessageBox(L"没有数据");
        return m_error;
    }
    else
    {
        for (int i = 0; i < m_listctrl.GetItemCount(); i++)
        {
            if (m_listctrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
            {
                return i;
            }
        }

        return m_error;
    }
}


std::string CDialogStudents::getSelectedItemColumn(int cloumn)
{
    int nItem = getSelectedItemIndex();

    if (nItem == m_error)
    {
        return std::string();
    }
    else
    {
        TCHAR szBuf[1024];
        LVITEM lvItem;
        lvItem.iItem = nItem;
        lvItem.iSubItem = cloumn;
        lvItem.mask = LVIF_TEXT;
        lvItem.pszText = szBuf;
        lvItem.cchTextMax = 1024;
        m_listctrl.GetItem(&lvItem);

#pragma warning(push)
#pragma warning(disable : 4927)

        return CW2A(lvItem.pszText);

#pragma warning(pop)
    }
}


void CDialogStudents::OnBnClickedButtonStudentsDeleteSelcet()
{
    //todo no yet finished
    //if the student is involed in classes or courses.
    int id;
    std::stringstream(getSelectedItemColumn(0)) >> id;
    pAppControl->deleteStudentById(id);

    m_listctrl.DeleteItem(getSelectedItemIndex());
}


void CDialogStudents::OnBnClickedButtonStudentsInfo()
{
    int nItem;
    std::string retStr = getSelectedItemColumn(0);
    if (retStr != std::string())
    {
        std::stringstream(getSelectedItemColumn(0)) >> nItem;
        DialogStudentInfo dialogStudentInfo(FromHandle(m_hWnd));
        dialogStudentInfo.viewInfo = { nItem, Viewing };
        dialogStudentInfo.student = pAppControl->findStudentById(nItem);
        dialogStudentInfo.DoModal();
    }
}

void CDialogStudents::OnBnClickedButtonStudentsAdd()
{
    DialogStudentInfo dialogStudentInfo(FromHandle(m_hWnd));
    dialogStudentInfo.viewInfo = { 0, Newing };
    dialogStudentInfo.DoModal();
}

void CDialogStudents::OnBnClickedButtonStudentsUpdate()
{
    int nItem;
    std::string retStr = getSelectedItemColumn(0);
    if (retStr != std::string())
    {
        std::stringstream(getSelectedItemColumn(0)) >> nItem;
        DialogStudentInfo dialogStudentInfo(this);
        dialogStudentInfo.viewInfo = { nItem, Editing };
        dialogStudentInfo.student = pAppControl->findStudentById(nItem);
        dialogStudentInfo.DoModal();
    }
}


afx_msg LRESULT CDialogStudents::OnUpdateStudentinfo(WPARAM wParam, LPARAM lParam)
{
    ViewInfo* viewInfo = reinterpret_cast<ViewInfo*>(wParam);
    
    //todo determine student type
    Student* student = reinterpret_cast<Student*>(lParam);

    if (viewInfo->mode == Newing)
    {
        pAppControl->addStudent(*student);
    }
    else if (viewInfo->mode == Editing)
    {
        pAppControl->updateStudnet(*student);
    }

    //data is changed, so update controls.
    UpdateData(FALSE);
    DoDataInit();
    AdjustColumnWidth();

    return 0;
}


afx_msg LRESULT CDialogStudents::OnStudentsDataInit(WPARAM wParam, LPARAM lParam)
{
    pAppControl = reinterpret_cast<AppControl*>(lParam);
    
    DoDataInit();
    AdjustColumnWidth();

    return 0;
}
