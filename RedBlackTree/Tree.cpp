#include <iostream>
#include "Tree.h"
#include <iostream>
#include <Windows.h>
#include "DrawingNodeObject.h"
#include "MemoryTracer.h"
#include "GlobalVariable.h"

std::vector<DrawingNodeObject*> g_Vector;

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
    if (node == m_Nill)
    {
        return;
    }

    DrawingNodeObject* pObject = new DrawingNodeObject(x, y, node->data, parentX,parentY,node);
   
    //g_Vector.push_back(pObject);

    delete pObject;

    width = (int)(width * 0.5);
    height +=(int)( height * 0.05);
        
    TraverseNPrint2(node->left, x - width, y + height, x,y, width, height);
    TraverseNPrint2(node->right, x + width, y + height, x, y, width, height);

    //TraverseNPrint2(node->left, x - (x/2), y + (y / 2), x,y, width, height);
    //TraverseNPrint2(node->right, x + (x/ 2), y + (y / 2), x, y, width, height);

}

void RedBlackTree::TraverseNRelease(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node == m_Nill)
    {
        return;
    }
    TraverseNRelease(node->left);
    TraverseNRelease(node->right);
    delete node;
}

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
                    parentNode->left = curNode;

                    //----------------------------------------------------------
                    // �θ�뵵�� ���� ���̳�,����Ŀ����� �б� ����.
                    //----------------------------------------------------------
                    if (curNode->parent->color == NODE_COLOR::BLACK)
                    {
                        return true;
                    }
                    else
                    {
                        BalanceInsertTree(curNode, LEFT);
                    }

                   
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
                    curNode->left = m_Nill;
                    curNode->right = m_Nill;
                    curNode->color = NODE_COLOR::RED;
                    parentNode->right = curNode;
                    m_NodeCount++;

                    if (curNode->parent->color == NODE_COLOR::BLACK)
                    {
                        return true;
                    }
                    else
                    {
                        BalanceInsertTree(curNode, RIGHT);
                    }
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

void RedBlackTree::DeleteNode(int data)
{
    TraverseDelete(m_RootNode, nullptr, data);
}

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

void RedBlackTree::PrintTree(int32_t x, int32_t y)
{

    TraverseNPrint2(m_RootNode,750+x,50+y,0,0,800,50);

}

void RedBlackTree::TestRotate()
{
    //RotateLeft(m_RootNode->left->left);
    RotateRight(m_RootNode->left);
}

bool RedBlackTree::BalanceInsertTree(Node* node,int direction)
{
    if (node == m_RootNode)
    {
        node->color = NODE_COLOR::BLACK;
        return true;
    }

    Node* parent = node->parent;

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

        BalanceInsertTree(grandParent, direction);
    }
    else
    {
        if (grandParent->left == parent)
        {
            BlackUncleProcess(node, LEFT);
        }
        else if (grandParent->right == parent)
        {
            BlackUncleProcess(node, RIGHT);
        }
       
    }

    return false;
}

bool RedBlackTree::BalanceDeleteTree(Node* node)
{
    if (node->color == NODE_COLOR::RED)
    {
        node->color = NODE_COLOR::BLACK;
        return true;
    }
    if (node == m_RootNode)
    {
        node->color = NODE_COLOR::BLACK;
        return true;
    }
    else
    {
        Node* sibling = nullptr;
        Node* parent = node->parent;
        int direction = 0;

        if (parent->left == node)
        {
            sibling = parent->right;
            direction = LEFT;
        }
        else if (parent->right == node)
        {
            sibling = parent->left;
            direction = RIGHT;
        }

        if (direction == LEFT)
        {
            //-------------------------------------------------------
            // ���� ��尡 �����ΰ�� --> ���� ����.
            // ������带 ������ ����������.
            //-------------------------------------------------------
            if (sibling->color == NODE_COLOR::RED)
            {
                RotateLeft(parent);
                sibling->color = NODE_COLOR::BLACK;
                parent->color = NODE_COLOR::RED;
                BalanceDeleteTree(node);
            }
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->left->color == NODE_COLOR::BLACK &&
                sibling->right->color == NODE_COLOR::BLACK)
            {

                sibling->color = NODE_COLOR::RED;
                BalanceDeleteTree(parent);
            }
            //-------------------------------------------------------
            // ������尡,���̰� �� �����ڽ��� �����ΰ��--> ȸ�����Ѽ� 6�����θ�������
            //-------------------------------------------------------
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->left->color == NODE_COLOR::RED)
            {
                RotateRight(sibling);
                parent->right->color = NODE_COLOR::BLACK;
                parent->right->right->color = NODE_COLOR::RED;
                BalanceDeleteTree(node);
            }
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->right->color == NODE_COLOR::RED)
            {
                RotateLeft(parent);
                sibling->color = parent->color;
                parent->color = NODE_COLOR::BLACK;
                sibling->right->color = NODE_COLOR::BLACK;
            }
        }
        else
        {
             //-------------------------------------------------------
             // ���� ��尡 �����ΰ�� --> ���� ����.
             // ������带 ������ ����������.
             //-------------------------------------------------------
            if (sibling->color == NODE_COLOR::RED)
            {
                RotateRight(parent);
                sibling->color = NODE_COLOR::BLACK;
                parent->color = NODE_COLOR::RED;
                BalanceDeleteTree(node);
            }
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->left->color == NODE_COLOR::BLACK &&
                sibling->right->color == NODE_COLOR::BLACK)
            {

                sibling->color = NODE_COLOR::RED;
                BalanceDeleteTree(parent);
            }
            //-------------------------------------------------------
            // ������尡,���̰� �� �����ڽ��� �����ΰ��--> ȸ�����Ѽ� 6�����θ�������
            //-------------------------------------------------------
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->right->color == NODE_COLOR::RED)
            {
                RotateRight(sibling);
                parent->left->color = NODE_COLOR::BLACK;
                parent->left->left->color = NODE_COLOR::RED;
                BalanceDeleteTree(node);
            }
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->left->color == NODE_COLOR::RED)
            {
                RotateRight(parent);
                sibling->color = parent->color;
                parent->color = NODE_COLOR::BLACK;
                sibling->left->color = NODE_COLOR::BLACK;
            }
        }
   
    }
    return true;
}

