#pragma once


class DrawingNodeObject
{
public:

	enum
	{
		NODE_RADI = 25,
	};
	DrawingNodeObject(int32_t x, int32_t y, int data, int32_t parentX, int32_t parentY,RedBlackTree::Node* node);
	~DrawingNodeObject();


private:
	int32_t m_X;
	int32_t m_Y;
	int32_t m_ParentX;
	int32_t m_ParentY;
	int32_t m_Data;

};