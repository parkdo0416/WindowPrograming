
// Practice3bView.cpp: CPractice3bView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice3b.h"
#endif

#include "Practice3bDoc.h"
#include "Practice3bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice3bView

IMPLEMENT_DYNCREATE(CPractice3bView, CView)

BEGIN_MESSAGE_MAP(CPractice3bView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPractice3bView 생성/소멸

CPractice3bView::CPractice3bView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bTimerRun = FALSE;
	m_bTimerType = TRUE;
}

CPractice3bView::~CPractice3bView()
{
}

BOOL CPractice3bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice3bView 그리기

void CPractice3bView::OnDraw(CDC* pDC)
{
	CPractice3bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPractice3bView 인쇄

BOOL CPractice3bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice3bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice3bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice3bView 진단

#ifdef _DEBUG
void CPractice3bView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice3bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice3bDoc* CPractice3bView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice3bDoc)));
	return (CPractice3bDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice3bView 메시지 처리기

void CPractice3bView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int hour;
	CString str;
	CTime timer;				// 타이머 변수 선언
	timer = CTime::GetCurrentTime();		// 현재 시각을 얻음

	if (m_bTimerType)			// 년, 월, 일, 시, 분, 초 형태일 경우
	{
		m_strTimer.Format(_T("현재는 %d년 %d월 %d일 %d시 %d분 %d초"),
			timer.GetYear(), timer.GetMonth(), timer.GetDay(),
			timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	}
	else
	{
		hour = timer.GetHour();
		if (hour >= 12)
		{
			str = _T("PM");
			if (hour >= 13)
				hour = hour - 12;
		}
		else
		{
			str = _T("AM");
		}
		m_strTimer.Format(_T("지금은 %s %d시 %d분 %d초"), str, hour,
			timer.GetMinute(), timer.GetSecond());
	}
	Invalidate();

	CView::OnTimer(nIDEvent);
}

int CPractice3bView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1000, NULL);
	m_bTimerRun = TRUE;

	return 0;
}

void CPractice3bView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerType)			 // 년, 월, 일, 시, 분, 초 형태로 출력 중 
	{
		if (AfxMessageBox(_T("시, 분, 초 형태로 표시하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = false;
		}
	}
	else					// 시, 분, 초 형태로 출력 중 
	{
		if (AfxMessageBox(_T("년, 월, 일, 시, 분, 초 형태로 표시하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = true;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CPractice3bView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun == false)		// 타이머가 동작 안 할 때 메시지 박스 출력 
	{
		if (AfxMessageBox(_T("디지털시계를 동작시키겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			SetTimer(0, 1000, NULL);		// 타이머 설정
			m_bTimerRun = true;		// 타이머 동작 => true
		}
	}
	else					// 타이머가 동작 중일 때 메시지 박스 출력
	{
		if (AfxMessageBox(_T("정말로 디지털시계 동작을 멈추겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);			// 타이머 해제
			m_bTimerRun = false;		// 타이머 동작 => false
		}
	}
	CView::OnRButtonDown(nFlags, point);
}

void CPractice3bView::OnDestroy()
{
	CView::OnDestroy();
	if (m_bTimerRun)
	KillTimer(0);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
