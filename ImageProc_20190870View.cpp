
// ImageProc_20190870View.cpp: CImageProc20190870View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20190870.h"
#endif

#include "ImageProc_20190870Doc.h"
#include "ImageProc_20190870View.h"

#include <vfw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CImageProc20190870View

IMPLEMENT_DYNCREATE(CImageProc20190870View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20190870View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProc20190870View::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20190870View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProc20190870View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20190870View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProc20190870View::OnPixelDiv)
	ON_COMMAND(ID_PIXLE_HISTO_EQU, &CImageProc20190870View::OnPixleHistoEqu)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CImageProc20190870View::OnPixelContrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20190870View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20190870View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20190870View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20190870View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTING, &CImageProc20190870View::OnRegionSmooting)
	ON_COMMAND(ID_EMBOSSING, &CImageProc20190870View::OnEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProc20190870View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20190870View::OnRegionSobel)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20190870View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20190870View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CImageProc20190870View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CImageProc20190870View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20190870View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20190870View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20190870View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20190870View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20190870View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20190870View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILNAR_INTERPRION, &CImageProc20190870View::OnGeometryZoominBilnarInterprion)
	ON_COMMAND(ID_GEOMETRY_ZOONOUT_SUBSAMPLING, &CImageProc20190870View::OnGeometryZoonoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImageProc20190870View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CImageProc20190870View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20190870View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_HOLIZANTIONAL_FLIP, &CImageProc20190870View::OnGeometryHolizantionalFlip)
	ON_COMMAND(ID_GEOMETRY_VERTICALFLIP, &CImageProc20190870View::OnGeometryVerticalflip)
	ON_COMMAND(ID_GEOMTRY_WARPING, &CImageProc20190870View::OnGeomtryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImageProc20190870View::OnAviView)
END_MESSAGE_MAP()

// CImageProc20190870View 생성/소멸

CImageProc20190870View::CImageProc20190870View() noexcept
{
	bAciMdode = false;
	

}

CImageProc20190870View::~CImageProc20190870View()
{
}

BOOL CImageProc20190870View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20190870View 그리기

void CImageProc20190870View::OnDraw(CDC* pDC)
{
	CImageProc20190870Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (bAciMdode)
	{
		//재생
		Load_AviFile(pDC);
		bAciMdode = false;
		return; 
	}
	int x, y;

	if (pDoc->InputImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x], pDoc->InputImg[y][x], pDoc->InputImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][3 * x + 0], pDoc->InputImg[y][3 * x + 1], pDoc->InputImg[y][3 * x + 2]));
		}
	}


	if (pDoc->ResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][3 * x + 0], pDoc->ResultImg[y][3 * x + 1], pDoc->ResultImg[y][3 * x + 2]));
		}
	}


	if (pDoc->InputImg2 != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->InputImg2[y][x], pDoc->InputImg2[y][x], pDoc->InputImg2[y][x]));
		}
		else 
		{
			for (y = 0; y < pDoc->Imagehight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->InputImg2[y][3 * x + 0], pDoc->InputImg2[y][3 * x + 1], pDoc->InputImg2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->Imagehight + 20 + y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->Imagehight + 20 + y, RGB(pDoc->gResultImg[y][3 * x + 0], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
		}
	}

}




void CImageProc20190870View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	 
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20190870View 인쇄


void CImageProc20190870View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProc20190870View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProc20190870View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProc20190870View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

//void CImageProc20190870View::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

//void CImageProc20190870View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CImageProc20190870View 진단

