
// Practice3cView.cpp: CPractice3cView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice3c.h"
#endif

#include "Practice3cDoc.h"
#include "Practice3cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice3cView

IMPLEMENT_DYNCREATE(CPractice3cView, CView)

BEGIN_MESSAGE_MAP(CPractice3cView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice3cView 생성/소멸

CPractice3cView::CPractice3cView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_strOutput = _T("");
	m_ptLocation = (0, 0);
	m_bDrag = FALSE;
}

CPractice3cView::~CPractice3cView()
{
}

BOOL CPractice3cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice3cView 그리기

void CPractice3cView::OnDraw(CDC* pDC)
{
	CPractice3cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->TextOutW(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CPractice3cView 인쇄

BOOL CPractice3cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice3cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice3cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice3cView 진단

#ifdef _DEBUG
void CPractice3cView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice3cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice3cDoc* CPractice3cView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice3cDoc)));
	return (CPractice3cDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice3cView 메시지 처리기

void CPractice3cView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();	// 입력된 데이터의 길이를 얻는다.

	if (nChar == VK_BACK)			// 백스페이스가 눌린 경우
		m_strOutput.Delete(nCharIndex - 1, 1);	// 한 번에 하나씩 지운다.
	else					// 백스페이스 이외의 키가 눌린 경우
		m_strOutput += (WCHAR)nChar;		// 키보드로 입력된 문자를 문자열에 추가

	Invalidate();				// 화면 갱신
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CPractice3cView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)					// 가상키 코드 값에 대해 
	{
	case VK_LEFT:					// 왼쪽 화살표 키를 누를 때
		m_ptLocation.x--;			// 왼쪽으로 1픽셀 이동
		break;
	case VK_RIGHT:				// 오른쪽 화살표 키를 누를 때
		m_ptLocation.x++;			// 오른쪽으로 1픽셀 이동
		break;
	case VK_UP:					// 위쪽 화살표 키를 누를 때
		m_ptLocation.y--;			// 위쪽으로 1픽셀 이동
		break;
	case VK_DOWN:				// 아래쪽 화살표 키를 누를 때
		m_ptLocation.y++;			// 아래쪽으로 1픽셀 이동
		break;
	case VK_PRIOR:					// Pg up 키를 누를 때
		m_ptLocation.y -= 50;			// 위쪽으로 50픽셀 이동
		break;
	case VK_NEXT:					// Pg dn 키를 누를 때
		m_ptLocation.y += 50;			// 아래쪽으로 50픽셀 이동
		break;
	case VK_HOME:					// Home 키를 누를 때
		m_ptLocation = CPoint(0, 0);		// 처음 위치로 이동
		break;
	}

	if (m_ptLocation.x < 0)			// 왼쪽 경계선을 만나면
	{
		m_ptLocation.x = 0;			// m_ptLocation.x = 0으로 초기화
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y < 0)			// 위쪽 경계선을 만나면
	{
		m_ptLocation.y = 0;			// m_ptLocation.y = 0으로 초기화
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.x > m_ptClientSize.x)	// 오른쪽 경계선을 만나면
	{
		m_ptLocation.x = m_ptClientSize.x;	// m_ptLocation.x = 윈도우 x 크기로 초기화
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y > m_ptClientSize.y)		// 아래쪽 경계선을 만나면
	{
		m_ptLocation.y = m_ptClientSize.y;	// m_ptLocation.y = 윈도우 y 크기로 초기화
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}
	Invalidate();					// 화면 갱신
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPractice3cView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;
	Invalidate();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CPractice3cView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptLocation = point;
	Invalidate();
	if (point.x >= m_ptLocation.x - 30 && point.x <= m_ptLocation.x + 30 &&
		point.y >= m_ptLocation.y - 30 && point.y <= m_ptLocation.y + 30)
	{
		m_bDrag = true;
	}
	m_ptLocation = point;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}

void CPractice3cView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strOutput.IsEmpty() == false)
	{
		if (AfxMessageBox(_T("문자를 모두 지우시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_strOutput.Empty();
		}
	}
	else
	{
		AfxMessageBox(_T("문자열을 입력하시오."));
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}	
