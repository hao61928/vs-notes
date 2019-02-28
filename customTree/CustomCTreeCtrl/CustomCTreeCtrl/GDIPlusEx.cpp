#include "stdafx.h"
#include <algorithm>
#include "GDIPlusEx.h"

//************************************************---------------------------
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

CGDIPlus::CGDIPlus()
{
	gdiplusToken=0;
	//GDI+初始化
 GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CGDIPlus::~CGDIPlus()
{
	//GDI+关闭
	if (0 != gdiplusToken)
	{
		GdiplusShutdown(gdiplusToken);
	}
}

/////////////////////////////////////////////////
//函数名：ChangeColor
//功  能：转换Graphics::Color的值为Gdiplus::Color的值
//参  数：aColor 被转换颜色值
//返  回：Gdiplus::Color(Gdiplus类型颜色值)
//说　明：转换颜色
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
//函数名：ucFillRectangle
//功  能：填充矩形区域
//参  数：DC (HDC) 绘图设备
//		  aRect (RECT) 绘制矩形区域
//		  aColor (COLORREF) 填充颜色
//		  abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：单色填充矩形区域
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgColor = ChangeColor(aColor);
	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
	SolidBrush lpBrush(lgColor);

	usGraphics.FillRectangle(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//函数名：usFillRectangle
//功  能：填充矩形区域
//参  数：DC (HDC) 绘图设备
//		  aRect (RECT) 绘制矩形区域
//        aBeginColor (COLORREF) 起始颜色
//        aEndColor (COLORREF) 结束颜色
//        aBeginPoint (POINT) 画刷起始点
//        aEndPoint (POINT) 画刷结束点
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：渐变色填充矩形区域
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, POINT aBeginPoint, POINT aEndPoint, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lBeginColor = ChangeColor(aBeginColor) ;
	Color lEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
	}
	LinearGradientBrush linGrBrush(
		Point(aBeginPoint.x, aBeginPoint.y),
		Point(aEndPoint.x, aEndPoint.y),
		lBeginColor,
		lEndColor);
	usGraphics.FillRectangle(&linGrBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//函数名：usFillRectangle
//功  能：填充矩形区域
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aBeginColor (COLORREF) 渐变开始颜色
//        aEndColor (COLORREF) 渐变结束颜色
//        Orientation (ENUM_DrawOrientation) 渐变方向
//        abEclosion(BOOL) 是否羽化
//返  回：NULL
//说　明：填充矩形区域，可选择渐变方式及渐变方向，以及亮度校正
/////////////////////////////////////////////////
void CGDIPlus::usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgBeginColor = ChangeColor(aBeginColor);
	Color lgEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
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
//函数名：usFillRectangle
//功  能：填充矩形
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 填充区域
//        aColor (COLORREF) 背景色
//        aAlpha (INT) 背景色透明度(0~255)
//        abEclosion (BOOL) 是否支持羽化
//返  回：NULL
//说　明：填充矩形时可带颜色透明参数
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
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量

	SolidBrush lpBrush(lgColor);
	usGraphics.FillRectangle(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//函数名：usFillCenterRectangle
//功  能：填充矩形区域
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aCenterColor (COLORREF) 渐变中间颜色
//        aSurroundColor (COLORREF) 渐变周围颜色
//        afCenterWidth (FLOAT) 中间渐变方式宽度向量调整
//        afCenterHeight (FLOAT) 中间渐变方式高度向量调整
//        abEclosion(BOOL) 是否羽化
//返  回：NULL
//说　明：填充矩形区域，可选择从两边向中间渐变的方式
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
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);      //低速、高质量
	}
	pthGrBrush.SetFocusScales(afCenterWidth, afCenterHeight);

	usGraphics.FillPath(&pthGrBrush, &lpPath);
}

/////////////////////////////////////////////////
//函数名：usFillRound
//功  能：填充矩形内切圆
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aColor (COLORREF) 填充颜色
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：填充单色矩形内切圆
/////////////////////////////////////////////////
void CGDIPlus::usFillRound(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lgColor = ChangeColor(aColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
	}
	SolidBrush lpBrush(lgColor);

	usGraphics.FillEllipse(&lpBrush, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top);
}