#ifdef _DEBUG
void CImageProc20190870View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20190870View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20190870Doc* CImageProc20190870View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20190870Doc)));
	return (CImageProc20190870Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20190870View 메시지 처리기


void CImageProc20190870View::OnPixelAdd()  // 픽셀기반처리 산술덧셈
{
	CImageProc20190870Doc* pDoc = GetDocument();
	
	if (pDoc->InputImg == NULL) return;
	int x, y;
	int value;

	for(y=0; y<pDoc->Imagehight;y++)
		for (x = 0; x<pDoc->ImageWidth*pDoc->depth;x++)
		{
			value = pDoc->InputImg[y][x] + 50;
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
				pDoc->ResultImg[y][x] = value;	
		}
	Invalidate();
}


void CImageProc20190870View::OnPixelSub()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	if (pDoc->InputImg == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = pDoc->InputImg[y][x] - 50;
			if (value > 255)    value = 255;
			else if (value < 0)    value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	Invalidate();
}


void CImageProc20190870View::OnPixelMul()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	if (pDoc->InputImg == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = static_cast<int>(pDoc->InputImg[y][x] * 1.5);
			if (value > 255)    value = 255;
			else if (value < 0)    value = 0;
			pDoc->ResultImg[y][x] = static_cast<unsigned char>(value);
		}

	Invalidate();
}




void CImageProc20190870View::OnPixelDiv()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	if (pDoc->InputImg == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->Imagehight; y++)
	{
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x += pDoc->depth)
		{
			// Separate RGB channels
			int r = pDoc->InputImg[y][x];
			int g = pDoc->InputImg[y][x + 1];
			int b = pDoc->InputImg[y][x + 2];

			// Perform division for each channel
			int resultR = static_cast<int>(r / 1.5);
			int resultG = static_cast<int>(g / 1.5);
			int resultB = static_cast<int>(b / 1.5);

			// Clamp values to the valid range
			resultR = max(0, min(255, resultR));
			resultG = max(0, min(255, resultG));
			resultB = max(0, min(255, resultB));

			// Save the results to ResultImg
			pDoc->ResultImg[y][x] = static_cast<unsigned char>(resultR);
			pDoc->ResultImg[y][x + 1] = static_cast<unsigned char>(resultG);
			pDoc->ResultImg[y][x + 2] = static_cast<unsigned char>(resultB);
		}
	}

	Invalidate();
}



void CImageProc20190870View::OnPixleHistoEqu()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y, k;
	int hist[256]; // 히스토그램을 저장하기 위한 변수
	int sum[256];  // 누적분포를 저장하기 위한 변수
	int acc_hist = 0;
	int N = 256 * 256;  // 전체 픽셀의 갯수

	for (k = 0; k < 256; k++) hist[k] = 0; // 히스토그램 초기화

	// 히스토그램 계산
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
			hist[pDoc->InputImg[y][x]]++;

	// 누적분포 계산
	for (k = 0; k < 256; k++)
	{
		acc_hist += hist[k];
		sum[k] = acc_hist;
	}

	// 히스토그램 평활화 적용
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			k = pDoc->InputImg[y][x];
			pDoc->ResultImg[y][x] = static_cast<int>(static_cast<double>(sum[k]) / N * 255.0);
		}

	Invalidate();  // 화면의 자동 갱신
}




/*void CImageProc20190870View::OnPixelContrastStretching() //명암대비스트레칭
{
	CImageProc20190870Doc* pDoc = GetDocument(); //도큐면트를 읽어서 view에서 처리할 수 있도록 만들어줌 

	//변수선언
	
	//최댓값, 최솟값검색 기준값 정하고 기준보다 큰 값 나오면 최댓값을 검색해주고 기준보다 작으면 최솟값을 검색해줌 
	//최대값은 기준 값이 0, 최솟값은 기준값이 256(가장 큰 값 )
	
	// P= (float)(P-min) / (max-min)*255 //나눗셈 생각하기
	//정수 나누기 정수는 소숫점이 없어져서 0이 나올 가능성이 높음, 소숫점이 반드시 필요할때는 fliat로 변환 필요 


	Invalidate();
}
*/

void CImageProc20190870View::OnPixelContrastStretching() //명암대비 스트레칭 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	// 변수 선언
	int x, y;
	int minPixelValue = 255; // 최솟값 초기화
	int maxPixelValue = 0;  // 최댓값 초기화

	// 최솟값과 최댓값 검색
	for (y = 0; y < 256; y++)
	{
		for (x = 0; x < 256; x++)
		{
			int pixelValue = pDoc->InputImg[y][x]; // 이미지의 해당 픽셀 값
			if (pixelValue < minPixelValue)
				minPixelValue = pixelValue;
			if (pixelValue > maxPixelValue)
				maxPixelValue = pixelValue;

		}
	}
	Invalidate();

	// 명암대비 스트레칭 수행
	for (y = 0; y < 256; y++)
	{
		for (x = 0; x < 256; x++)
		{
			int pixelValue = pDoc->InputImg[y][x];
			float stretchedPixelValue = (float)(pixelValue - minPixelValue) / (maxPixelValue - minPixelValue) * 255.0f;
			pDoc->ResultImg[y][x] = static_cast<unsigned char>(stretchedPixelValue);
		}
	}

	Invalidate();
}



