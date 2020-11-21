#pragma once
class RedBlackTree
{
public:
	enum class NODE_COLOR
	{
		BLACK = 0,
		RED
	};
	enum
	{
		LEFT  =0,
		RIGHT
	};
	struct Node
	{
		int data;
		Node* parent;
		Node* left;
		Node* right;
		NODE_COLOR color;
	};
public:
	RedBlackTree()
		:m_RootNode(nullptr),
		m_NodeCount(0),
		m_Nill(nullptr),
		m_Depth(0),
		m_Height(0),
		m_Width(0),
		m_MaxBlackNum(0),
		m_bFirst(false)
	{
		m_Nill = new Node;
		m_Nill->color = NODE_COLOR::BLACK;
		m_Nill->left = nullptr;
		m_Nill->right = nullptr;
		m_Nill->parent = nullptr;
	}
	~RedBlackTree()
	{
		TraverseNRelease(m_RootNode);
		delete m_Nill;
		m_NodeCount = 0;
	}
public:
	void TraverseNPrint(Node* node);
	void TraverseNPrint2(Node* node,int x, int y,int parentX, int parentY, int width, int height);
	void TraverseNRelease(Node* node);
	bool InsertNode(int data);
	void DeleteNode(int data);

	bool RotateLeft(Node* node);
	bool RotateRight(Node* node);

	void Print();
	void PrintTree(int32_t x, int32_t y);

	void TestRotate();
	void TraverseDelete(Node* node, Node* parent, int data);

	void DepthCheck(Node* node,int32_t depth);
	void BlackCheck(Node* node, int32_t blackNum);

	int32_t GetBlackNum();
private:
	bool BalanceInsertTree(Node* node,int direction);
	bool BalanceDeleteTree(Node* node);
	bool BlackUncleProcess(Node* node, int direction);
private:
	int32_t m_Width;
	int32_t m_Height;
	int32_t m_Depth;
	int32_t m_MaxBlackNum;
	Node* m_RootNode;
	int32_t m_NodeCount;
	Node* m_Nill;
	bool m_bFirst;



};