#include "stdafx.h"
#include <algorithm>
#include "GDIPlusEx.h"

//************************************************---------------------------
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

CGDIPlus::CGDIPlus()
{
	gdiplusToken=0;
	//GDI+��ʼ��
 GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CGDIPlus::~CGDIPlus()
{
	//GDI+�ر�
	if (0 != gdiplusToken)
	{
		GdiplusShutdown(gdiplusToken);
	}
}

/////////////////////////////////////////////////
//��������ChangeColor
//��  �ܣ�ת��Graphics::Color��ֵΪGdiplus::Color��ֵ
//��  ����aColor ��ת����ɫֵ
//��  �أ�Gdiplus::Color(Gdiplus������ɫֵ)
//˵������ת����ɫ
/////////////////////////////////////////////////
Gdiplus::Color ChangeColor(COLORREF aColor)
{
	int liRed,liGreen,liBlue;
	liRed = GetRValue(aColor);
	liGreen = GetGValue(aColor);
	liBlue = GetBValue(aColor);
	return  Color(liRed,liGreen,liBlue);
}

/////////////////////////////////////////////////
//��������ucFillRectangle
//��  �ܣ�����������
//��  ����DC (HDC) ��ͼ�豸
//		  aRect (RECT) ���ƾ�������
//		  aColor (COLORREF) �����ɫ
//		  abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵��������ɫ����������
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgColor = ChangeColor(aColor);
	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	SolidBrush lpBrush(lgColor);

	usGraphics.FillRectangle(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//��������usFillRectangle
//��  �ܣ�����������
//��  ����DC (HDC) ��ͼ�豸
//		  aRect (RECT) ���ƾ�������
//        aBeginColor (COLORREF) ��ʼ��ɫ
//        aEndColor (COLORREF) ������ɫ
//        aBeginPoint (POINT) ��ˢ��ʼ��
//        aEndPoint (POINT) ��ˢ������
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵����������ɫ����������
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, POINT aBeginPoint, POINT aEndPoint, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lBeginColor = ChangeColor(aBeginColor) ;
	Color lEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	}
	LinearGradientBrush linGrBrush(
		Point(aBeginPoint.x, aBeginPoint.y),
		Point(aEndPoint.x, aEndPoint.y),
		lBeginColor,
		lEndColor);
	usGraphics.FillRectangle(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//��������usFillRectangle
//��  �ܣ�����������
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aBeginColor (COLORREF) ���俪ʼ��ɫ
//        aEndColor (COLORREF) ���������ɫ
//        Orientation (ENUM_DrawOrientation) ���䷽��
//        abEclosion(BOOL) �Ƿ���
//��  �أ�NULL
//˵���������������򣬿�ѡ�񽥱䷽ʽ�����䷽���Լ�����У��
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgBeginColor = ChangeColor(aBeginColor);
	Color lgEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	}
	if (Orientation == edoVertical)
	{
		LinearGradientBrush linGrBrush(
			Point(aRect.left, aRect.top - 1),
			Point(aRect.left, aRect.bottom),
			lgBeginColor,
			lgEndColor);


		linGrBrush.SetGammaCorrection(TRUE);
		usGraphics.FillRectangle(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
	}
	else
	{
		LinearGradientBrush linGrBrush(
			Point(aRect.left - 1, aRect.top),
			Point(aRect.right, aRect.top),
			lgBeginColor,
			lgEndColor);


		linGrBrush.SetGammaCorrection(TRUE);
		usGraphics.FillRectangle(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
	}
}

/////////////////////////////////////////////////
//��������usFillRectangle
//��  �ܣ�������
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) �������
//        aColor (COLORREF) ����ɫ
//        aAlpha (INT) ����ɫ͸����(0~255)
//        abEclosion (BOOL) �Ƿ�֧����
//��  �أ�NULL
//˵������������ʱ�ɴ���ɫ͸������
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, INT aAlpha, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	INT liRed, liGreen, liBlue;
	liRed = GetRValue(aColor);
	liGreen = GetGValue(aColor);
	liBlue = GetBValue(aColor);
	Color lgColor(aAlpha, liRed, liGreen, liBlue);
	
	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������

	SolidBrush lpBrush(lgColor);
	usGraphics.FillRectangle(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//��������usFillCenterRectangle
//��  �ܣ�����������
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aCenterColor (COLORREF) �����м���ɫ
//        aSurroundColor (COLORREF) ������Χ��ɫ
//        afCenterWidth (FLOAT) �м佥�䷽ʽ�����������
//        afCenterHeight (FLOAT) �м佥�䷽ʽ�߶���������
//        abEclosion(BOOL) �Ƿ���
//��  �أ�NULL
//˵���������������򣬿�ѡ����������м佥��ķ�ʽ
/////////////////////////////////////////////////
void CGDIPlus::usFillCenterRectangle(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	GraphicsPath lpPath;

	lpPath.AddRectangle(Rect(aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top));

	PathGradientBrush pthGrBrush(&lpPath);
	pthGrBrush.SetGammaCorrection(TRUE);

	Color lSurroundColor = ChangeColor(aSurroundColor);
	Color lCenterColor = ChangeColor(aCenterColor);

	INT num = 1;
	pthGrBrush.SetSurroundColors(&lSurroundColor, &num);
	pthGrBrush.SetCenterColor(lCenterColor);
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);      //���١�������
	}
	pthGrBrush.SetFocusScales(afCenterWidth, afCenterHeight);

	usGraphics.FillPath(&pthGrBrush, &lpPath);
}

