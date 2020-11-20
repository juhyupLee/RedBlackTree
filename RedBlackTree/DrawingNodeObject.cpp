#include <iostream>
#include <Windows.h>
#include <iostream>
#include "Tree.h"
#include "DrawingNodeObject.h"

#include "GlobalVariable.h"




DrawingNodeObject::DrawingNodeObject(int32_t x, int32_t y, int data, int32_t parentX, int32_t parentY, RedBlackTree::Node* node)
	:
	m_X(x),
	m_Y(y),
	m_ParentX(parentX),
	m_ParentY(parentY),
	m_Data(data)

{
	HDC hdc = GetDC(g_hWnd);
	

	if (parentX != 0 && parentY != 0)
	{
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, parentX, parentY);
	}
	WCHAR dataBuf[128];
	wsprintf(dataBuf, L"%d", data);

	HBRUSH brush;
	if (node->color == RedBlackTree::NODE_COLOR::BLACK)
	{
		brush = CreateSolidBrush(RGB(0, 0, 0));
	}
	else
	{
		brush = CreateSolidBrush(RGB(255, 0, 0));
	}
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	
	Ellipse(hdc, m_X - NODE_RADI, m_Y - NODE_RADI, m_X + NODE_RADI, m_Y + NODE_RADI);
	SelectObject(hdc, oldBrush);

	TextOut(hdc, x-10, y-10, dataBuf, wcslen(dataBuf));

	DeleteObject(brush);
	ReleaseDC(g_hWnd, hdc);

}

DrawingNodeObject::~DrawingNodeObject()
{
}
