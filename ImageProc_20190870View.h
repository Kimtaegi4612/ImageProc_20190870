
// ImageProc_20190870View.h: CImageProc20190870View 클래스의 인터페이스
//

#pragma once


class CImageProc20190870View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20190870View() noexcept;
	DECLARE_DYNCREATE(CImageProc20190870View)

// 특성입니다.
public:
	CImageProc20190870Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProc20190870View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixleHistoEqu();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSharpening();
	void Convolve(unsigned char** InputImg, unsigned char** ResultImg, int cols, int rows, float mask[3][3], int bias, int depth);
	afx_msg void OnRegionSmooting();
	afx_msg void OnEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopologyDilation();
	void CopyResultToinput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilnarInterprion();
	afx_msg void OnGeometryZoonoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryHolizantionalFlip();
	afx_msg void OnGeometryVerticalflip();
	afx_msg void OnGeomtryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAciMdode;
	CString AviFileName;
	void Load_AviFile(CDC* pDC);
};

#ifndef _DEBUG  // ImageProc_20190870View.cpp의 디버그 버전
inline CImageProc20190870Doc* CImageProc20190870View::GetDocument() const
   { return reinterpret_cast<CImageProc20190870Doc*>(m_pDocument); }
#endif

