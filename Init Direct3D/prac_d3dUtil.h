#pragma once

#include <Windows.h>
#include <wrl.h>				//COM �� �����ϱ� ���� �ʿ��� ���
#include <dxgi1_4.h>			//DXGI�� ����ϱ� ���� ���
#include <d3d12.h>				//DirectX12 ���� �Լ��� ����ϱ� ���� ���
#include <d3dcompiler.h>		// HLSL�� ������ �������ϱ� ���� ���
#include <DirectXMath.h>		 //DirectX�� Math�� ����ϱ� ���� ���
#include <DirectXPackedVector.h> //DirectXMath.h �� ���� ���Ǵ� ��� (���� ���� ����)
#include <DirectXColors.h>		 //DirectX�� ���Ǵ� ���� ������ ���� ���
#include <DirectXCollision.h>	 //DirectXMath.h �� ���� ���Ǵ� ��� (�浹 ���� ����)
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include "../Common/d3dx12.h"


class DxException {
public:
	DxException() = default;
	DxException(HRESULT hr, const std::wstring& function, const std::wstring& filename, int lineNumber);

	std::wstring ToString() const;

	HRESULT			ErrorCode = S_OK;
	std::wstring	FunctionName;
	std::wstring	Filename;
	int LineNumber = -1;
};

inline std::wstring AnsiToWString(const std::string& str) {
	WCHAR buffer[512];
	MultiByteToWideChar(
		CP_ACP,			// ��ȯ�� �ڵ� ������ (�⺻������ CP_ACP)
		0,				// ��ȯ Ÿ���� ��Ÿ����.
		str.c_str(),	// ��ȯ�� ���ڿ�
		-1,				// ��ȭ�� ���ڿ��� ������
		buffer,			// ��ȯ�� ���� ����
		512);			// ��ȯ�� ���� ������

	return std::wstring(buffer);
}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)											\
{																	\
	HRESULT hr__ = (x);												\
	std::wstring wfn = AnsiToWString(__FILE__);						\
	if(FAILED(hr__)) {throw DxException(hr__,L#x,wfn,__LINE__);}	\
}
#endif

#ifndef ReleaseCom
#define ReleaseCom(x) {if(x){x->Release(); x = 0;}}
#endif