void CImageProc20190870View::OnPixelBinarization()    //이진화
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int thresh = 150; //중간값 기준 이거보다 크면 흰색 이거보다 작으면 검은색 //흰색이 많이 타면 thresh값을 올려서 검은색이 더 많이 나오게 하면 된다.
	int x, y; 

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) //이중 for 문으로 순환시키기

		{
			if (pDoc->InputImg[y][x] > thresh)
				pDoc->ResultImg[y][x] = 255;
			else								//2가지 비교 그래서 Result에는 흰색 아니면 검은색이 들어가게됨 
				pDoc->ResultImg[y][x] = 0;
		}

	Invalidate(); 

}


void CImageProc20190870View::OnPixelTwoImageAdd() //두 영상의 덧셈 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->Imagehight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->ResultImg[y][x] = 0.5 * pDoc->InputImg[y][x] + 0.5 * pDoc->InputImg2[y][x];
				}
				else
				{
					pDoc->ResultImg[y][3 * x + 0] = 0.5 * pDoc->InputImg[y][3 * x + 0] + 0.5 * pDoc->InputImg2[y][3 * x + 0];
					pDoc->ResultImg[y][3 * x + 1] = 0.5 * pDoc->InputImg[y][3 * x + 1] + 0.5 * pDoc->InputImg2[y][3 * x + 1];
					pDoc->ResultImg[y][3 * x + 2] = 0.5 * pDoc->InputImg[y][3 * x + 2] + 0.5 * pDoc->InputImg2[y][3 * x + 2];
				}
			}

		Invalidate();
	}
}




void CImageProc20190870View::OnPixelTwoImageSub() //두영상의 뺼셈
{
    CImageProc20190870Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->Imagehight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->ResultImg[y][x] = abs(pDoc->InputImg[y][x] - pDoc->InputImg2[y][x]);
				}
				else
				{
					pDoc->ResultImg[y][3 * x + 0] = abs(pDoc->InputImg[y][3 * x + 0] - pDoc->InputImg2[y][3 * x + 0]);
					pDoc->ResultImg[y][3 * x + 1] = abs(pDoc->InputImg[y][3 * x + 1] - pDoc->InputImg2[y][3 * x + 1]);
					pDoc->ResultImg[y][3 * x + 2] = abs(pDoc->InputImg[y][3 * x + 2] - pDoc->InputImg2[y][3 * x + 2]);
				}
			}

		Invalidate();
	}
}




	void CImageProc20190870View::Convolve(unsigned char** InImg, unsigned char** OutImg, int cols, int rows, float mask[][3], int bias, int depth)
	{
		int x, y, value, i, j;
		float sum, redsum, greensum, bluesum;

		for (y = 1; y < rows - 1; y++)
			for (x = 1; x < cols - 1; x++)
			{
				if (depth == 1)
				{
					sum = 0;
					for (j = 0; j < 3; j++)
						for (i = 0; i < 3; i++)
						{
							sum += InImg[y - 1 + j][x - 1 + i] * mask[j][i];
						}
					sum = sum + bias;
					if (sum > 255)		sum = 255;
					else if (sum < 0)	sum = 0;
					OutImg[y][x] = sum;
				}
				else
				{
					redsum = 0; greensum = 0; bluesum = 0;
					for (j = 0; j < 3; j++)
						for (i = 0; i < 3; i++)
						{
							redsum += InImg[y - 1 + j][3 * (x - 1 + i) + 0] * mask[j][i];
							greensum += InImg[y - 1 + j][3 * (x - 1 + i) + 1] * mask[j][i];
							bluesum += InImg[y - 1 + j][3 * (x - 1 + i) + 2] * mask[j][i];
						}
					redsum += bias;
					greensum += bias;
					bluesum += bias;

					if (redsum > 255)		redsum = 255;
					else if (redsum < 0)	redsum = 0;
					if (greensum > 255)		greensum = 255;
					else if (redsum < 0)	greensum = 0;
					if (bluesum > 255)		bluesum = 255;
					else if (bluesum < 0)	bluesum = 0;

					OutImg[y][3 * x + 0] = redsum;
					OutImg[y][3 * x + 1] = greensum;
					OutImg[y][3 * x + 2] = bluesum;
				}
				Invalidate();
			}
	}




