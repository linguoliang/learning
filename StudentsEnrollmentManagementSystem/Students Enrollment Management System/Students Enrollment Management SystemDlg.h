
// Students Enrollment Management SystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "DialogClasses.h"
#include "DialogCourses.h"
#include "DialogStudents.h"
#include "AppControl.h"
#include "Utilities.h"

// CStudentsEnrollmentManagementSystemDlg 对话框
class CStudentsEnrollmentManagementSystemDlg : public CDialogEx
{
// 构造
public:
	CStudentsEnrollmentManagementSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STUDENTSENROLLMENTMANAGEMENTSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void On32776About();
    CTabCtrl m_tabctrl;
    CDialogStudents m_page_students;
    CDialogClasses m_page_classes;
    CDialogCourses m_page_courses;
    int m_CurSelTab;
    CDialog* pDialog[3];
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void On32772Exit();
private:
    AppControl control;
    void DoDataInit();
};
