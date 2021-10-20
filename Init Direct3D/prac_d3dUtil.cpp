#include "prac_d3dUtil.h"
#include <comdef.h> // ComŸ���� �����ϱ� ���� Ŭ�������� ���� �Ǿ� �ִ�. 
#include <fstream>

DxException::DxException(HRESULT hr, const std::wstring& function, const std::wstring& filename, int lineNumber)
	:ErrorCode(hr),
	FunctionName(function),
	Filename(filename),
	LineNumber(lineNumber)
{
}

std::wstring DxException::ToString()const {
	_com_error err(ErrorCode); // Com �� ���õ� API���� �߻��� ������ �ص��Ͽ� �����Ѵ�.
	std::wstring msg = err.ErrorMessage();

	return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
}