/////////////////////////////////////////////////
//��������usFillRound
//��  �ܣ�����������Բ
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aColor (COLORREF) �����ɫ
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵��������䵥ɫ��������Բ
/////////////////////////////////////////////////
void CGDIPlus::usFillRound(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgColor = ChangeColor(aColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	}
	SolidBrush lpBrush(lgColor);

	usGraphics.FillEllipse(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//��������usFillRound
//��  �ܣ�����������Բ
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aBeginColor (COLORREF) ���俪ʼ��ɫ
//        aEndColor (COLORREF) ���������ɫ
//        Orientation (ENUM_DrawOrientation) ���䷽��
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵����������������Բ����ѡ�񽥱䷽ʽ�����䷽���Լ�����У��
/////////////////////////////////////////////////
void CGDIPlus::usFillRound(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	
	Color lgBeginColor = ChangeColor(aBeginColor) ;
	Color lgEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	}
	if (Orientation == edoVertical)
	{
		LinearGradientBrush linGrBrush(
			Point(aRect.left, aRect.top - 1),
			Point(aRect.left, aRect.bottom),
			lgBeginColor,
			lgEndColor);


		linGrBrush.SetGammaCorrection(TRUE);
		usGraphics.FillEllipse(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
	}
	if (Orientation == edoHorizontal)
	{
		LinearGradientBrush linGrBrush(
			Point(aRect.left - 1, aRect.top),
			Point(aRect.right, aRect.top),
			lgBeginColor,
			lgEndColor);

		linGrBrush.SetGammaCorrection(TRUE);
		usGraphics.FillEllipse(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
	}
}

/////////////////////////////////////////////////
//��������usFillCenterRound
//��  �ܣ�����������Բ
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aCenterColor (COLORREF) �����м���ɫ
//        aSurroundColor (COLORREF) ������Χ��ɫ
//        afCenterWidth (FLOAT) �м佥�䷽ʽ�����������
//        afCenterHeight (FLOAT) �м佥�䷽ʽ�߶���������
//        abEclosion(BOOL) �Ƿ���
//��  �أ�NULL
//˵����������������Բ����ѡ����������м佥��ķ�ʽ
/////////////////////////////////////////////////
void CGDIPlus::usFillCenterRound(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	GraphicsPath lpPath;

	lpPath.AddEllipse(aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);

	PathGradientBrush pthGrBrush(&lpPath);
	pthGrBrush.SetGammaCorrection(TRUE);

	Color lSurroundColor = ChangeColor(aSurroundColor);
	Color lCenterColor = ChangeColor(aCenterColor);

	INT num = 1;
	pthGrBrush.SetSurroundColors(&lSurroundColor, &num);
	pthGrBrush.SetCenterColor(lCenterColor);
	
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������
	}
	pthGrBrush.SetFocusScales(afCenterWidth, afCenterHeight);

	usGraphics.FillPath(&pthGrBrush, &lpPath);
}

/////////////////////////////////////////////////
//��������usDrawRectangle
//��  �ܣ������α߿�
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aColor (COLORREF) ������ɫ
//        aiPenWidth (INT) ��ˢ���
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵�����������α߿�
/////////////////////////////////////////////////
void CGDIPlus::usDrawRectangle(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;
	
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //�߻��ʡ�����
	}

	Pen lpPen(lColor, afPenWidth);
	Rect lRect(aRect.left, aRect.top, aRect.right - aRect.left - 1, aRect.bottom - aRect.top );
	usGraphics.DrawRectangle(&lpPen, lRect);
}

/////////////////////////////////////////////////
//��������usDrawArc
//��  �ܣ�����
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aColor (COLORREF) ������ɫ
//        aiPenWidth (INT) ��ˢ���
//        aiBeginPosition (INT) ��ʼλ��
//        aiLength (INT) ����
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵����������
/////////////////////////////////////////////////
void CGDIPlus::usDrawArc(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, FLOAT afBeginPosition, FLOAT afLength, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;
	
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //�߻��ʡ�����
	}

	Pen lpPen(lColor, afPenWidth);
	usGraphics.DrawArc(&lpPen, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top, afBeginPosition, afLength);
}

