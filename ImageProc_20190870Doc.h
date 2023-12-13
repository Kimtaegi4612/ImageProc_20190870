﻿
// ImageProc_20190870Doc.h: CImageProc20190870Doc 클래스의 인터페이스
//


#pragma once



class CImageProc20190870Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProc20190870Doc() noexcept;
	DECLARE_DYNCREATE(CImageProc20190870Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProc20190870Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 입력이미지
	unsigned char **InputImg; //[y][x]
	unsigned char **InputImg2; //[y][x]

	//출력이미지
	unsigned char **ResultImg; //[y][x]


	int ImageWidth;
	int Imagehight;
	int depth;  // 1 = 흑백, 3 = 칼라 칼라인지 흑백인지는 depth보고 구분하면됨 1일때인가 3일때인가 

	int gImageWidth;
	int gImageHeight;

	unsigned char** gResultImg; //[y][x]


	// ImageProc_20190870Doc.h 파일 내에 추가
public:
	// 다른 멤버 함수들과 함께 위치하도록 적절한 위치에 추가
	int LoadImageFile(CArchive& ar);

	// ImageProc_20190870Doc.h 파일 내에 추가
public:
	// 다른 멤버 함수들과 함께 위치하도록 적절한 위치에 추가
	int LoadSecondImageFile(CArchive& ar);

};