// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

#import "D:\\VS\\tmp\\EXCEL.EXE" no_namespace
// CRefreshEvents ��װ��

class CRefreshEvents : public COleDispatchDriver
{
public:
	CRefreshEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CRefreshEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRefreshEvents(const CRefreshEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// RefreshEvents ����
public:
	void BeforeRefresh(BOOL * Cancel)
	{
		static BYTE parms[] = VTS_PBOOL ;
		InvokeHelper(0x63c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cancel);
	}
	void AfterRefresh(BOOL Success)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x63d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Success);
	}

	// RefreshEvents ����
public:

};
