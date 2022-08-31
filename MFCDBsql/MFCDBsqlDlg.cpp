
// MFCDBsqlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCDBsql.h"
#include "MFCDBsqlDlg.h"
#include "afxdialogex.h"
#include "CMysqlController.h"

#include "CMyBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDBsqlDlg 대화 상자



CMFCDBsqlDlg::CMFCDBsqlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDBSQL_DIALOG, pParent)
	, m_ed_bookname_val(_T(""))
	, m_ed_author_val(_T(""))
	, m_ed_price_val(_T(""))
	, m_ed_other_val(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDBsqlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_BOOKNAME, m_ed_bookname_info);
	DDX_Control(pDX, IDC_ED_AUTHOR, m_ed_author_info);
	DDX_Control(pDX, IDC_ED_PRICE, m_ed_price_info);
	DDX_Control(pDX, IDC_ED_OTHER, m_ed_other_info);
	DDX_Text(pDX, IDC_ED_BOOKNAME, m_ed_bookname_val);
	DDX_Text(pDX, IDC_ED_AUTHOR, m_ed_author_val);
	DDX_Text(pDX, IDC_ED_PRICE, m_ed_price_val);
	DDX_Text(pDX, IDC_ED_OTHER, m_ed_other_val);
	DDX_Control(pDX, IDC_LIST_box, m_list);
}

BEGIN_MESSAGE_MAP(CMFCDBsqlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_SELECT, &CMFCDBsqlDlg::OnBnClickedBtSelect)
	ON_BN_CLICKED(IDC_BT_INSERT, &CMFCDBsqlDlg::OnBnClickedBtInsert)
END_MESSAGE_MAP()


// CMFCDBsqlDlg 메시지 처리기

BOOL CMFCDBsqlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, _T("id"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("bookname"), LVCFMT_LEFT,100);
	m_list.InsertColumn(2, _T("author"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("price"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T("other"), LVCFMT_LEFT, 100);

	CString sampleName[5]={m_ed_bookname_val,m_ed_author_val,m_ed_price_val,m_ed_other_val};

	for (int i = 0; i < 5; i++)
	{
		m_list.InsertItem(i, m_ed_bookname_val);
	}
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



void CMFCDBsqlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCDBsqlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCDBsqlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDBsqlDlg::OnBnClickedBtSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMysqlController conn;
	vector<CMyBook*> result;
	if (conn.SelectQuery("select * from TB_Book", result) != true)
	{
		return;
	}

	m_list.DeleteAllItems();

	for(int i = 0 ; i < result.size() ; i++)
	{
		CString id, price;
		id.Format("%d", result.at(i)->id);
		price.Format("%d", result.at(i)->price);
		m_list.InsertItem(i, id);
		m_list.SetItem(i, 1, LVIF_TEXT, result.at(i)->bookname, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 2, LVIF_TEXT, result.at(i)->author, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 3, LVIF_TEXT, price, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 4, LVIF_TEXT, result.at(i)->other, NULL, NULL, NULL, NULL);
	}


	int size = result.size();
	for (int i = 0; i < size; i++)
	{
		delete result.at(i);
	}
	

}



void CMFCDBsqlDlg::OnBnClickedBtInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	CMysqlController conn;
	CString tmp;
	vector<CMyBook*> result;
	if (conn.SelectQuery("select * from TB_Book", result) != true)
	{
		return;
	}

	m_list.DeleteAllItems();

	for (int i = 0; i < result.size(); i++)
	{
		CString id, price;
		id.Format("%d", result.at(i)->id);
		price.Format("%d", result.at(i)->price);
		m_list.InsertItem(i, id);
		m_list.SetItem(i, 1, LVIF_TEXT, result.at(i)->bookname, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 2, LVIF_TEXT, result.at(i)->author, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 3, LVIF_TEXT, price, NULL, NULL, NULL, NULL);
		m_list.SetItem(i, 4, LVIF_TEXT, result.at(i)->other, NULL, NULL, NULL, NULL);
	}


	int size = result.size();
	for (int i = 0; i < size; i++)
	{
		delete result.at(i);
	}


	tmp = _T("insert into TB_book(bookname, author, price, other) values('");
	tmp += m_ed_bookname_val;
	tmp += _T("', '");
	tmp += m_ed_author_val;
	tmp += _T("',");
	tmp += m_ed_price_val;

	if(m_ed_other_val == _T(""))
	{
		tmp += _T(", NULL");
	}
	else
	{
		tmp += _T(", '");
		tmp += m_ed_other_val;
		tmp += _T("'");
	}
	tmp += _T(")");

	if (conn.InsertQuery(LPSTR(LPCTSTR(tmp))) == true)
	{
		AfxMessageBox(_T("성공"));
	}
	else
	{
		AfxMessageBox(_T("실패"));
	}
	


	//SELECT

	

	
}
