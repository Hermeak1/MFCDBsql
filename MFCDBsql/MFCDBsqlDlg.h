
// MFCDBsqlDlg.h: 헤더 파일
//

#pragma once


// CMFCDBsqlDlg 대화 상자
class CMFCDBsqlDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCDBsqlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDBSQL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtSelect();
	afx_msg void OnBnClickedBtInsert();
	CEdit m_ed_bookname_info;
	CEdit m_ed_author_info;
	CEdit m_ed_price_info;
	CEdit m_ed_other_info;
	CString m_ed_bookname_val;
	CString m_ed_author_val;
	CString m_ed_price_val;
	CString m_ed_other_val;
	CListCtrl m_list;
	CMFCDBsqlDlg* dlgPtr;
	void SetParentPtr(CMFCDBsqlDlg* dlg);

};
