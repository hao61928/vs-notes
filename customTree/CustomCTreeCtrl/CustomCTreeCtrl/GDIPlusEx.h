#ifndef USGdiplusExH
#define USGdiplusExH

//����DGI+�����ļ�
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

enum ENUM_DrawOrientation {edoHorizontal, edoVertical};     //���Ʒ���
enum ENUM_Corner {ecLeftTop, ecRightTop, ecLeftBottom, ecRightBottom};     //�ĸ���
enum ENUM_DashStyle {
	UCDashStyleSolid = 0,       //ʵ��
	UCDashStyleDash = 1,        //����
	UCDashStyleDot = 2,         //����
	UCDashStyleDashDot = 3,     //�㻮��
	UCDashStyleDashDotDot = 4,  //˫�㻮��
	UCDashStyleCustom = 5,      //�Զ�����
};

class  CGDIPlus  
{
public:
	CGDIPlus();
	virtual ~CGDIPlus();

	/////////////////////////////////////////////////
	//��������usFillRectangle
	//��  �ܣ�����������
	//��  ����DC (HDC) ��ͼ�豸
	//		  aRect (RECT) ���ƾ�������
	//		  aColor (COLORREF) �����ɫ
	//		  abEclosion (BOOL) �Ƿ���
	//��  �أ�NULL
	//˵��������ɫ����������
	/////////////////////////////////////////////////
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, POINT aBeginPoint, POINT aEndPoint, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion);



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
	void usFillRectangle(HDC DC, RECT aRect, COLORREF aColor, INT aAlpha, BOOL abEclosion);

		
		
	/////////////////////////////////////////////////
	//��������usFillCenterRectangle
	//��  �ܣ�����������
	//��  ����DC (HDC) ��ͼ�豸
	//        aRect (RECT) ���ƾ�������
	//        aCenterColor (COLORREF) �����м���ɫ
	//        aSurroundColor (COLORREF) ������Χ��ɫ
	//        afCenterWidth (FLOAT) �м佥�䷽ʽ�����������
	//        afCenterHeight (FLOAT) �м佥�䷽ʽ�߶���������
	//        abEclosion(bool) �Ƿ���
	//��  �أ�NULL
	//˵���������������򣬿�ѡ����������м佥��ķ�ʽ
	/////////////////////////////////////////////////
	void usFillCenterRectangle(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion);



	/////////////////////////////////////////////////
	//��������usFillRound
	//��  �ܣ�����������Բ
	//��  ����DC (HDC) ��ͼ�豸
	//        aRect (RECT) ���ƾ�������
	//        aColor (COLORREF) �����ɫ
	//        abEclosion(BOOL) �Ƿ���
	//��  �أ�NULL
	//˵��������䵥ɫ��������Բ
	/////////////////////////////////////////////////
	void usFillRound(HDC DC, RECT aRect, COLORREF aColor, BOOL abEclosion);



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
	void usFillRound(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, ENUM_DrawOrientation Orientation, BOOL abEclosion);

		
		
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
	void usFillCenterRound(HDC DC, RECT aRect, COLORREF aCenterColor, COLORREF aSurroundColor, FLOAT afCenterWidth, FLOAT afCenterHeight, BOOL abEclosion);



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
	void usDrawRectangle(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, BOOL abEclosion);



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
	void usDrawArc(HDC DC, RECT aRect, COLORREF aColor, FLOAT afPenWidth, FLOAT afBeginPosition, FLOAT afLength, BOOL abEclosion);



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
	void usDrawLine(HDC DC, COLORREF aColor, FLOAT afPenWidth, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, FLOAT afPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usDrawLine(HDC DC, ENUM_DashStyle aDashStyle, INT aiPenWidth, COLORREF aColor, INT aiBeginLeft, INT aiBeginTop, INT aiEndLeft, INT aiEndTop, BOOL abEclosion);



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
	void usFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion);



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
	void usAdvanceFillRoundRectangle(HDC DC, RECT aRect, COLORREF aBeginColor, COLORREF aEndColor, COLORREF aBorderColor, INT aiCornerRadius, ENUM_DrawOrientation Orientation, BOOL abEclosion, INT aiAlend);



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
	void usDrawArrow(HDC DC, COLORREF aColor, INT aiFirstLeft, INT aiFirstTop, INT aiSecondLeft, INT aiSecondTop, INT aiThirdLeft, INT aiThirdTop, BOOL aEclosion);



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
	void usFillRoundCorner(HDC DC, RECT aRect, INT aiRadius, COLORREF aBeginColor, COLORREF aEndColor, ENUM_Corner Corner, BOOL abEclosion);



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
	//        abGammaCorrection (BOOL) ����У��
	//��  �أ�NULL
	//˵��������������
	/////////////////////////////////////////////////
	void usFillPolygon(HDC DC, COLORREF aBeginColor, COLORREF aEndColor, POINT apPoint1, POINT apPoint2, POINT apPoint3, POINT apPoint4, POINT apPoint5, BOOL abEclosion, BOOL abGammaCorrection);



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
	void usFillCenterPolygon(HDC DC, COLORREF aSurroundColor, COLORREF aCenterColor, POINT aPoint1, POINT aPoint2, POINT aPoint3, POINT aPoint4, POINT aPoint5, FLOAT afCenterWidth, FLOAT afCenterLength, BOOL abEclosion, BOOL abGammaCorrection);



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
	void usFillHatchRect(HDC DC, RECT aRect, COLORREF aFrontColor, INT aiFrontAlend, COLORREF aBackColor, INT aiBackAlend, INT aiStyle);


	//////////////////////////////////////////////////
	
};
#endif