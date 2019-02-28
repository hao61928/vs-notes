#ifndef USGdiplusExH
#define USGdiplusExH

//加载DGI+所需文件
#include "gdiplus.h"
using namespace Gdiplus;
#pragma  comment(lib,"gdiplus.lib")

#ifndef _US_EXT_CLASS
#define _US_EXT_CLASS	__declspec(dllexport) 
#endif

const long clBlack  = 0x000000;
const long clWhite  = 0xffffff;
const long clSilver = 0xc0c0c0;
const long clGray   = 0xc0c0c0;
const long clBlue   = 0xff0000;

enum ENUM_DrawOrientation {edoHorizontal, edoVertical};     //绘制方向
enum ENUM_Corner {ecLeftTop, ecRightTop, ecLeftBottom, ecRightBottom};     //四个角
enum ENUM_DashStyle {
	UCDashStyleSolid = 0,       //实线
	UCDashStyleDash = 1,        //虚线
	UCDashStyleDot = 2,         //点线
	UCDashStyleDashDot = 3,     //点划线
	UCDashStyleDashDotDot = 4,  //双点划线
	UCDashStyleCustom = 5,      //自定义线
};

class  CGDIPlus  
{
public:
	CGDIPlus();
	virtual ~CGDIPlus();

	/////////////////////////////////////////////////
	//函数名：usFillRectangle
	//功  能：填充矩形区域
	//参  数：DC (HDC) 绘图设备
	//		  aRect (RECT) 绘制矩形区域
	//		  aColor (COLORREF) 填充颜色
	//		  abEclosion (BOOL) 是否羽化
	//返  回：NULL
	//说　明：单色填充矩形区域
	/////////////////////////////////////////////////
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, POINT aBeginPoint, POINT aEndPoint, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, INT aAlpha, BOOL abEclosion);

		
		
	/////////////////////////////////////////////////
	//函数名：usFillCenterRectangle
	//功  能：填充矩形区域
	//参  数：DC (HDC) 绘图设备
	//        aRect (RECT) 绘制矩形区域
	//        aCenterColor (COLORREF) 渐变中间颜色
	//        aSurroundColor (COLORREF) 渐变周围颜色
	//        afCenterWidth (FLOAT) 中间渐变方式宽度向量调整
	//        afCenterHeight (FLOAT) 中间渐变方式高度向量调整
	//        abEclosion(bool) 是否羽化
	//返  回：NULL
	//说　明：填充矩形区域，可选择从两边向中间渐变的方式
	/////////////////////////////////////////////////
	void usFillCenterRectangle(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion);



	/////////////////////////////////////////////////
	//函数名：usFillRound
	//功  能：填充矩形内切圆
	//参  数：DC (HDC) 绘图设备
	//        aRect (RECT) 绘制矩形区域
	//        aColor (COLORREF) 填充颜色
	//        abEclosion(BOOL) 是否羽化
	//返  回：NULL
	//说　明：填充单色矩形内切圆
	/////////////////////////////////////////////////
	void usFillRound(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion);



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
	void usFillRound(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion);

		
		
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
	void usFillCenterRound(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion);



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
	void usDrawRectangle(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, BOOL abEclosion);



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
	void usDrawArc(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, FLOAT afBeginPosition, FLOAT afLength, BOOL abEclosion);



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
	void usDrawLine(HDC DC, COLORREF aColor, FLOAT afPenWidth, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, FLOAT afPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, INT aiPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion);



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
	void usAdvanceFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion, INT aiAlend);



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
	void usDrawArrow(HDC DC, COLORREF aColor, INT aiFirstLeft, INT aiFirstTop, INT aiSecondLeft, INT aiSecondTop, INT aiThirdLeft, INT aiThirdTop, BOOL aEclosion);



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
	void usFillRoundCorner(HDC DC, RECT aRect, INT aiRadius, COLORREF aBeginColor, COLORREF aEndColor, ENUM_Corner Corner, BOOL abEclosion);



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
	//        abGammaCorrection (BOOL) 亮度校正
	//返  回：NULL
	//说　明：填充五边形
	/////////////////////////////////////////////////
	void usFillPolygon(HDC DC, COLORREF aBeginColor, COLORREF aEndColor, POINT apPoint1, POINT apPoint2, POINT apPoint3, POINT apPoint4, POINT apPoint5, BOOL abEclosion, BOOL abGammaCorrection);



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
	void usFillCenterPolygon(HDC DC, COLORREF aSurroundColor, COLORREF aCenterColor, POINT aPoint1, POINT aPoint2, POINT aPoint3, POINT aPoint4, POINT aPoint5, FLOAT afCenterWidth, FLOAT afCenterLength, BOOL abEclosion, BOOL abGammaCorrection);



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
	void usFillHatchRect(HDC DC, RECT aRect, COLORREF aFrontColor, INT aiFrontAlend, COLORREF aBackColor, INT aiBackAlend, INT aiStyle);


	//////////////////////////////////////////////////
	
};
#endif