void CImageProc20190870View::OnRegionSharpening() // 선명하게 하기 함수
{


CImageProc20190870Doc* pDoc = GetDocument();

float kernel[3][3] = { {0, 1, -1},
			 {-1, 5, -1},
			{0, -1, 0} };

Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->Imagehight, kernel, 0, pDoc->depth);

Invalidate();
}



	void CImageProc20190870View::OnRegionSmooting()  //흐리게 하기
	{
		CImageProc20190870Doc* pDoc = GetDocument();

		float kernel[3][3] = { {1 / 9.0,1 / 9.0,1 / 9.0},
						  {1 / 9.0,1 / 9.0,1 / 9.0},
						  {1 / 9.0,1 / 9.0,1 / 9.0}, };
		Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->Imagehight, kernel, 0, pDoc->depth);

		Invalidate();
	}




void CImageProc20190870View::OnEmbossing()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0},
					{0, 0, 0},
					{0, 0, 1} };

	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->Imagehight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CImageProc20190870View::OnRegionPrewitt()

{
	CImageProc20190870Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,-1,-1},
					  {0, 0, 0},
					  {1, 1, 1} }; //수평 방향 마스크
	float Vmask[3][3] = { {-1, 0, 1},
					  {-1, 0, 1},
					  {-1, 0, 1} }; //수직 방향 마스크

	unsigned char** Er, ** Ec;
	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->Imagehight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->Imagehight, Hmask, 0, pDoc->depth); //수평 방향
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->Imagehight, Vmask, 0, pDoc->depth); //수직 방향

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]); 
				if (value < 0) value = 0;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;

			}
		}

	//메모리 해제
	for (int i = 0; i < pDoc->Imagehight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}




void CImageProc20190870View::OnRegionRoberts()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {1, 0, 0},
						  {0, -1, 0},
						  {0, 0, 0} }; // 수평 방향 마스크
	float Vmask[3][3] = { {0, 0, 0},
						  {0, -1, 0},
						  {0, 1, 0} }; // 수직 방향 마스크

	unsigned char** Er, ** Ec;
	int x, y, value;

	// 메모리 할당
	Er = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->Imagehight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->Imagehight, Hmask, 0, pDoc->depth); // 수평 방향
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->Imagehight, Vmask, 0, pDoc->depth); // 수직 방향

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value < 0) value = 0;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;

			}
		}

	// 메모리 해제
	for (int i = 0; i < pDoc->Imagehight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}




void CImageProc20190870View::OnRegionSobel()  // 소벨 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	float maskH[3][3] = { { -1,  -2,  -1},
							{  0,   0,   0},
							{  1,   2,   1} };	
	float maskV[3][3] = { { 1,   0,  -1},
							{ -2,   0,  2},
							{ -1,   0,  1} };

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->Imagehight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->Imagehight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->Imagehight, maskH, 128, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->Imagehight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->ResultImg[y][x] = sum;
			}
			else
			{
				rsum = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rsum > 255)		rsum = 255;
				else if (rsum < 0)	rsum = 0;

				gsum = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gsum > 255)		gsum = 255;
				else if (rsum < 0)	gsum = 0;

				bsum = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bsum > 255)		bsum = 255;
				else if (rsum < 0)	bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255)			sum = 255;
				else if (sum < 0)		sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->ResultImg[y][3 * x + 0] = sum;
				pDoc->ResultImg[y][3 * x + 1] = sum;
				pDoc->ResultImg[y][3 * x + 2] = sum;
			}
		}

	for (i = 0; i < pDoc->Imagehight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}





