#include <iostream>
#include "Tree.h"
#include <iostream>
#include <Windows.h>
#include "DrawingNodeObject.h"

void RedBlackTree::TraverseNPrint(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    TraverseNPrint(node->left);
    wprintf(L"%d\n", node->data);
    TraverseNPrint(node->right);
    
}

void RedBlackTree::TraverseNPrint2(Node* node, int x, int y, int parentX, int parentY, int width, int height)
{
    if (node == nullptr)
    {
        return;
    }

    DrawingNodeObject* pObject = new DrawingNodeObject(x, y, node->data, parentX,parentY,node);
    
    
    width = (int)(width * 0.7);
    height +=(int)( height * 0.1);
        
    TraverseNPrint2(node->left, x - width, y + height, x,y, width, height);
    TraverseNPrint2(node->right, x + width, y + height, x, y, width, height);
}

void RedBlackTree::TraverseNRelease(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    TraverseNRelease(node->left);
    TraverseNRelease(node->right);
    delete node;
}

//bool RedBlackTree::InsertNode(int data)
//{
//    if (m_RootNode == nullptr)
//    {
//        m_RootNode = new Node;
//        m_RootNode->data = data;
//        m_RootNode->left = nullptr;
//        m_RootNode->right = nullptr;
//        m_RootNode->parent = nullptr;
//
//        m_NodeCount++;
//        return true;
//    }
//    else
//    {
//        Node* curNode = m_RootNode;
//        Node* parentNode = nullptr;
//        bool bRight = true;
//
//        while (true)
//        {
//            //------------------------------------
//            // ��Ʈ��庸�� ������ (Left)
//            //------------------------------------
//            if (curNode->data > data)
//            {
//                parentNode = curNode;
//                curNode = curNode->left;
//                if (curNode == nullptr)
//                {
//                    curNode = new Node;
//                    curNode->data = data;
//                    curNode->left = nullptr;
//                    curNode->right = nullptr;
//                    curNode->parent = parentNode;
//                    parentNode->left = curNode;
//                    m_NodeCount++;
//                    return true;
//                }
//            }
//            //------------------------------------
//            // ��Ʈ��庸�� Ŭ �� (Right)
//            //------------------------------------
//            else if (curNode->data < data)
//            {
//                parentNode = curNode;
//                curNode = curNode->right;
//                if (curNode == nullptr)
//                {
//                    curNode = new Node;
//                    curNode->data = data;
//                    curNode->left = nullptr;
//                    curNode->right = nullptr;
//                    curNode->parent = parentNode;
//                    parentNode->right = curNode;
//                    m_NodeCount++;
//                    return true;
//                }
//            }
//            else
//            {
//                return false;
//            }
//        }
//
//        m_NodeCount++;
//    }
//    return true;
//}
bool RedBlackTree::InsertNode(int data)
{
    if (m_RootNode == nullptr)
    {
        m_RootNode = new Node;
        m_RootNode->data = data;
        m_RootNode->parent = nullptr;
        m_RootNode->left = m_Nill;
        m_RootNode->right = m_Nill;
        m_RootNode->color = NODE_COLOR::BLACK;

        m_NodeCount++;
        return true;
    }
    else
    {
        Node* curNode = m_RootNode;
        Node* parentNode = nullptr;
        bool bRight = true;

        while (curNode!=m_Nill)
        {
            //------------------------------------
            // ��Ʈ��庸�� ������ (Left)
            //------------------------------------
            if (curNode->data > data)
            {
                parentNode = curNode;
                curNode = curNode->left;
                if (curNode == m_Nill)
                {
                    curNode = new Node;
                    curNode->data = data;
                    curNode->parent = parentNode;
                    curNode->left = m_Nill;
                    curNode->right = m_Nill;
                    curNode->color = NODE_COLOR::RED;

                    //----------------------------------------------------------
                    // �θ�뵵�� ���� ���̳�,����Ŀ����� �б� ����.
                    //----------------------------------------------------------
                    if (curNode->parent->color == NODE_COLOR::BLACK)
                    {
                        parentNode->left = curNode;
                        return true;
                    }
                    else
                    {
                        Node* parent = parentNode;
                        Node* grandFather = parentNode->parent;
                        Node* uncle = nullptr;
                        parent->left = curNode;

                        if (grandFather->left == parentNode)
                        {
                            uncle = grandFather->right;
                        }
                        else
                        {
                            uncle = grandFather->left;
                        }

                        //----------------------------------------------------------
                        // ���̳����� ���� ����� ���̳Ŀ� ���� �б� ����.
                        //----------------------------------------------------------
                        if (uncle->color == NODE_COLOR::RED)
                        {
                            grandFather->color = NODE_COLOR::RED;
                            parent->color = NODE_COLOR::BLACK;
                            uncle->color = NODE_COLOR::BLACK;

                            RedUncleProcess(grandFather);

                        }
                        else
                        {
                           
                            BlackUncleProcess(curNode);
                        }
                    }

                    parentNode->left = curNode;
                    m_NodeCount++;
                    return true;
                }
            }
            //------------------------------------
            // ��Ʈ��庸�� Ŭ �� (Right)
            //------------------------------------
            else if(curNode->data < data)
            {
                parentNode = curNode;
                curNode = curNode->right;
                if (curNode == m_Nill)
                {
                    curNode = new Node;
                    curNode->data = data;
                    curNode->parent = parentNode;
                    curNode->left = nullptr;
                    curNode->right = nullptr;
                    parentNode->right = curNode;
                    m_NodeCount++;
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
       
       

        m_NodeCount++;
    }
    return true;
}

//void RedBlackTree::DeleteNode(int data)
//{
//    TraverseDelete(m_RootNode, nullptr, data);
//}

bool RedBlackTree::RotateLeft(Node* node)
{
    if (node->right == nullptr)
    {
        return false;
    }
    //�켱 ��� ��尡 �ٲ������
    //�� �θ� �����������
    // ���θ� --- Right 
    Node* tempParent = node->parent;
    Node* rightNode = node->right;
    Node* leftNode = node->left;

    if (m_RootNode == node)
    {
        m_RootNode = rightNode;
    }

    if (tempParent != nullptr)
    {
        if (tempParent->left == node)
        {
            tempParent->left = rightNode;
        }
        else if (tempParent->right ==node)
        {
            tempParent->right = rightNode;
        }
    }
    rightNode->parent = tempParent;


    //��� ����Ǻθ�� ���� right���ȴ�
    // right����� left��  �����尡�ȴ�

    node->parent = rightNode;

    Node* leftFromRightNode = rightNode->left;
    rightNode->left = node;


    //�������� right�� right����� left���ȴ�
    node->right = leftFromRightNode;

    //right ����� left�� �θ�� �����尡 �ȴ�.
    if (leftFromRightNode != nullptr)
    {
        leftFromRightNode->parent = node;
    }

    return true;
}

bool RedBlackTree::RotateRight(Node* node)
{
    if (node->left == nullptr)
    {
        return false;
    }
    //�켱 ��� ��尡 �ٲ������
    //�� �θ� �����������
    // ���θ� --- left
    Node* tempParent = node->parent;
    Node* rightNode = node->right;
    Node* leftNode = node->left;

    if (m_RootNode == node)
    {
        m_RootNode = leftNode;
    }

    if (tempParent != nullptr)
    {
        if (tempParent->left == node)
        {
            tempParent->left = leftNode;
        }
        else if (tempParent->right == node)
        {
            tempParent->right = leftNode;
        }
    }
    leftNode->parent = tempParent;


    //��� ����Ǻθ�� ���� right���ȴ�
    // right����� left��  �����尡�ȴ�

    node->parent = leftNode;

    Node* rightFromLeftNode = leftNode->right;
    leftNode->right = node;


    //�������� right�� right����� left���ȴ�
    node->left= rightFromLeftNode;

    //right ����� left�� �θ�� �����尡 �ȴ�.
    if (rightFromLeftNode != nullptr)
    {
        rightFromLeftNode->parent = node;
    }

    return true;
}

void RedBlackTree::Print()
{
    TraverseNPrint(m_RootNode);
}

void RedBlackTree::PrintTree()
{

    TraverseNPrint2(m_RootNode,600,50,0,0,300,60);

}

void RedBlackTree::TestRotate()
{
    //RotateLeft(m_RootNode->left->left);
    RotateRight(m_RootNode->left);
}

bool RedBlackTree::RedUncleProcess(Node* node)
{
    Node* parent = node->parent;
    if (parent == nullptr)
    {
        return true;
    }
    if (parent->color == NODE_COLOR::BLACK)
    {
        return true;
    }

    Node* grandParent = parent->parent;
    Node* uncle=nullptr;
    if (grandParent->left != parent)
    {
        uncle = grandParent->left;
    }
    else 
    {
        uncle = grandParent->right;
    }

    if (uncle->color == NODE_COLOR::RED)
    {
        parent->color = NODE_COLOR::BLACK;
        uncle->color = NODE_COLOR::BLACK;
        grandParent->color = NODE_COLOR::RED;

        RedUncleProcess(grandParent);
    }
    else
    {
        BlackUncleProcess(node);
    }

    return false;
}

bool RedBlackTree::BlackUncleProcess(Node* node)
{
    Node* parent = node->parent;
    Node* grandParent = parent->parent;

    if (parent->left == node)
    {
        RotateRight(grandParent);
        parent->color = NODE_COLOR::BLACK;
        grandParent->color = NODE_COLOR::RED;

    }
    else if (parent->right == node)
    {
        RotateLeft(parent);
        RotateRight(grandParent);

        node->color = NODE_COLOR::BLACK;
        grandParent->color = NODE_COLOR::RED;
    }
    return false;
}

//void RedBlackTree::TraverseDelete(Node* node,Node* parent, int data)
//{
//    if (node == nullptr)
//    {
//        return;
//    }
//    if (node->data == data)
//    {
//        //---------------------------------------------------------------
//        // �ڽ� ��尡 ���°��
//        //---------------------------------------------------------------
//        if (node->left == nullptr && node->right == nullptr)
//        {
//            if (parent->left == node)
//            {
//                parent->left = nullptr;
//            }
//            else if (parent->right == node)
//            {
//                parent->right = nullptr;
//            }
//            delete node;
//            return;
//        }
//
//        //---------------------------------------------------------------
//        // �ڽĳ�尡 �ϳ��� �ִ� ���
//        //---------------------------------------------------------------
//        else if ((node->left == nullptr&& node->right != nullptr )|| (node->left != nullptr && node->right == nullptr))
//        {
//            //---------------------------------------------------------------
//            // �����ߵ� ��带 ������ ����°� �ƴ϶�, �� �ڽĳ���� �����͸� �ű��
//            // �ڽĵ� �ű���� �� �ڽĳ�带 ����������.
//            //---------------------------------------------------------------
//            Node* childNode = nullptr;
//
//            if (node->left != nullptr)
//            {
//                childNode = node->left;
//            }
//            else if (node->right != nullptr)
//            {
//                childNode = node->right;
//            }
//            node->data = childNode->data;
//            node->left = childNode->left;
//            node->right = childNode->right;
//
//            delete childNode;
//            return;
//        }
//        //---------------------------------------------------------------
//        // �ڽĳ�尡 ���� ���
//        //---------------------------------------------------------------
//        else if (node->left != nullptr && node->right != nullptr)
//        {
//            //---------------------------------------------------------------
//            // ������ �ɳ���� �ڽ��� �������� �����ؼ� �� �������� ���� ������� null�̳��ö����� ã�´�
//            // ���� ���ʿ��ִ� ��带 �����ߵ� ����� �����Ϳ� ��ȯ�ϰ�, �� �θ� right�� �����Ѵ�
//            //---------------------------------------------------------------
//            Node* childParent = node;
//            Node* childNode = node->right;
//            
//            while (childNode->left != nullptr)
//            {
//                childParent = childNode;
//                childNode = childNode->left;
//            }
//
//            node->data = childNode->data;
//
//            //---------------------------------------------------------------
//            // �� �������ִ� ����� �θ��� ���ʿ��� �����ٸ�,  �� �θ� ���ʿ� �������� ���̰�,
//            // �����ʿ��� �����ٸ�  �����ʿ� �������� ���δ�.(��Ʈ����� ��� ����)
//            //---------------------------------------------------------------
//            if (childParent->left == childNode)
//            {
//                childParent->left = childNode->right;
//            }
//            else if (childParent->right == childNode)
//            {
//                childParent->right = childNode->right;
//            }
//
//            delete childNode;
//
//            return;
//        }
//    }
//    else if (node->data > data)
//    {
//        TraverseDelete(node->left, node, data);
//    }
//    else if (node->data < data)
//    {
//        TraverseDelete(node->right, node, data);
//    }
//}