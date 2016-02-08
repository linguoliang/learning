// DialogClasses.cpp : 实现文件
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogClasses.h"
#include "afxdialogex.h"


// CDialogClasses 对话框

IMPLEMENT_DYNAMIC(CDialogClasses, CDialogEx)

CDialogClasses::CDialogClasses(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogClasses::IDD, pParent)
{
    
}

CDialogClasses::~CDialogClasses()
{
}

void CDialogClasses::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BOOL CDialogClasses::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CRect rc;
    GetClientRect(rc);
    rc.top += 45;
    rc.left += 5;
    rc.right -= 5;
    rc.bottom -= 45;
    m_listctrl.MoveWindow(&rc);

    m_listctrl.InsertColumn(0, L"班级编号");
    m_listctrl.SetColumnWidth(0, 60);

    m_listctrl.InsertColumn(1, L"班级名称");
    m_listctrl.SetColumnWidth(1, 80);

    m_listctrl.InsertColumn(2, L"班级人数");
    m_listctrl.SetColumnWidth(2, 80);

    m_listctrl.InsertColumn(3, L"所在学院");
    m_listctrl.SetColumnWidth(3, 80);

    m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDialogClasses, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CLASSES_ADD, &CDialogClasses::OnBnClickedButtonClassesAdd)
    ON_BN_CLICKED(IDC_BUTTON_CLASSES_DELETESELECTED, &CDialogClasses::OnBnClickedButtonClassesDeleteselected)
    ON_BN_CLICKED(IDC_BUTTON_CLASSES_UPDATE, &CDialogClasses::OnBnClickedButtonClassesUpdate)
    ON_BN_CLICKED(IDC_BUTTON_CLASSES_INFO, &CDialogClasses::OnBnClickedButtonClassesInfo)
    ON_MESSAGE(WM_Classes_Data_Init, &CDialogClasses::OnClassesDataInit)
    ON_MESSAGE(WM_Update_ClassInfo, &CDialogClasses::OnUpdateClassinfo)
END_MESSAGE_MAP()


// CDialogClasses 消息处理程序


void CDialogClasses::LoadData()
{
}


void CDialogClasses::DoDataInit()
{
    m_listctrl.DeleteAllItems();

    Classes& classes = pAppControl->getClasses();
    for (StudentSetItem studentSetItem : classes.getSet())
    {

        AddItem(m_listctrl, studentSetItem);
    }
}

void CDialogClasses::AddItem(CListCtrl &ctrl, StudentSetItem studentSetItem)
{
    int row = ctrl.GetItemCount();
    int column = 0;

    LVITEM lvItem_Id;
    lvItem_Id.iItem = row;
    lvItem_Id.iSubItem = column;
    lvItem_Id.pszText = stringToLPWSTR(std::to_string(studentSetItem.getId()));
    lvItem_Id.mask = LVFIF_TEXT;
    ctrl.InsertItem(&lvItem_Id);

    column++;
    LVITEM lvItem_Name;
    lvItem_Name.iItem = row;
    lvItem_Name.iSubItem = column;
    lvItem_Name.pszText = stringToLPWSTR(studentSetItem.getName());
    lvItem_Name.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_Name);

    column++;
    LVITEM lvItem_Number;
    lvItem_Number.iItem = row;
    lvItem_Number.iSubItem = column;
    lvItem_Number.pszText = stringToLPWSTR(std::to_string(studentSetItem.getNumberOfPeople()));
    lvItem_Number.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_Number);

    column++;
    LVITEM lvItem_School;
    lvItem_School.iItem = row;
    lvItem_School.iSubItem = column;
    lvItem_School.pszText = stringToLPWSTR(studentSetItem.getSchool());
    lvItem_School.mask = LVFIF_TEXT;
    ctrl.SetItem(&lvItem_School);
}


void CDialogClasses::AdjustColumnWidth()
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

int CDialogClasses::getSelectedItemIndex()
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


std::string CDialogClasses::getSelectedItemColumn(int cloumn)
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


void CDialogClasses::OnBnClickedButtonClassesAdd()
{
    DialogClassInfo dialogClassInfo(FromHandle(m_hWnd));
    dialogClassInfo.viewInfo = { 0, Newing };
    dialogClassInfo.DoModal();
}


void CDialogClasses::OnBnClickedButtonClassesDeleteselected()
{
    //todo no yet finished
    //if the student is involed in classes or courses.
    int id;
    std::stringstream(getSelectedItemColumn(0)) >> id;
    pAppControl->deleteClassById(id);

    m_listctrl.DeleteItem(getSelectedItemIndex());
}


void CDialogClasses::OnBnClickedButtonClassesUpdate()
{
    int nItem;
    std::string retStr = getSelectedItemColumn(0);
    if (retStr != std::string())
    {
        std::stringstream(getSelectedItemColumn(0)) >> nItem;
        DialogClassInfo dialogClassInfo(FromHandle(m_hWnd));;
        dialogClassInfo.viewInfo = { nItem, Editing };
        dialogClassInfo.classItem = pAppControl->findClassById(nItem);
        dialogClassInfo.DoModal();
    }
}


void CDialogClasses::OnBnClickedButtonClassesInfo()
{
    int nItem;
    std::string retStr = getSelectedItemColumn(0);
    if (retStr != std::string())
    {
        std::stringstream(getSelectedItemColumn(0)) >> nItem;
        DialogClassInfo dialogClassInfo(FromHandle(m_hWnd));;
        dialogClassInfo.viewInfo = { nItem, Viewing };
        dialogClassInfo.classItem = pAppControl->findClassById(nItem);
        dialogClassInfo.DoModal();
    }
}


afx_msg LRESULT CDialogClasses::OnClassesDataInit(WPARAM wParam, LPARAM lParam)
{
    pAppControl = reinterpret_cast<AppControl*>(lParam);

    DoDataInit();
    AdjustColumnWidth();

    return 0;
}


afx_msg LRESULT CDialogClasses::OnUpdateClassinfo(WPARAM wParam, LPARAM lParam)
{
    ViewInfo* viewInfo = reinterpret_cast<ViewInfo*>(wParam);

    ClassItem* classItem = reinterpret_cast<ClassItem*>(lParam);

    if (viewInfo->mode == Newing)
    {
        pAppControl->addClass(*classItem);
    }
    else if (viewInfo->mode == Editing)
    {
        pAppControl->updateClass(*classItem);
    }

    //data is changed, so update controls.
    UpdateData(FALSE);
    DoDataInit();
    AdjustColumnWidth();

    return 0;
}