void CImageProc20190870View::OnRegionAverageFiltering() //평균값 필터링 
{
	CImageProc20190870Doc* pDoc = GetDocument();
	int x, y, i, j;
	int sum, rsum, gsum, bsum;

	//5*5 영역의 평균값
	for (y = 2; y < pDoc->Imagehight - 2; y++)
		for (x = 2; x < pDoc->ImageWidth - 2; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						sum += pDoc->InputImg[y + j - 2][x + i - 2];
					}
				sum /= 25;

				if (sum > 255)		sum = 255;
				else if (sum < 0)		sum = 0;

				pDoc->ResultImg[y][x] = sum;
			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						rsum += pDoc->InputImg[y + j - 2][3 * (x + i - 2) + 0];
						gsum += pDoc->InputImg[y + j - 2][3 * (x + i - 2) + 1];
						bsum += pDoc->InputImg[y + j - 2][3 * (x + i - 2) + 2];
					}
				rsum /= 25;		gsum /= 25;		bsum /= 25;

				if (rsum > 255)			rsum = 255;
				else if (rsum < 0)		rsum = 0;
				if (gsum > 255)			gsum = 255;
				else if (gsum < 0)		gsum = 0;
				if (bsum > 255)			bsum = 255;
				else if (bsum < 0)		bsum = 0;

				pDoc->ResultImg[y][3 * x + 0] = rsum;
				pDoc->ResultImg[y][3 * x + 1] = gsum;
				pDoc->ResultImg[y][3 * x + 2] = bsum;
			}
		}

	Invalidate();
}


void CImageProc20190870View::OnRegionMedianFiltering() // 중간값 필터링 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->Imagehight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				n[0] = pDoc->InputImg[y - 1][x - 1];
				n[1] = pDoc->InputImg[y - 1][x + 0];
				n[2] = pDoc->InputImg[y - 1][x + 1];
				n[3] = pDoc->InputImg[y - 0][x - 1];
				n[4] = pDoc->InputImg[y - 0][x + 0];
				n[5] = pDoc->InputImg[y - 0][x + 1];
				n[6] = pDoc->InputImg[y + 1][x - 1];
				n[7] = pDoc->InputImg[y + 1][x + 0];
				n[8] = pDoc->InputImg[y + 1][x + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImg[y][x] = n[4];
			}
			else
			{
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImg[y - 1][3 * (x + 0) + 0];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImg[y - 0][3 * (x + 0) + 0];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImg[y + 1][3 * (x + 0) + 0];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 0];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImg[y][3 * x + 0] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImg[y - 1][3 * (x + 0) + 1];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImg[y - 0][3 * (x + 0) + 1];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImg[y + 1][3 * (x + 0) + 1];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImg[y][3 * x + 1] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImg[y - 1][3 * (x + 0) + 2];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImg[y - 0][3 * (x + 0) + 2];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImg[y + 1][3 * (x + 0) + 2];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 2];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImg[y][3 * x + 2] = n[4];
			}
		}

	Invalidate();
}


void CImageProc20190870View::OnMopologyColorGray()
{
	CImageProc20190870Doc* pDoc = GetDocument();
	if (pDoc->depth == 1)	return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3;

			pDoc->InputImg[y][3 * x + 0] = gray;
			pDoc->InputImg[y][3 * x + 1] = gray;
			pDoc->InputImg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CImageProc20190870View::OnMopologyBinarization()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y;
	int thresh = 128;

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InputImg[y][x] > thresh)
					pDoc->InputImg[y][x] = 255;
				else
					pDoc->InputImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3
	> thresh)
				{
					pDoc->InputImg[y][3 * x + 0] = 255;
					pDoc->InputImg[y][3 * x + 1] = 255;
					pDoc->InputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImg[y][3 * x + 0] = 0;
					pDoc->InputImg[y][3 * x + 1] = 0;
					pDoc->InputImg[y][3 * x + 2] = 0;
				}

			}
		}
	Invalidate();
}


void CImageProc20190870View::OnMopologyErosion() //형태학적 침식연산 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min, rmin, gmin, bmin = 255;

	for (y = 1; y < pDoc->Imagehight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] < min)
							min = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = min;
			}
			else
			{
				rmin = 255;	gmin = 255;	bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmin;
				pDoc->ResultImg[y][3 * x + 1] = gmin;
				pDoc->ResultImg[y][3 * x + 2] = bmin;
			}
		}

	Invalidate();
}