/////////////////////////////////////////////////
//函数名：usFillRound
//功  能：填充矩形内切圆
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aBeginColor (COLORREF) 渐变开始颜色
//        aEndColor (COLORREF) 渐变结束颜色
//        Orientation (ENUM_DrawOrientation) 渐变方向
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：填充矩形内切圆，可选择渐变方式及渐变方向，以及亮度校正
/////////////////////////////////////////////////
void CGDIPlus::usFillRound(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	
	Color lgBeginColor = ChangeColor(aBeginColor) ;
	Color lgEndColor = ChangeColor(aEndColor) ;
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
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
//函数名：usFillCenterRound
//功  能：填充矩形内切圆
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aCenterColor (COLORREF) 渐变中间颜色
//        aSurroundColor (COLORREF) 渐变周围颜色
//        afCenterWidth (FLOAT) 中间渐变方式宽度向量调整
//        afCenterHeight (FLOAT) 中间渐变方式高度向量调整
//        abEclosion(BOOL) 是否羽化
//返  回：NULL
//说　明：填充矩形内切圆，可选择从两边向中间渐变的方式
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
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量
	}
	pthGrBrush.SetFocusScales(afCenterWidth, afCenterHeight);

	usGraphics.FillPath(&pthGrBrush, &lpPath);
}

/////////////////////////////////////////////////
//函数名：usDrawRectangle
//功  能：画矩形边框
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aColor (COLORREF) 画笔颜色
//        aiPenWidth (INT) 笔刷宽度
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画矩形边框
/////////////////////////////////////////////////
void CGDIPlus::usDrawRectangle(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;
	
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //高画质、低速
	}

	Pen lpPen(lColor, afPenWidth);
	Rect lRect(aRect.left, aRect.top, aRect.right - aRect.left - 1, aRect.bottom - aRect.top );
	usGraphics.DrawRectangle(&lpPen, lRect);
}

/////////////////////////////////////////////////
//函数名：usDrawArc
//功  能：画弧
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aColor (COLORREF) 画笔颜色
//        aiPenWidth (INT) 笔刷宽度
//        aiBeginPosition (INT) 起始位置
//        aiLength (INT) 弧长
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画弧
/////////////////////////////////////////////////
void CGDIPlus::usDrawArc(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, FLOAT afBeginPosition, FLOAT afLength, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;
	
	if (abEclosion)
	{
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //高画质、低速
	}

	Pen lpPen(lColor, afPenWidth);
	usGraphics.DrawArc(&lpPen, aRect.left, aRect.top, aRect.right - aRect.left, aRect.bottom - aRect.top, afBeginPosition, afLength);
}

/////////////////////////////////////////////////
//函数名：usDrawLine
//功  能：画线段
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aColor (COLORREF) 画笔颜色
//        aiPenWidth (INT) 笔刷宽度
//        aiBeginLeft (INT) 起始左边距
//        aiBeginTop (INT) 起始上边距
//        aiEndLeft (INT) 结束左边距
//        aiEndTop (INT) 结束上边距
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画线段
/////////////////////////////////////////////////
void CGDIPlus::usDrawLine(HDC DC, COLORREF aColor, FLOAT afPenWidth, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor) ;

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
	Pen lpPen(lColor, afPenWidth);

	usGraphics.DrawLine(&lpPen, aiBeginLeft, aiBeginTop, aiEndLeft, aiEndTop) ;
}

/////////////////////////////////////////////////
//函数名：usDrawLine
//功  能：画线
//参  数：DC (HDC) 绘图设备
//        aDashStyle (ENUM_DashStyle) 笔刷风格
//        aiPenWidth (INT) 笔刷宽度
//        aColor (COLORREF) 画笔颜色
//        aiBeginLeft (INT) 起始左边距
//        aiBeginTop (INT) 起始上边距
//        aiEndLeft (INT) 结束左边距
//        aiEndTop (INT) 结束上边距
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画线，可带多种线段风格
/////////////////////////////////////////////////
void CGDIPlus::usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, FLOAT afPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion)
{
	Graphics usGraphics(DC);
	Color lColor = ChangeColor(aColor);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速
	Pen pen(lColor, afPenWidth);
	pen.SetDashStyle((DashStyle)(INT)aDashStyle);
	usGraphics.DrawLine(&pen, aiBeginLeft, aiBeginTop, aiEndLeft, aiEndTop);
}

