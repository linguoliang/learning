#pragma once

#include <sstream>
#include "Utilities.h"
#include "CourseItem.h"
#include "afxwin.h"

// DialogCourseInfo 对话框

class DialogCourseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCourseInfo)

public:
	DialogCourseInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCourseInfo();
    virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_COURSES_INFO };

    ViewInfo viewInfo;
    CourseItem courseItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
    CEdit m_editControlId;
    CEdit m_editControlName;
    CEdit m_editControlNumber;
    CEdit m_editControlSchool;
    CButton m_buttonOK;
    CWnd* cParent;
public:
    afx_msg void OnBnClickedOk();
};
