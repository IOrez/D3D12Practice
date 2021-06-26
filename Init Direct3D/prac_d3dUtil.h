#pragma once

#include <Windows.h>
#include <wrl.h>				//COM 을 수행하기 위해 필요한 헤더
#include <dxgi1_4.h>			//DXGI를 사용하기 위한 헤더
#include <d3d12.h>				//DirectX12 버전 함수를 사용하기 위한 헤더
#include <d3dcompiler.h>		// HLSL의 내용을 컴파일하기 위한 헤더
#include <DirectXMath.h>		 //DirectX의 Math를 사용하기 위한 헤더
#include <DirectXPackedVector.h> //DirectXMath.h 에 의해 사용되는 헤더 (벡터 연산 지원)
#include <DirectXColors.h>		 //DirectX에 사용되는 색상 정보를 담은 헤더
#include <DirectXCollision.h>	 //DirectXMath.h 에 의해 사용되는 헤더 (충돌 연산 지원)
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
		CP_ACP,			// 변환할 코드 페이지 (기본적으로 CP_ACP)
		0,				// 변환 타입을 나타낸다.
		str.c_str(),	// 변환할 문자열
		-1,				// 변화할 문자열의 사이즈
		buffer,			// 변환값 저장 버퍼
		512);			// 변환될 값의 사이즈

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