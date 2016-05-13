#ifndef _GUI_H_
#define _GUI_H_

#include <Windows.h>
#include <string>

typedef struct StaticWindowAttributes
{
	CGUI_ShellBase* instance;
	LRESULT (CALLBACK *pCallback)(HWND, UINT, WPARAM, LPARAM);
} SAttr;

class CGUI_Component
{

};
typedef CGUI_Component T_Button, T_Field;

class CGUI_ShellBase
{
public:
	explicit CGUI_ShellBase(HINSTANCE hInstance) : m_hInstance(hInstance) {}

	virtual void Setup() = 0;
	void RunApplication();

	virtual LRESULT CALLBACK WndHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual short DestroyWithReturn() = 0;
	virtual ~CGUI_ShellBase() {}

protected:
	unsigned int m_Width;
	unsigned int m_Height;
	DWORD m_WndStyleFlags;
	std::wstring m_ClassName;
	std::wstring m_CurrentExpression;
	HINSTANCE m_hInstance;
};

class CGUI_Shell_Simple : public CGUI_ShellBase
{
public:
	explicit CGUI_Shell_Simple(HINSTANCE hInstance) : CGUI_ShellBase(hInstance) {}

	void Setup();
	LRESULT CALLBACK WndHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	~CGUI_Shell_Simple() {}
};

class CGUI_Shell_Extended : public CGUI_ShellBase
{
public:
	explicit CGUI_Shell_Extended(HINSTANCE hInstance) : CGUI_ShellBase(hInstance) {}

	void Setup();
	LRESULT CALLBACK WndHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	~CGUI_Shell_Extended() {}
};

class CGUI_Shell_Matrix : public CGUI_ShellBase
{
public:
	explicit CGUI_Shell_Matrix(HINSTANCE hInstance) : CGUI_ShellBase(hInstance) {}

	void Setup();
	LRESULT CALLBACK WndHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	~CGUI_Shell_Matrix() {}
};

static CGUI_ShellBase* SimpleApp;
static LRESULT CALLBACK SA_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return SimpleApp->WndHandler(hWnd, msg, wParam, lParam);
}

static CGUI_ShellBase* ExtendedApp;
static LRESULT CALLBACK EA_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ExtendedApp->WndHandler(hWnd, msg, wParam, lParam);
}

static CGUI_ShellBase* MatrixApp;
static LRESULT CALLBACK MA_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return MatrixApp->WndHandler(hWnd, msg, wParam, lParam);
}

#endif