/////////////////////////////////////////////////
//��������usDrawLine
//��  �ܣ����߶�
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aColor (COLORREF) ������ɫ
//        aiPenWidth (INT) ��ˢ���
//        aiBeginLeft (INT) ��ʼ��߾�
//        aiBeginTop (INT) ��ʼ�ϱ߾�
//        aiEndLeft (INT) ������߾�
//        aiEndTop (INT) �����ϱ߾�
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵���������߶�
/////////////////////////////////////////////////
void CGDIPlus::usDrawLine(HDC DC, COLORREF aColor, FLOAT afPenWidth, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //�߻��ʡ�����
	Pen lpPen(lColor, afPenWidth);

	usGraphics.DrawLine(&lpPen, aiBeginLeft, aiBeginTop, aiEndLeft, aiEndTop) ;
}

/////////////////////////////////////////////////
//��������usDrawLine
//��  �ܣ�����
//��  ����DC (HDC) ��ͼ�豸
//        aDashStyle (ENUM_DashStyle) ��ˢ���
//        aiPenWidth (INT) ��ˢ���
//        aColor (COLORREF) ������ɫ
//        aiBeginLeft (INT) ��ʼ��߾�
//        aiBeginTop (INT) ��ʼ�ϱ߾�
//        aiEndLeft (INT) ������߾�
//        aiEndTop (INT) �����ϱ߾�
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵���������ߣ��ɴ������߶η��
/////////////////////////////////////////////////
void CGDIPlus::usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, FLOAT afPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //�߻��ʡ�����
	Pen pen(lColor, afPenWidth);
	pen.SetDashStyle((DashStyle)(INT)aDashStyle);
	usGraphics.DrawLine(&pen, aiBeginLeft, aiBeginTop, aiEndLeft, aiEndTop);
}

