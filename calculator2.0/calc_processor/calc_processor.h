#ifndef _CALC_PROCESSOR_H_
#define _CALC_PROCESSOR_H_

#include <Windows.h>
#include <string>
#include <cmath>

class cIOHandler
{
public:
	void Init();
	bool Input(char);
	LPCTSTR GetFinallyText();

private:
	std::wstring m_Compute();
	void m_Clear();
	void m_DeleteSymbol();
	void m_SwapTarget();

	std::wstring *target;
	std::wstring operandA;
	std::wstring operandB;
	std::wstring finallyString;
	char operation;
	bool isOperationEntered;
};

#endif