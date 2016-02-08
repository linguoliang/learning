#pragma once

#include <sstream>
#include "Utilities.h"
#include "AppControl.h"
#include "Classes.h"
#include "ClassItem.h"
#include "DialogClassInfo.h"
#include "afxcmn.h"

// CDialogClasses 对话框

class CDialogClasses : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogClasses)

public:
	CDialogClasses(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogClasses();

// 对话框数据
	enum { IDD = IDD_DIALOG_CLASSES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnSize(UINT nType, int cx, int cy);
//    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
private:
    CListCtrl m_listctrl;

    // 指向Control
    AppControl* pAppControl;
    void LoadData();
    void DoDataInit();
    void AddItem(CListCtrl &ctrl, StudentSetItem studentSetItem);
    void AdjustColumnWidth();
    int getSelectedItemIndex();
    std::string getSelectedItemColumn(int cloumn);
public:
    afx_msg void OnBnClickedButtonClassesAdd();
    afx_msg void OnBnClickedButtonClassesDeleteselected();
    afx_msg void OnBnClickedButtonClassesUpdate();
    afx_msg void OnBnClickedButtonClassesInfo();
protected:
    afx_msg LRESULT OnClassesDataInit(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdateClassinfo(WPARAM wParam, LPARAM lParam);
};
