
// Practice2b_pdView.cpp: CPractice2bpdView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice2b_pd.h"
#endif

#include "Practice2b_pdDoc.h"
#include "Practice2b_pdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice2bpdView

IMPLEMENT_DYNCREATE(CPractice2bpdView, CView)

BEGIN_MESSAGE_MAP(CPractice2bpdView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPractice2bpdView 생성/소멸

CPractice2bpdView::CPractice2bpdView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice2bpdView::~CPractice2bpdView()
{
}

BOOL CPractice2bpdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice2bpdView 그리기

void CPractice2bpdView::OnDraw(CDC* pDC)
{
	CPractice2bpdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOutW(10, 10, m_strWindowSize);

	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->TextOut(m_ptMouseMove.x, m_ptMouseMove.y, m_strMouseMove);

}


// CPractice2bpdView 인쇄

BOOL CPractice2bpdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice2bpdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice2bpdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice2bpdView 진단

#ifdef _DEBUG
void CPractice2bpdView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice2bpdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice2bpdDoc* CPractice2bpdView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice2bpdDoc)));
	return (CPractice2bpdDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice2bpdView 메시지 처리기

void CPractice2bpdView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_strWindowSize.Format(_T("윈도우 크기는 넓이 %d, 높이 %d 입니다"), cx, cy);

	Invalidate();
}

void CPractice2bpdView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnRButtonDown(nFlags, point);
	m_strOutput = _T("오른쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();
}

void CPractice2bpdView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	m_bDrag = TRUE;

	m_strOutput = _T("왼쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();
}

void CPractice2bpdView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	m_strOutput = _T("키보드를 눌렀습니다.");
	Invalidate();
}

void CPractice2bpdView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
	
	if (m_bDrag == TRUE)
	{
		m_strOutput = _T("마우스를 드래그하고 있습니다.");
	}
	else
	{
		m_strOutput = _T("마우스를 이동 중입니다.");
	}
	
	m_ptMouseMove = point;
	m_strMouseMove.Format(_T("X:%d Y:%d"), point.x, point.y);

	Invalidate();
}


void CPractice2bpdView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);
	
	m_bDrag = FALSE;
}