/////////////////////////////////////////////////
//函数名：usFillRoundRectangle
//功  能：画圆角矩形
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aBeginColor (COLORREF) 起始颜色
//        aEndColor (COLORREF) 结束颜色
//        aBorderColor (COLORREF) 边框颜色
//        aiCornerRadius (INT) 角度
//        Orientation (ENUM_DrawOrientation) 方向
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画圆角矩形
/////////////////////////////////////////////////
void CGDIPlus::usFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion)
{
	usAdvanceFillRoundRectangle(DC, aRect, aBeginColor, aEndColor, aBorderColor, aiCornerRadius, Orientation, abEclosion, 255);
}
/////////////////////////////////////////////////
//函数名：usAdvanceFillRoundRectangle
//功  能：画圆角矩形(高级)
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aBeginColor (COLORREF) 起始颜色
//        aEndColor (COLORREF) 结束颜色
//        aBorderColor (COLORREF) 边框颜色
//        aiCornerRadius (INT) 角度
//        Orientation (ENUM_DrawOrientation) 方向
//        abEclosion (BOOL) 是否羽化
//        aiAlend (INT) 透明度(0~255)
//返  回：NULL
//说　明：画圆角矩形(可控制透明度)
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

	HrgnUpperLeft = CreateEllipticRgn(lUpperLeftRect.left, lUpperLeftRect.top, lUpperLeftRect.right, lUpperLeftRect.bottom);           //获取四区域
	HrgnUpperRight = CreateEllipticRgn(lUpperRightRect.left, lUpperRightRect.top, lUpperRightRect.right, lUpperRightRect.bottom);
	HrgnLowerLeft = CreateEllipticRgn(lLowerLeftRect.left, lLowerLeftRect.top, lLowerLeftRect.right, lLowerLeftRect.bottom);
	HrgnLowerRight = CreateEllipticRgn(lLowerRightRect.left, lLowerRightRect.top, lLowerRightRect.right, lLowerRightRect.bottom);

	HrgnMidVertical = CreateRectRgn(lMidVerticalRect.left, lMidVerticalRect.top, lMidVerticalRect.right, lMidVerticalRect.bottom);      //获取矩形区域
	HrgnMidHorizontal = CreateRectRgn(lMidHorizontalRect.left, lMidHorizontalRect.top, lMidHorizontalRect.right, lMidHorizontalRect.bottom);

	//合并区域
	HRGN hMergeHrgn;
	hMergeHrgn = CreateRectRgn(aRect.left, aRect.top, aRect.left, aRect.top);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnUpperLeft, RGN_OR);                                                                       //获取圆角矩形
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnUpperRight, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnLowerLeft, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnLowerRight, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnMidVertical, RGN_OR);
	CombineRgn(hMergeHrgn, hMergeHrgn, HrgnMidHorizontal, RGN_OR);

	Graphics usGraphics(DC);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速

	INT R, G, B;
	R = GetRValue(aBeginColor);
	G = GetGValue(aBeginColor);
	B = GetBValue(aBeginColor);
	Gdiplus::Color lBeginColor(aiAlend, R, G, B);			//起点颜色
	R = GetRValue(aEndColor);
	G = GetGValue(aEndColor);
	B = GetBValue(aEndColor);
	Gdiplus::Color lEndColor(aiAlend, R, G, B);				//终点颜色

	Gdiplus::Point lpPointBegin;
	Gdiplus::Point lpPointEnd;

	if (Orientation == edoVertical)                         //垂直渐进
	{
		lpPointBegin = Point(aRect.left, aRect.top);
		lpPointEnd = Point(aRect.left, aRect.bottom);
	}
	else                                                    //水平渐进3
	{
		lpPointBegin = Point(aRect.left, aRect.top);
		lpPointEnd = Point(aRect.right, aRect.top);

	}                                                                  
	LinearGradientBrush linGrBrush(							//生成GDI+渐进刷
		lpPointBegin,
		lpPointEnd,
		lBeginColor,
		lEndColor);                
	Region RegionMerge(hMergeHrgn);							//获取GDI+ Region

	usGraphics.FillRegion(&linGrBrush, &RegionMerge);

	usDrawLine(DC, aBorderColor, 1, lMidVerticalRect.left - 1, lMidVerticalRect.top, lMidVerticalRect.right, lMidVerticalRect.top, abEclosion); //矩形边线
	usDrawLine(DC, aBorderColor, 1, lMidVerticalRect.left - 1, lMidVerticalRect.bottom - 1, lMidVerticalRect.right, lMidVerticalRect.bottom - 1, abEclosion);
	usDrawLine(DC, aBorderColor, 1, lMidHorizontalRect.left, lMidHorizontalRect.top, lMidHorizontalRect.left, lMidHorizontalRect.bottom, abEclosion);
	usDrawLine(DC, aBorderColor, 1, lMidHorizontalRect.right - 1, lMidHorizontalRect.top, lMidHorizontalRect.right - 1, lMidHorizontalRect.bottom, abEclosion);

	RECT lRect;
	//无羽化
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
//函数名：usDrawArrow
//功  能：画三角箭头
//参  数：DC (HDC) 绘图设备
//        aColor (COLORREF) 箭头颜色
//        aiFirstLeft (INT) 第一点左边距
//        aiFirstTop (INT) 第一点上边距
//        aiSecondLeft (INT) 第二点左边距
//        aiSecondTop (INT) 第二点上边距
//        aiThirdLeft (INT) 第三点左边距
//        aiThirdTop (INT) 第三点上边距
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：画三角箭头
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
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality); //高画质、低速

	usGraphics.FillPolygon(&lpBrush, Points, 3);
}