bool RedBlackTree::BlackUncleProcess(Node* node, int direction)
{
    Node* parent = node->parent;
    Node* grandParent = parent->parent;

    if (direction == LEFT)
    {
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
    }
    else
    {
        if (parent->right == node)
        {
            RotateLeft(grandParent);
            parent->color = NODE_COLOR::BLACK;
            grandParent->color = NODE_COLOR::RED;

        }
        else if (parent->left == node)
        {
            RotateRight(parent);
            RotateLeft(grandParent);

            node->color = NODE_COLOR::BLACK;
            grandParent->color = NODE_COLOR::RED;
        }
    }
    
    return true;
}

void RedBlackTree::TraverseDelete(Node* node,Node* parent, int data)
{
    if (node == m_Nill)
    {
        return;
    }
 
    if (node->data > data)
    {
        TraverseDelete(node->left, node, data);
    }
    else if (node->data < data)
    {
        TraverseDelete(node->right, node, data);
    }
    else
    {
        Node* replaceNode = nullptr;
        NODE_COLOR delNodeColor;

        if (node->data == data)
        {
            //---------------------------------------------------------------
            // �ڽ� ��尡 ���°��
            //---------------------------------------------------------------
            if (node->left == m_Nill && node->right == m_Nill)
            {
                //-------------------------------------------------------
                // �ڽĳ�尡���� ���� ���� ����̰ų�, �ƴ� ��Ʈ��� �ϳ����������ε�..
                //-------------------------------------------------------
                if (node == m_RootNode)
                {
                    delete node;
                    m_RootNode = nullptr;
                    m_Nill->parent = nullptr;
                    return;
                }
                else
                {
                    if (parent->left == node)
                    {
                        parent->left = m_Nill;
                    }
                    else if (parent->right == node)
                    {
                        parent->right = m_Nill;
                    }

                    m_Nill->parent = parent;
                    
                    replaceNode = m_Nill;
                    delNodeColor = node->color;
                    delete node;
                }
               
            }
            //---------------------------------------------------------------
            // �ڽĳ�尡 �ϳ��� �ִ� ���
            //---------------------------------------------------------------
            else if ((node->left == m_Nill && node->right != m_Nill) || (node->left != m_Nill && node->right == m_Nill))
            {
                //---------------------------------------------------------------
                // �����ߵ� ��带 ������ ����°� �ƴ϶�, �� �ڽĳ���� �����͸� �ű��
                // �ڽĵ� �ű���� �� �ڽĳ�带 ����������.
                //---------------------------------------------------------------

                Node* childNode = nullptr;
                Node* parent = node->parent;

                //-----------------------------
                // Child��� ã�Ƴ���
                //-----------------------------
                if (node->left != m_Nill)
                {
                    childNode = node->left;
                }
                else if (node->right != m_Nill)
                {
                    childNode = node->right;
                }
   

                //-----------------------------
                // Child���  <------------>����� �θ� ����
                //-----------------------------
                childNode->parent = parent;

                //-----------------------------
                // ��尡 �θ��� ����Ʈ���ٸ�, ���ϵ��带 ����Ʈ�ο���
                // �׹ݴ�� ����Ʈ�� ����
                //-----------------------------
                if (parent->left == node)
                {
                    parent->left = childNode;
                }
                else if (parent->right == node)
                {
                    parent->right = childNode;
                }
                
                replaceNode = childNode;
                delNodeColor = node->color;

                delete node;
            }
            //---------------------------------------------------------------
            // �ڽĳ�尡 ���� ���
            //---------------------------------------------------------------
            else if (node->left != m_Nill && node->right != m_Nill)
            {
                //---------------------------------------------------------------
                // ������ �ɳ���� �ڽ��� �������� �����ؼ� �� �������� ���� ������� null�̳��ö����� ã�´�
                // ���� ���ʿ��ִ� ��带 �����ߵ� ����� �����Ϳ� ��ȯ�ϰ�, �� �θ� right�� �����Ѵ�
                //---------------------------------------------------------------
                Node* childNode = node->right;

                while (childNode->left != m_Nill)
                {
                    childNode = childNode->left;
                }

                node->data = childNode->data;

                //---------------------------------------------------------------
                // �� �������ִ� ����� �θ��� ���ʿ��� �����ٸ�,  �� �θ� ���ʿ� �������� ���̰�,
                // �����ʿ��� �����ٸ�  �����ʿ� �������� ���δ�.(��Ʈ����� ��� ����)
                //---------------------------------------------------------------

                Node* childParent = childNode->parent;

                if (childParent->left == childNode)
                {
                    childParent->left = childNode->right;
                }
                else if (childParent->right == childNode)
                {
                    childParent->right = childNode->right;
                }

                childNode->right->parent = childParent;

                replaceNode = childNode->right;
                delNodeColor = childNode->color;

                delete childNode;
            }
            if (delNodeColor == NODE_COLOR::RED)
            {
                return;
            }
            else
            {
                BalanceDeleteTree(replaceNode);
            }
        }
    }
}