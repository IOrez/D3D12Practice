#include "prac_d3dUtil.h"
#include <comdef.h> // Com타입을 지원하기 위한 클래스들이 정의 되어 있다. 
#include <fstream>

DxException::DxException(HRESULT hr, const std::wstring& function, const std::wstring& filename, int lineNumber)
	:ErrorCode(hr),
	FunctionName(function),
	Filename(filename),
	LineNumber(lineNumber)
{
}

std::wstring DxException::ToString()const {
	_com_error err(ErrorCode); // Com 과 관련된 API에서 발생한 에러를 해독하여 보관한다.
	std::wstring msg = err.ErrorMessage();

	return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
}