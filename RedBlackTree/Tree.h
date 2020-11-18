#pragma once
class RedBlackTree
{
public:
	enum class NODE_COLOR
	{
		BLACK = 0,
		RED
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
		m_Nill(nullptr)
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
		m_NodeCount = 0;
	}
public:
	void TraverseNPrint(Node* node);
	void TraverseNPrint2(Node* node,int x, int y,int parentX, int parentY, int width, int height);
	void TraverseNRelease(Node* node);
	//bool InsertNode(int data);
	bool InsertNode(int data);
//	void DeleteNode(int data);

	bool RotateLeft(Node* node);
	bool RotateRight(Node* node);

	void Print();
	void PrintTree();

	void TestRotate();
	//void TraverseDelete(Node* node, Node* parent, int data);
private:
	bool RedUncleProcess(Node* node);
	bool BlackUncleProcess(Node* node);
private:
	Node* m_RootNode;
	int32_t m_NodeCount;
	Node* m_Nill;


};