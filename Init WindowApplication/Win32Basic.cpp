#include <Windows.h>

// �� â�� �ڵ�. â �ڵ��� ������ â�� �ĺ��ϴ� �뵵�� ����
HWND ghMainWnd = 0;

/*
	Windows ���� ���α׷��� �ʱ�ȭ�� �ʿ��� �ڵ带 ����
	�Լ�. �ʱ�ȭ�� �����ϸ� true��, �׷��� ������ false�� �����ش�.	
*/
bool InitWindowsApp(HINSTANCE instanceHandle, int show);

// �޽��� ���� �ڵ带 ���� �Լ�.
int Run();

// �� â�� ���� ��ǵ��� ó���ϴ� â�� ���ν��� �Լ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Windows ���� ���α׷��� �� ������. �ܼ� ���α׷��� main()�� �ش�.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR pCmdLine, int nShowCmd) {
	/* 
		�켱 hInstance�� nShowCmd�� �ʱ�ȭ �Լ�(InitWindowsApp)�� ȣ���ؼ�
		���� ���α׷� �� â�� �ʱ�ȭ �Ѵ�.
	*/
	if (!InitWindowsApp(hInstance, nShowCmd))
		return 0;

	/*
		���� ���α׷��� ���������� ����, �ʱ�ȭ�Ǿ��ٸ� �޽��� ������ �����Ѵ�.
		�� ������ ���� ���α׷��� ����Ǿ�� ���� ���ϴ�
		WM_QUIT �޽����� ���� ������ ��� ���ư���.
	*/
	return Run();
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show){
	/*
		â�� ������ �� ���� ���� �� ���� â�� ��� Ư���� �����ϴ�
		WINCLASS ����ü�� ä��� ���̴�.
	*/
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass";

	/*
		��������, �� WNDCLASS �ν��Ͻ�('â Ŭ����')�� Windows�� ����Ѵ�.
		�׷��� ���� �ܰ迡�� �� â Ŭ������ �����ؼ� â�� ������ �� �ִ�.
	*/
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	/*
		WNDCLASS �ν��Ͻ��� ���������� ��ϵǾ��ٸ� CreateWindow �Լ���
		â�� ������ �� �ִ�. �� �Լ��� ���� �ÿ��� ������ â�� �ڵ�(HWND ������ ��)��,
		���� �ÿ��� ���� 0�� �ڵ��� �����ش�. â �ڵ��� Ư�� â�� ��Ī�ϴ� �� ���̴� ������,
		Windows�� ���������� �����Ѵ�. â�� �ٷ�� Win32 API �Լ� �߿��� �ڽ��� �۾��� â�� �ĺ�
		�ϱ� ���� �� HWND ���� �޴� �͵��� ����.
	*/

	ghMainWnd = CreateWindow(
		L"BasicWndClass",			// ����� â Ŭ������ �̸�(�տ��� ����ߴ� ��)
		L"Win32Basic",				// â�� ����
		WS_OVERLAPPEDWINDOW,		// ��Ÿ�� �÷��׵�
		CW_USEDEFAULT,				// â�� ��ġ�� x��ǥ�� ����
		CW_USEDEFAULT,				// â�� ��ġ�� y��ǥ�� ����
		CW_USEDEFAULT,				// â�� �ʺ�
		CW_USEDEFAULT,				// â�� ����
		0,							// �θ� â �ڵ�
		0,							// �޴� �ڵ�
		instanceHandle,				// ���� ���α׷� �ν��Ͻ� �ڵ�
		0);							// �߰� ���� �÷��׵�

	if (!ghMainWnd)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	/*
		â�� �����Ǿ �ٷ� ȭ�鿡 ��Ÿ������ �ʴ´�. ������ â��
		���� ȭ�鿡 ǥ���ϰ� �����ϱ� ���ؼ��� ���� �� �Լ��� ȣ����
		�־�� �Ѵ�. �� �Լ� ���, ǥ�� �Ǵ� ������ â�� �ڵ��� �޴´ٴ�
		���� �ָ��ϱ� �ٶ���. �� �ڵ��� �Լ��� ǥ�� �Ǵ� ������ â��
		�������� �˷��ִ� ������ �Ѵ�.
	*/
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run(){
	MSG msg = { 0 };

	/*
		WM_QUIT �޽����� ���� ������ ������ ������. GetMessage()�Լ���
		WM_QUIT �޽����� ���� ��쿡�� 0�� �����ָ�, �׷��� ���������
		������ ����ȴ�. ���� �޽��� ���ſ��� ������ �־����� �� �Լ���
		-1�� �����ش�. ����, GetMessage()�� ȣ���ϸ� �޽����� ������ ������
		���� ���α׷� �����尡 ����(Sleep) ���°� �ȴٴ� ���� �����ϱ� �ٶ���.
	*/
	BOOL bRet = 1;
	while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	/*
		��� �޽����� ��������� ó���Ѵ�. ó���� �޽�����
		���ؼ��� �ݵ�� 0�� ��ȯ�ؾ� ���� ������ ��
	*/
	switch (msg) {
		//���� ���콺 ��ư�� �������� �޽��� ���ڸ� ǥ���Ѵ�.
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"Hello, World", L"Hello", MB_OK);
		return 0;

		//ESC Ű�� �������� �� ���� ���α׷��� â�� �ı��Ѵ�.
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			DestroyWindow(ghMainWnd);
			return 0;
		}

		/*
			�ı� �޽����� ��쿡�� ���� �޽����� ������. �׷���
			��������� �޽��� ������ ����ȴ�.
		*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	/*
		���⼭ ��������� ó������ ���� �ٸ� �޽������� �⺻ â
		���ν���(DefWindowProc)���� �Ѱ� �ش�. �� â ���ν�����
		�ݵ�� DefWindowProc�� ��ȯ���� ���� �־�� ���� �����ϱ�
		�ٶ���.
	*/

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