void CImageProc20190870View::OnMopologyDilation() //형태학적 팽창연산 
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax = 0; // 0또는 마이너스 값 교환이 처음에는 반드시 일어나도록. 

	for (y = 1; y < pDoc->Imagehight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] > max)
							max = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = max;
			}
			else
			{
				rmax = 0;	gmax = 0;	bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmax;
				pDoc->ResultImg[y][3 * x + 1] = gmax;
				pDoc->ResultImg[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
}



void CImageProc20190870View::OnMopologyOpening() 
{
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion(); 
	CopyResultToinput();

	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
}




void CImageProc20190870View::CopyResultToinput()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->Imagehight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->InputImg[y][x] = pDoc->ResultImg[y][x];  // 흑백의 경우 resultimg 복사 ? 
		}
}


void CImageProc20190870View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();

	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion(); 
	
}


void CImageProc20190870View::OnGeometryZoominPixelCopy()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int	x, y;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->Imagehight * yscale;
	// 메모리 할당 

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->InputImg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 2];
			}
		}
	Invalidate();
}



void CImageProc20190870View::OnGeometryZoominBilnarInterprion()//interpolation
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int	x, y;

	float xscale = 2.3;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}	

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->Imagehight * yscale + 0.5;
	// 메모리 할당 

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상 
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta  = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->gImageWidth - 1;
			if (Cy > pDoc->Imagehight - 1) Cy = pDoc->Imagehight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->gImageWidth - 1;
			if (Dy > pDoc->Imagehight - 1) Dy = pDoc->Imagehight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->InputImg[Ay][Ax] + alpha * pDoc->gResultImg[By][Bx];
				F = (1 - alpha) * pDoc->InputImg[Cy][Cx] + alpha * pDoc->gResultImg[Dy][Dx];

				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 0] + alpha * pDoc->gResultImg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 0] + alpha * pDoc->gResultImg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 1] + alpha * pDoc->gResultImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 1] + alpha * pDoc->gResultImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;


				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 2] + alpha * pDoc->gResultImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 2] + alpha * pDoc->gResultImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;

			}
		}
	Invalidate();
}


void CImageProc20190870View::OnGeometryZoonoutSubsampling()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int xscale = 3;		// 1/3
	int yscale = 2;		// 1/2
	int x, y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->Imagehight / yscale;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->InputImg[y * yscale][x * xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 2];
			}
		}
	Invalidate();
}

void CImageProc20190870View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmooting();
	CopyResultToinput();
	OnGeometryZoonoutSubsampling();
}



