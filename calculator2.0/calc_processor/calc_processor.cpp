#include "calc_processor.h"

void cIOHandler::Init()
{
	operandA = operandB = finallyString = L"";
	target = &operandA;
	operation = 0;
	isOperationEntered = false;
}
bool cIOHandler::Input(char ch)
{
	switch(ch)
	{
	case '0':
		if(target->length() == 1 && (*target)[0] == L'0')
			break;
		else if(!target->empty() && (*target)[target->size() - 1] == L'.')
			break;
		else
		{
			*target += L'0';
			finallyString += L'0';
			return true;
		}
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if(target->length() == 1 && (*target)[0] == L'0')
			m_DeleteSymbol();
		*target += wchar_t(ch);
		finallyString += wchar_t(ch);
		return true;
	case '=':
		if(!isOperationEntered || operandA.empty() || operandB.empty())
			break;
		else
		{
			if((*target)[target->size() - 1] == L'.')
				m_DeleteSymbol();
			m_SwapTarget();
			*target = finallyString = m_Compute();
			isOperationEntered = false;
			return true;
		}
	case '+':
	case '-':
	case '*':
	case '/':
	case 'P':
		if(isOperationEntered || operandA.empty())
			break;
		else
		{
			if(!target->empty())
			{
				if((*target)[target->size() - 1] == L'.')
					m_DeleteSymbol();
			}
			operation = ch;
			finallyString = finallyString + L'\n' + wchar_t(operation) + L'\n';
			m_SwapTarget();
			isOperationEntered = true;
			return true;
		}
	case 'C':
		m_Clear();
		return true;
	case 'D':
		if(!finallyString.empty())
		{
			m_DeleteSymbol();
			return true;
		}
		else
			break;
	case '.':
		size_t dot = target->find_last_of(L'.');
		if(target->empty())
			break;
		else if(dot < target->length())
			break;
		else
		{
			*target += L'.';
			finallyString += L'.';
			return true;
		}
	}
	return false;
}
LPCTSTR cIOHandler::GetFinallyText()
{
	return LPCTSTR(finallyString.c_str());
}
std::wstring cIOHandler::m_Compute()
{
	std::wstring result = L"";
	switch(operation)
	{
	case '+':
		result = std::to_wstring(std::stold(operandA) + std::stold(operandB));
		break;
	case '-':
		result = std::to_wstring(std::stold(operandA) - std::stold(operandB));
		break;
	case '*':
		result = std::to_wstring(std::stold(operandA) * std::stold(operandB));
		break;
	case '/':
		result = std::to_wstring(std::stold(operandA) / std::stold(operandB));
		break;
	case 'P':
		result = std::to_wstring(std::pow(std::stold(operandA), std::stoi(operandB)));
		break;
	default:
		break;
	}
	unsigned short count = 0;
	for(size_t i = result.find(L'.') + 1; i <= result.size() - 1; i++)
	{
		if(result[i] != L'0')
		{
			count++;
			break;
		}
	}
	if(count == 0)
	{
		result.erase(result.find(L'.'), result.size() - result.find(L'.'));
	}
	size_t foundDot = result.find(L'.');
	if(foundDot != std::string::npos)
	{
		while(result[result.length() - 1] == L'0')
			result.erase(result.end() - 1);
	}
	operandB = L"";
	return result;
}
void cIOHandler::m_Clear()
{
	Init();
}
void cIOHandler::m_DeleteSymbol()
{
	if(isOperationEntered && target->empty())
	{
		finallyString.erase(finallyString.end() - 3, finallyString.end());
		operation = 0;
		isOperationEntered = false;
		m_SwapTarget();
	}
	else
	{
		target->erase(target->end() - 1);
		finallyString.erase(finallyString.end() - 1);
	}
	return;
}
void cIOHandler::m_SwapTarget()
{
	target == &operandA ? target = &operandB : target = &operandA;
}