/////////////////////////////////////////////////
//��������usFillRoundRectangle
//��  �ܣ���Բ�Ǿ���
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aBeginColor (COLORREF) ��ʼ��ɫ
//        aEndColor (COLORREF) ������ɫ
//        aBorderColor (COLORREF) �߿���ɫ
//        aiCornerRadius (INT) �Ƕ�
//        Orientation (ENUM_DrawOrientation) ����
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵��������Բ�Ǿ���
/////////////////////////////////////////////////
void CGDIPlus::usFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	usAdvanceFillRoundRectangle(DC, aRect, aBeginColor, aEndColor, aBorderColor, aiCornerRadius, Orientation, abEclosion, 255);
}
/////////////////////////////////////////////////
//��������usAdvanceFillRoundRectangle
//��  �ܣ���Բ�Ǿ���(�߼�)
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aBeginColor (COLORREF) ��ʼ��ɫ
//        aEndColor (COLORREF) ������ɫ
//        aBorderColor (COLORREF) �߿���ɫ
//        aiCornerRadius (INT) �Ƕ�
//        Orientation (ENUM_DrawOrientation) ����
//        abEclosion (BOOL) �Ƿ���
//        aiAlend (INT) ͸����(0~255)
//��  �أ�NULL
//˵��������Բ�Ǿ���(�ɿ���͸����)
/////////////////////////////////////////////////
void CGDIPlus::usAdvanceFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion, INT aiAlend)
{
	HRGN HrgnUpperLeft, HrgnUpperRight, HrgnLowerLeft, HrgnLowerRight, HrgnMidVertical, HrgnMidHorizontal;

	RECT lUpperLeftRect;
	lUpperLeftRect.left = aRect.left;
	lUpperLeftRect.top = aRect.top;
	lUpperLeftRect.right = aRect.left + aiCornerRadius;
	lUpperLeftRect.bottom = aRect.top + aiCornerRadius;
	RECT lUpperRightRect;
	lUpperRightRect.left = aRect.right - aiCornerRadius + 1;
	lUpperRightRect.top = aRect.top;
	lUpperRightRect.right = aRect.right + 1;
	lUpperRightRect.bottom = aRect.top + aiCornerRadius;
	RECT lLowerLeftRect;
	lLowerLeftRect.left = aRect.left;
	lLowerLeftRect.top = aRect.bottom - aiCornerRadius + 1;
	lLowerLeftRect.right = aRect.left + aiCornerRadius;
	lLowerLeftRect.bottom = aRect.bottom + 1;
	RECT lLowerRightRect;
	lLowerRightRect.left = aRect.right - aiCornerRadius + 1;
	lLowerRightRect.top = aRect.bottom - aiCornerRadius + 1;
	lLowerRightRect.right = aRect.right + 1;
	lLowerRightRect.bottom = aRect.bottom + 1;
	RECT lMidVerticalRect;
	lMidVerticalRect.left = aRect.left + aiCornerRadius / 2;
	lMidVerticalRect.top = aRect.top;
	lMidVerticalRect.right = aRect.right - aiCornerRadius / 2;
	lMidVerticalRect.bottom = aRect.bottom;
	RECT lMidHorizontalRect;
	lMidHorizontalRect.left = aRect.left;
	lMidHorizontalRect.top = aRect.top + aiCornerRadius / 2;
	lMidHorizontalRect.right = aRect.right;
	lMidHorizontalRect.bottom = aRect.bottom - aiCornerRadius / 2;

	HrgnUpperLeft = CreateEllipticRgn(lUpperLeftRect.left, lUpperLeftRect.top, lUpperLeftRect.right, lUpperLeftRect.bottom);           //��ȡ������
	HrgnUpperRight = CreateEllipticRgn(lUpperRightRect.left, lUpperRightRect.top, lUpperRightRect.right, lUpperRightRect.bottom);
	HrgnLowerLeft = CreateEllipticRgn(lLowerLeftRect.left, lLowerLeftRect.top, lLowerLeftRect.right, lLowerLeftRect.bottom);
	HrgnLowerRight = CreateEllipticRgn(lLowerRightRect.left, lLowerRightRect.top, lLowerRightRect.right, lLowerRightRect.bottom);

	HrgnMidVertical = CreateRectRgn(lMidVerticalRect.left, lMidVerticalRect.top, lMidVerticalRect.right, lMidVerticalRect.bottom);      //��ȡ��������
	HrgnMidHorizontal = CreateRectRgn(lMidHorizontalRect.left, lMidHorizontalRect.top, lMidHorizontalRect.right, lMidHorizontalRect.bottom);

	//�ϲ�����
	HRGN hMergeHrgn;
	hMergeHrgn = CreateRectRgn(aRect.left, aRect.top, aRect.left, aRect.top);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnUpperLeft, RGN_OR);                                                                       //��ȡԲ�Ǿ���
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnUpperRight, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnLowerLeft, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnLowerRight, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnMidVertical, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnMidHorizontal, RGN_OR);

	Graphics usGraphics(DC);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //�߻��ʡ�����

	INT R, G, B;
	R = GetRValue(aBeginColor);
	G = GetGValue(aBeginColor);
	B = GetBValue(aBeginColor);
	Gdiplus::Color lBeginColor(aiAlend, R, G, B);			//�����ɫ
	R = GetRValue(aEndColor);
	G = GetGValue(aEndColor);
	B = GetBValue(aEndColor);
	Gdiplus::Color lEndColor(aiAlend, R, G, B);				//�յ���ɫ

	Gdiplus::Point lpPointBegin;
	Gdiplus::Point lpPointEnd;

	if (Orientation == edoVertical)                         //��ֱ����
	{
		lpPointBegin = Point(aRect.left, aRect.top);
		lpPointEnd = Point(aRect.left, aRect.bottom);
	}
	else                                                    //ˮƽ����3
	{
		lpPointBegin = Point(aRect.left, aRect.top);
		lpPointEnd = Point(aRect.right, aRect.top);

	}                                                                  
	LinearGradientBrush linGrBrush(							//����GDI+����ˢ
		lpPointBegin,
		lpPointEnd,
		lBeginColor,
		lEndColor);                
	Region RegionMerge(hMergeHrgn);							//��ȡGDI+ Region

	usGraphics.FillRegion(&linGrBrush, &RegionMerge);

	usDrawLine(DC, aBorderColor, 1, lMidVerticalRect.left - 1, lMidVerticalRect.top, lMidVerticalRect.right, lMidVerticalRect.top, abEclosion); //���α���
	usDrawLine(DC, aBorderColor, 1, lMidVerticalRect.left - 1, lMidVerticalRect.bottom - 1, lMidVerticalRect.right, lMidVerticalRect.bottom - 1, abEclosion);
	usDrawLine(DC, aBorderColor, 1, lMidHorizontalRect.left, lMidHorizontalRect.top, lMidHorizontalRect.left, lMidHorizontalRect.bottom, abEclosion);
	usDrawLine(DC, aBorderColor, 1, lMidHorizontalRect.right - 1, lMidHorizontalRect.top, lMidHorizontalRect.right - 1, lMidHorizontalRect.bottom, abEclosion);

	RECT lRect;
	//����
	lRect.left = lUpperLeftRect.left;
	lRect.top = lUpperLeftRect.top;
	lRect.right = lUpperLeftRect.right - 1;
	lRect.bottom = lUpperLeftRect.bottom - 1;
	usDrawArc(DC, lRect, aBorderColor, 1, 180, 90, TRUE);
	lRect.left = lUpperRightRect.left - 1;
	lRect.top = lUpperRightRect.top;
	lRect.right = lUpperRightRect.right - 2;
	lRect.bottom = lUpperRightRect.bottom - 1;
	usDrawArc(DC, lRect, aBorderColor, 1, 270, 90, TRUE);
	lRect.left = lLowerLeftRect.left;
	lRect.top = lLowerLeftRect.top - 1;
	lRect.right = lLowerLeftRect.right - 1;
	lRect.bottom = lLowerLeftRect.bottom - 2;
	usDrawArc(DC, lRect, aBorderColor, 1, 90, 90, TRUE);
	lRect.left = lLowerRightRect.left - 1;
	lRect.top = lLowerRightRect.top - 1;
	lRect.right = lLowerRightRect.right - 2;
	lRect.bottom = lLowerRightRect.bottom - 2;
	usDrawArc(DC, lRect, aBorderColor, 1, 0, 90, TRUE);

	DeleteObject(HrgnUpperLeft);
	DeleteObject(HrgnUpperRight);
	DeleteObject(HrgnLowerLeft);
	DeleteObject(HrgnLowerRight);
	DeleteObject(HrgnMidVertical);
	DeleteObject(HrgnMidHorizontal);
	DeleteObject(hMergeHrgn);
}

