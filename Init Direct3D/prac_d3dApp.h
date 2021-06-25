#pragma once


#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC	// �޸� ���� Ž�� ����� ����ϱ� ���� �����Ѵ�.
#include <crtdbg.h>			// �޸� �Ҵ��� �����Ѵ�. _CrtDumpMemoryLeaks(), _CrtSetDbgFlag()
#endif

#include "prac_d3dUtil.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"D3D12.lib")
#pragma comment(lib, "dxgi.lib")


class D3DApp {
protected:
	D3DApp(HINSTANCE hInstance);
	D3DApp(const D3DApp& rhs) = delete;
	virtual ~D3DApp();
	D3DApp& operator=(const D3DApp& rhs) = delete;

public:
	static D3DApp* GetApp();
	HINSTANCE  AppInst() const;
	HWND	   MainWnd() const;

	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual void OnResize();

protected:
	bool InitMainWindow();

protected:

	static D3DApp* mApp;
	
	HINSTANCE	mhAppInst = nullptr;
	HWND		mhMainWnd = nullptr;
	
	std::wstring mMainWndCaption = L"d3d App";

	int mClientWidth = 800;
	int mClientHeight = 600;
};