void CImageProc20190870View::OnGeometryAvgFiltering()
{
	CImageProc20190870Doc* pDoc = GetDocument();

	int xscale = 3;		// 1/3
	int yscale = 2;		// 1/2
	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->Imagehight / yscale;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향사상
	for (y = 0; y < pDoc->Imagehight; y += yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->InputImg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->InputImg[src_y][3 * src_x + 0];
						gsum += pDoc->InputImg[src_y][3 * src_x + 1];
						bsum += pDoc->InputImg[src_y][3 * src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}
	Invalidate();
}


#define PI 3.1415926521

#include "CAngleDialog.h"
void CImageProc20190870View::OnGeometryRotation()
{
	CImageProc20190870Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30; // degree 단위
	float radian;
	int Hy;    //y좌표의 마지막 위치
	int Cx, Cy; //영상의 가운데 좌표값
	int x, y, i, xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;


	radian = PI / 180 * angle;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->Imagehight * fabs(cos(PI / 2 - radian)) +
		pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->Imagehight * fabs(cos(radian)) +
		pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->Imagehight / 2;
	//y의 마지막좌표
	Hy = pDoc->Imagehight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->Imagehight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = ((Hy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - (((Hy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1)
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->Imagehight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InputImg[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->Imagehight - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImg[y_source][3 * (x_source)+0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImg[y_source][3 * (x_source)+1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImg[y_source][3 * (x_source)+2];

				}
			}
		}
	Invalidate();
}

	void CImageProc20190870View::OnGeometryHolizantionalFlip()
	{
		CImageProc20190870Doc* pDoc = GetDocument();
		int x, y;

		for(y=0; y<pDoc->Imagehight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if(pDoc->depth==1)
				pDoc->ResultImg[y][x] = pDoc->InputImg[y][pDoc->ImageWidth - 1 - x];
				else
				{
					pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
					pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
					pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
				}
			}
		Invalidate();
	}


	void CImageProc20190870View::OnGeometryVerticalflip()   //상하대칭 
	{
		CImageProc20190870Doc* pDoc = GetDocument();
		int x, y;

		for (y = 0; y < pDoc->Imagehight; y++) {
			for (x = 0; x < pDoc->ImageWidth; x++) {
				if (pDoc->depth == 1) {
					// 단일 채널 이미지의 경우
					pDoc->ResultImg[y][x] = pDoc->InputImg[pDoc->Imagehight - 1 - y][x];
				}
				else {
					// 다중 채널 이미지의 경우
					pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[pDoc->Imagehight - 1 - y][3 * x + 0];
					pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[pDoc->Imagehight - 1 - y][3 * x + 1];
					pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[pDoc->Imagehight - 1 - y][3 * x + 2];
				}
			}
		}

		Invalidate();


	}

	typedef struct
	{
		int Px;
		int Py;
		int Qx;
		int Qy;

	} control_line;

	control_line mctrl_source = { 100,100,150,150 };
	control_line mctrl_dest = { 100,100,200,200 };


	void CImageProc20190870View::OnGeomtryWarping()
	{
		CImageProc20190870Doc* pDoc = GetDocument();

		control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->Imagehight - 1},
		{pDoc->ImageWidth - 1,pDoc->Imagehight - 1,0,pDoc->Imagehight - 1},{0,pDoc->Imagehight - 1,0,0} };
		control_line dest_lines[5] = { {100,100,200,200},
			{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->Imagehight - 1},
			{pDoc->ImageWidth - 1,pDoc->Imagehight - 1,0,pDoc->Imagehight - 1},{0,pDoc->Imagehight - 1,0,0} };

		source_lines[0] = mctrl_source;
		dest_lines[0] = mctrl_dest;

		int x, y;

		double u;	// 수직 교차점의 위치  
		double h;	// 제어선으로부터 픽셀의 수직 변위
		double d;	// 제어선과 픽셀 사이의 거리
		double tx, ty;	//결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
		double xp, yp;	//각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치
		double weight;	//각 제어선의 가중치
		double totalweight;	// 가중치의 합  
		double a = 0.001;
		double b = 2.0;
		double p = 0.75;

		int x1, y1, x2, y2;
		int src_x1, src_y1, src_x2, src_y2;
		double src_line_length, dest_line_length;

		int num_lines = 5; // 제어선의 개수
		int line;
		int source_x, source_y;
		int last_row, last_col;

		last_col = pDoc->ImageWidth - 1;
		last_row = pDoc->Imagehight - 1;

		for (y = 0; y < pDoc->Imagehight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				tx = 0.0;
				ty = 0.0;
				totalweight = 0.0;

				for (line = 0; line < num_lines; line++)
				{
					x1 = dest_lines[line].Px;
					y1 = dest_lines[line].Py;
					x2 = dest_lines[line].Qx;
					y2 = dest_lines[line].Qy;

					dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

					u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
						(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

					h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

					if (u < 0)		d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
					else if (u > 1)	d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
					else			d = fabs(h);

					src_x1 = source_lines[line].Px;
					src_y1 = source_lines[line].Py;
					src_x2 = source_lines[line].Qx;
					src_y2 = source_lines[line].Qy;

					src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

					xp = src_x1 + u * (src_x2 - src_x1) + h * (src_y2 - src_y1) / src_line_length;
					yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

					weight = pow(pow(dest_line_length, p) / (a + d), b);

					tx += (xp - x) * weight;
					ty += (yp - y) * weight;
					totalweight += weight;
				}

				source_x = x + (tx / totalweight);
				source_y = y + (ty / totalweight);

				if (source_x < 0)			source_x = 0;
				if (source_x > last_col)	source_x = last_col;
				if (source_y < 0)			source_y = 0;
				if (source_y > last_row)	source_y = last_row;

				if (pDoc->depth == 1)
					pDoc->ResultImg[y][x] = pDoc->InputImg[source_y][source_x];
				else
				{
					pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[source_y][3 * source_x + 0];
					pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[source_y][3 * source_x + 1];
					pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[source_y][3 * source_x + 2];
				}

				}
		Invalidate();

	} 

	CPoint mpos_st, mpos_end;

	void CImageProc20190870View::OnLButtonDown(UINT nFlags, CPoint point)
	{
		mpos_st = point;

		CScrollView::OnLButtonDown(nFlags, point);
	}


	void CImageProc20190870View::OnLButtonUp(UINT nFlags, CPoint point)
	{
		mpos_end = point;

		CDC* pDC = GetDC(); 
		CPen rpen;
		rpen.CreatePen(PS_SOLID,0,RGB(255, 0, 0));
		pDC->SelectObject(&rpen);

		pDC->MoveTo(mpos_st);
		pDC -> LineTo(mpos_end);
		ReleaseDC(pDC);

		int Ax, Ay, Bx, By;
		Ax = mpos_st.x;
		Ay = mpos_st.y;
		Bx = mpos_end.x;
		By = mpos_end.x;

		if (Ax < Bx) mctrl_source.Px = Ax - (Bx - Ax) / 2;
		else		mctrl_source.Px = Ax+ (Bx - Ax) / 2;

		if (Ay < By) mctrl_source.Py = Ay - (By - Ay) / 2;
		else		mctrl_source.Py = Ay + (By - Ay) / 2;
		
		mctrl_dest.Px = mctrl_source.Px;
		mctrl_dest.Px = mctrl_source.Px;

		mctrl_source.Qx = mpos_st.x;
		mctrl_source.Qy = mpos_st.y;
		mctrl_dest.Qx = mpos_end.x;

		CScrollView::OnLButtonUp(nFlags, point);
	}



	void CImageProc20190870View::OnAviView()
	{
		CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Avi화일(*.avi|*.avi|모든화일|*,*|");

			if (dlg.DoModal() == IDOK)
			{
				AviFileName = dlg.GetPathName();
				bAciMdode = true; // 이름 잘못만듬 원랜 bAvimdode
					Invalidate();
			}
	
	}


	void CImageProc20190870View::Load_AviFile(CDC* pDC)
	{
		PAVIFILE pavi; // # include <vwf> 이걸 추가하면 PAVIFILE 파일의 오류가 사라짐 
		AVIFILEINFO fi;
		int stm;
		PAVISTREAM pstm = NULL;
		AVISTREAMINFO si;
		PGETFRAME pfrm = NULL;
		int frame;
		LPBITMAPINFOHEADER pbmpih;
		unsigned char* image;
		int x, y;

		AVIFileInit();
		AVIFileOpen(&pavi, AviFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
		AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

		for (stm = 0; stm < fi.dwStreams; stm++)
		{
			AVIFileGetStream(pavi, &pstm, 0, stm);
			AVIStreamInfo(pstm, &si, sizeof(si));
			if (si.fccType == streamtypeVIDEO)
			{
				pfrm = AVIStreamGetFrameOpen(pstm, NULL);
				for (frame = 0; frame < si.dwLength; frame++) //si.dwLength;  이 부분이 전체 프레임 수  앞에 30 프레임만 재생 해본다
				{
					pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
						if (!pbmpih)	continue;
						
						image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

						/*
						for(y=0; y<fi.dwHeight; y++)
							for (x = 0; x < fi.dwWidth; x++)
							{
								pDC->SetPixel(x, fi.dwHeight-1-y,
									RGB(image[(y * fi.dwWidth + x) * 3 + 2],
										image[(y * fi.dwWidth + x) * 3 + 1],
										image[(y * fi.dwWidth + x) * 3 + 0]));
								
							}
							*/
						::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight,
							0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
						Sleep(1); //33정도가 일반 
				}
			}
		}
		AVIStreamGetFrameClose(pfrm);
		AVIStreamRelease(pstm);
		AVIFileRelease(pavi);
		AVIFileExit();
	}