/////////////////////////////////////////////////
//��������usDrawArrow
//��  �ܣ������Ǽ�ͷ
//��  ����DC (HDC) ��ͼ�豸
//        aColor (COLORREF) ��ͷ��ɫ
//        aiFirstLeft (INT) ��һ����߾�
//        aiFirstTop (INT) ��һ���ϱ߾�
//        aiSecondLeft (INT) �ڶ�����߾�
//        aiSecondTop (INT) �ڶ����ϱ߾�
//        aiThirdLeft (INT) ��������߾�
//        aiThirdTop (INT) �������ϱ߾�
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵�����������Ǽ�ͷ
/////////////////////////////////////////////////
void CGDIPlus::usDrawArrow(HDC DC, COLORREF aColor, INT aiFirstLeft, INT aiFirstTop, INT aiSecondLeft, INT aiSecondTop, INT aiThirdLeft, INT aiThirdTop, BOOL aEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor);
	
	SolidBrush lpBrush(lColor);
	Point Points[] = {Point(aiFirstLeft, aiFirstTop),
		Point(aiSecondLeft, aiSecondTop),
		Point(aiThirdLeft, aiThirdTop),
		Point(50, 60)};
	if (aEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //�߻��ʡ�����

	usGraphics.FillPolygon(&lpBrush, Points, 3);
}

