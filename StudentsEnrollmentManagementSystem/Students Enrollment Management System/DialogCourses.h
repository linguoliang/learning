#pragma once

#include <sstream>
#include "Utilities.h"
#include "AppControl.h"
#include "Courses.h"
#include "CourseItem.h"
#include "DialogCourseInfo.h"
#include "afxcmn.h"


// CDialogCourses 对话框

class CDialogCourses : public CDialogEx
{
    DECLARE_DYNAMIC(CDialogCourses)

public:
    CDialogCourses(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDialogCourses();

// 对话框数据
    enum { IDD = IDD_DIALOG_COURSES };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
private:
    CListCtrl m_listctrl;

    // 指向Control
    AppControl* pAppControl;
    void DoDataInit();
    void AddItem(CListCtrl &ctrl, StudentSetItem studentSetItem);
    void AdjustColumnWidth();
    int getSelectedItemIndex();
    std::string getSelectedItemColumn(int cloumn);
public:
    afx_msg void OnBnClickedButtonCoursesInfo();
    afx_msg void OnBnClickedButtonCoursesUpdate();
    afx_msg void OnBnClickedButtonCoursesDeleteselected();
    afx_msg void OnBnClickedButtonCoursesAdd();
protected:
    afx_msg LRESULT OnCoursesDataInit(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdateCourseinfo(WPARAM wParam, LPARAM lParam);
};