/////////////////////////////////////////////////
//函数名：usFillRoundCorner
//功  能：填充弧度角
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 绘制矩形区域
//        aiRadius (INT) 弧度
//        aBeginColor (COLORREF) 起始颜色
//        aEndColor (COLORREF) 结束颜色
//        Corner (ENUM_Corner) 填充四个角其中之一
//        abEclosion (BOOL) 是否羽化
//返  回：NULL
//说　明：填充弧度角，可用来填充带弧度角组件的角空白
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
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量

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
//函数名：usFillPolygon
//功  能：填充五边形
//参  数：DC (HDC) 绘图设备
//        aBeginColor (COLORREF) 起始颜色
//        aEndColor (COLORREF) 结束颜色
//        apPoint1 (POINT) 第一点
//        apPoint2 (POINT) 第二点
//        apPoint3 (POINT) 第三点
//        apPoint4 (POINT) 第四点
//        apPoint5 (POINT) 第五点
//        abEclosion (BOOL) 是否羽化
//        abEclosion (BOOL) 亮度校正
//返  回：NULL
//说　明：填充五边形
/////////////////////////////////////////////////
void CGDIPlus::usFillPolygon(HDC DC, COLORREF aBeginColor, COLORREF aEndColor, POINT apPoint1, POINT apPoint2, POINT apPoint3, POINT apPoint4, POINT apPoint5, BOOL abEclosion, BOOL abGammaCorrection)
{
	Graphics usGraphics(DC);

	if (abEclosion)
		usGraphics.SetSmoothingMode(SmoothingModeHighQuality);     //低速、高质量

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
//函数名：usFillCenterPolygon
//功  能：填充多边形
//参  数：DC (HDC) 绘图设备
//        aSurroundColor (COLORREF) 渐变周围颜色
//        aCenterColor (COLORREF) 渐变中间颜色
//        apPoint1 (POINT) 第一点
//        apPoint2 (POINT) 第二点
//        apPoint3 (POINT) 第三点
//        apPoint4 (POINT) 第四点
//        apPoint5 (POINT) 第五点
//        afCenterWidth (FLOAT) 中间渐变方式宽度向量调整
//        afCenterHeight (FLOAT) 中间渐变方式宽度向量调整
//        abEclosion (BOOL) 是否羽化
//        abGammaCorrection (BOOL) 亮度校正
//返  回：NULL
//说　明：填充多边形，可选择从两边向中间渐变的方式
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
//函数名：usFillHatchRect
//功  能：填充影线风格的矩形
//参  数：DC (HDC) 绘图设备
//        aRect (RECT) 填充区域
//        aFrontColor (COLORREF) 前景色
//        aiFrontAlend (INT) 前景色透明度(0~255)
//        aBackColor (COLORREF) 背景色
//        aiBackAlend (INT) 背景色透明度
//        aiStyle (INT) 可选风格(0~54)
//返  回：NULL
//说　明：填充影线风格的矩形
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