/////////////////////////////////////////////////
//��������usFillRoundCorner
//��  �ܣ���仡�Ƚ�
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) ���ƾ�������
//        aiRadius (INT) ����
//        aBeginColor (COLORREF) ��ʼ��ɫ
//        aEndColor (COLORREF) ������ɫ
//        Corner (ENUM_Corner) ����ĸ�������֮һ
//        abEclosion (BOOL) �Ƿ���
//��  �أ�NULL
//˵��������仡�Ƚǣ��������������Ƚ�����Ľǿհ�
/////////////////////////////////////////////////
void CGDIPlus::usFillRoundCorner(HDC DC, RECT aRect, INT aiRadius, COLORREF aBeginColor, COLORREF aEndColor, ENUM_Corner Corner, BOOL abEclosion)
{
	HRGN hrgnCombine, hrgnElliptic, hrgnRect;
	hrgnCombine = CreateRectRgn(aRect.left, aRect.top, aRect.right, aRect.bottom);

	switch (Corner)
	{
	case ecLeftTop:
		{
			hrgnRect = CreateRectRgn(aRect.left, aRect.top, aRect.left + aiRadius, aRect.top + aiRadius);
			hrgnElliptic = CreateEllipticRgn(aRect.left, aRect.top, aRect.left + aiRadius * 2, aRect.top + aiRadius * 2);
		}
		break;
	case ecRightTop:
		{
			hrgnRect = CreateRectRgn(aRect.right - aiRadius, aRect.top, aRect.right, aRect.top + aiRadius);
			hrgnElliptic = CreateEllipticRgn(aRect.right - aiRadius * 2, aRect.top, aRect.right, aRect.top + aiRadius * 2);
		}
		break;
	case ecLeftBottom:
		{
			hrgnRect = CreateRectRgn(aRect.left, aRect.bottom - aiRadius, aRect.left + aiRadius, aRect.bottom);
			hrgnElliptic = CreateEllipticRgn(aRect.left, aRect.bottom - aiRadius * 2, aRect.left + aiRadius * 2, aRect.bottom);
		}
		break;
	case ecRightBottom:
		{
			hrgnRect = CreateRectRgn(aRect.right - aiRadius, aRect.bottom - aiRadius, aRect.right, aRect.bottom);
			hrgnElliptic = CreateEllipticRgn(aRect.right - aiRadius * 2, aRect.bottom - aiRadius * 2, aRect.right, aRect.bottom);
		}
		break;
	default:
		return;
	}

	CombineRgn(hrgnCombine, hrgnCombine, hrgnElliptic, RGN_DIFF);
	CombineRgn(hrgnCombine, hrgnCombine, hrgnRect, RGN_AND);

	Graphics usGraphics(DC);

	if(abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������

	Gdiplus::Region gRgnCombine(hrgnCombine);

	Color lBeginColor = ChangeColor(aBeginColor);
	Color lEndColor = ChangeColor(aEndColor);
	Point lpPointBegin(aRect.left, aRect.top);
	Point lpPointEnd(aRect.left, aRect.bottom);
	LinearGradientBrush linGrBrush(
		lpPointBegin,
		lpPointEnd,
		lBeginColor,
		lEndColor);

	usGraphics.FillRegion(&linGrBrush, &gRgnCombine);
	DeleteObject(hrgnElliptic);
	DeleteObject(hrgnRect);
	DeleteObject(hrgnCombine);
}

/////////////////////////////////////////////////
//��������usFillPolygon
//��  �ܣ���������
//��  ����DC (HDC) ��ͼ�豸
//        aBeginColor (COLORREF) ��ʼ��ɫ
//        aEndColor (COLORREF) ������ɫ
//        apPoint1 (POINT) ��һ��
//        apPoint2 (POINT) �ڶ���
//        apPoint3 (POINT) ������
//        apPoint4 (POINT) ���ĵ�
//        apPoint5 (POINT) �����
//        abEclosion (BOOL) �Ƿ���
//        abEclosion (BOOL) ����У��
//��  �أ�NULL
//˵��������������
/////////////////////////////////////////////////
void CGDIPlus::usFillPolygon(HDC DC, COLORREF aBeginColor, COLORREF aEndColor, POINT apPoint1, POINT apPoint2, POINT apPoint3, POINT apPoint4, POINT apPoint5, BOOL abEclosion, BOOL abGammaCorrection)
{
	Graphics usGraphics(DC);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //���١�������

	Color lBeginColor = ChangeColor(aBeginColor);
	Color lEndColor = ChangeColor(aEndColor);
	Point lpPointBegin;
	Point lpPointEnd;

	LONG liBeginY=0, liEndY=0;
	LONG liFlag = 0;

	if (apPoint1.y == apPoint2.y)
	{
		liFlag = 1;
		liBeginY = apPoint1.y;
	}
	if (apPoint2.y == apPoint3.y)
	{
		if (liFlag == 1)
			liEndY = apPoint2.y;
		else
		{
			liBeginY = apPoint2.y;
			liFlag = 1;
		}
	}
	if (apPoint3.y == apPoint4.y)
	{
		if (liFlag == 1)
			liEndY = apPoint3.y;
		else
		{
			liBeginY = apPoint3.y;
			liFlag = 1;
		}
	}
	if (apPoint4.y == apPoint5.y)
	{
		if (liFlag == 1)
			liEndY = apPoint4.y;
		else
		{
			liBeginY = apPoint4.y;
			liFlag = 1;
		}
	}
	if (apPoint5.y == apPoint1.y)
	{
		if (liFlag == 1)
			liEndY = apPoint5.y;
		else
		{
			liBeginY = apPoint5.y;
			liFlag = 1;
		}
	}

	if (liBeginY > liEndY)
	{
		lpPointBegin = Point(apPoint1.x, liBeginY);
		lpPointEnd = Point(apPoint1.x, liEndY);
	}
	else
	{
		lpPointBegin = Point(apPoint1.x, liEndY);
		lpPointEnd = Point(apPoint1.x, liBeginY);
	}
	LinearGradientBrush linGrBrush(
		lpPointBegin,
		lpPointEnd,
		lBeginColor,
		lEndColor);
	Point Points[] = {Point(apPoint1.x, apPoint1.y),
		Point(apPoint2.x, apPoint2.y),
		Point(apPoint3.x, apPoint3.y),
		Point(apPoint4.x, apPoint4.y),
		Point(apPoint5.x, apPoint5.y)
	};

	linGrBrush.SetGammaCorrection(abGammaCorrection);
	usGraphics.FillPolygon(&linGrBrush, Points, 5);
}

/////////////////////////////////////////////////
//��������usFillCenterPolygon
//��  �ܣ��������
//��  ����DC (HDC) ��ͼ�豸
//        aSurroundColor (COLORREF) ������Χ��ɫ
//        aCenterColor (COLORREF) �����м���ɫ
//        apPoint1 (POINT) ��һ��
//        apPoint2 (POINT) �ڶ���
//        apPoint3 (POINT) ������
//        apPoint4 (POINT) ���ĵ�
//        apPoint5 (POINT) �����
//        afCenterWidth (FLOAT) �м佥�䷽ʽ�����������
//        afCenterHeight (FLOAT) �м佥�䷽ʽ�����������
//        abEclosion (BOOL) �Ƿ���
//        abGammaCorrection (BOOL) ����У��
//��  �أ�NULL
//˵������������Σ���ѡ����������м佥��ķ�ʽ
/////////////////////////////////////////////////
void CGDIPlus::usFillCenterPolygon(HDC DC, COLORREF aSurroundColor, COLORREF aCenterColor, POINT aPoint1, POINT aPoint2, POINT aPoint3, POINT aPoint4, POINT aPoint5, FLOAT afCenterWidth, FLOAT afCenterLength, BOOL abEclosion, BOOL abGammaCorrection)
{
	Graphics usGraphics(DC);

	GraphicsPath lpPath;
	Point Points[] = {Point(aPoint1.x, aPoint1.y),
		Point(aPoint2.x, aPoint2.y),
		Point(aPoint3.x, aPoint3.y),
		Point(aPoint4.x, aPoint4.y),
		Point(aPoint5.x, aPoint5.y)
	};
	lpPath.AddLines(Points, 5);

	PathGradientBrush pthGrBrush(&lpPath);
	pthGrBrush.SetGammaCorrection(abGammaCorrection);

	Color lSurroundColor  = ChangeColor(aSurroundColor);
	Color lCenterColor  = ChangeColor(aCenterColor);

	INT liNum = 1;
	pthGrBrush.SetSurroundColors(&lSurroundColor, &liNum);
	pthGrBrush.SetCenterColor(lCenterColor);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);

	pthGrBrush.SetFocusScales(afCenterWidth, afCenterLength);
	usGraphics.FillPath(&pthGrBrush, &lpPath);
}

