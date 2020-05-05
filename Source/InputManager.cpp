#include <stdafx.h>
#include "InputManager.h"
#include "Renderer.h"

InputManager* InputManager::m_instance = nullptr;

InputManager* InputManager::CreateInstance() 
{
	if (m_instance == nullptr) 
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

void InputManager::DestroyInstance() 
{
	if (m_instance != nullptr) 
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

InputManager::InputManager() 
{
	memset(m_keyCurrentState, 0, 256);
}

InputManager::~InputManager() 
{

}

void InputManager::SetKey(u8 a_key, bool a_val)
{
	m_keyCurrentState[a_key] = a_val;
}

bool InputManager::GetKeyDown(u8 a_key) 
{
	return m_keyCurrentState[a_key];
}

LRESULT CALLBACK InputManager::HandleWindowCallbacks(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	PAINTSTRUCT paintstruct;
	HDC hDC;
	Renderer* renderer = Renderer::GetInstance();
	if (hwnd == renderer->GetWindowHandle()) 
	{
		switch (message)
		{
		case WM_PAINT://called when the window content is invalidated
		{
			hDC = BeginPaint(hwnd, &paintstruct);

			RECT clRect;
			GetClientRect(hwnd, &clRect);
			BitBlt(hDC, clRect.left, clRect.top, (clRect.right - clRect.left) + 1,
				(clRect.bottom - clRect.top) + 1, renderer->GetBufferContext(), 0, 0, SRCCOPY);

			EndPaint(hwnd, &paintstruct);
			break;
		}
		case WM_DESTROY://called when the window needs to close
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN://Handles keyboard presses
		{
			InputManager* im = InputManager::GetInstance();
			im->SetKey((u8)wParam, true);
			break;
		}
		case WM_KEYUP:
		{
			InputManager* im = InputManager::GetInstance();
			im->SetKey((u8)wParam, false);
			break;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		};
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}