
// Practice3-1View.cpp: CPractice31View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice3-1.h"
#endif

#include "Practice3-1Doc.h"
#include "Practice3-1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice31View

IMPLEMENT_DYNCREATE(CPractice31View, CView)

BEGIN_MESSAGE_MAP(CPractice31View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CPractice31View 생성/소멸

CPractice31View::CPractice31View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_intMiliSecond = 0;
	m_intSecond = 0;
	m_intMinute = 0;
}

CPractice31View::~CPractice31View()
{
}

BOOL CPractice31View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice31View 그리기

void CPractice31View::OnDraw(CDC* pDC)
{
	CPractice31Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPractice31View 인쇄

BOOL CPractice31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice31View 진단

#ifdef _DEBUG
void CPractice31View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice31View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice31Doc* CPractice31View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice31Doc)));
	return (CPractice31Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice31View 메시지 처리기

void CPractice31View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun)
	{
			m_bTimerRun = false;
	}
	else
	{
			m_bTimerRun = true;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CPractice31View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		if (AfxMessageBox(_T("초기화 하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerRun = false;
			m_intMiliSecond = 0;
			m_intSecond = 0;
			m_intMinute = 0;
		}
	CView::OnRButtonDown(nFlags, point);
}

void CPractice31View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun)
	{
		m_ctimeCurrentTime = CTime::GetCurrentTime();
		m_intMiliSecond += 1;
		if (m_intMiliSecond == 60)
		{
			m_intMiliSecond = 0;
			m_intSecond += 1;
		}
		if (m_intSecond == 60)
		{
			m_intMinute += 1;
			m_intSecond = 0;
		}
	}
		m_strTimer.Format(_T("%02d: %02d. %02d")
			, m_intMinute, m_intSecond, m_intMiliSecond);

	Invalidate();

	CView::OnTimer(nIDEvent);
}

int CPractice31View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 10, NULL);
	m_bTimerRun = TRUE;
	m_ctimeWhenStart = CTime::GetCurrentTime();
	
	return 0;
}