/////////////////////////////////////////////////
//��������usFillHatchRect
//��  �ܣ����Ӱ�߷��ľ���
//��  ����DC (HDC) ��ͼ�豸
//        aRect (RECT) �������
//        aFrontColor (COLORREF) ǰ��ɫ
//        aiFrontAlend (INT) ǰ��ɫ͸����(0~255)
//        aBackColor (COLORREF) ����ɫ
//        aiBackAlend (INT) ����ɫ͸����
//        aiStyle (INT) ��ѡ���(0~54)
//��  �أ�NULL
//˵���������Ӱ�߷��ľ���
/////////////////////////////////////////////////
void CGDIPlus::usFillHatchRect(HDC DC, RECT aRect, COLORREF aFrontColor, INT aiFrontAlend, COLORREF aBackColor, INT aiBackAlend, INT aiStyle)
{

	Graphics usGraphics(DC);

	INT R, G, B;
	R = GetRValue(aFrontColor);
	G = GetGValue(aFrontColor);
	B = GetBValue(aFrontColor);

	Color lFrontColor(aiFrontAlend, R, G, B);
	R = GetRValue(aBackColor);
	G = GetGValue(aBackColor);
	B = GetBValue(aBackColor);

	Color lBackColor(aiBackAlend, R, G, B);
	HatchBrush lHatchBrush(HatchStyle(aiStyle), lFrontColor, lBackColor);
	Rect lRect(aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
	usGraphics.FillRectangle(&lHatchBrush, lRect);
}
