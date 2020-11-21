#include <iostream>
#include "Tree.h"
#include <iostream>
#include <Windows.h>
#include "DrawingNodeObject.h"
#include "MemoryTracer.h"
#include "GlobalVariable.h"
#include <cassert>

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
   

    delete pObject;

    width = (int)(width * 0.5);
    height +=(int)( height * 0.05);
        
    TraverseNPrint2(node->left, x - width, y + height, x,y, width, height);
    TraverseNPrint2(node->right, x + width, y + height, x, y, width, height);

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
            // 루트노드보다 작을때 (Left)
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
                    // 부모노도의 색이 블랙이냐,레드냐에따라 분기 나뉨.
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
            // 루트노드보다 클 때 (Right)
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
    //우선 가운데 노드가 바뀌었으니
    //윗 부모를 연결시켜주자
    // 윗부모 --- Right 
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


    //가운데 노드의부모는 이제 right가된다
    // right노드의 left는  가운데노드가된다

    node->parent = rightNode;

    Node* leftFromRightNode = rightNode->left;
    rightNode->left = node;


    //가운데노드의 right는 right노드의 left가된다
    node->right = leftFromRightNode;

    //right 노드의 left의 부모는 가운데노드가 된다.
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
    //우선 가운데 노드가 바뀌었으니
    //윗 부모를 연결시켜주자
    // 윗부모 --- left
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


    //가운데 노드의부모는 이제 right가된다
    // right노드의 left는  가운데노드가된다

    node->parent = leftNode;

    Node* rightFromLeftNode = leftNode->right;
    leftNode->right = node;


    //가운데노드의 right는 right노드의 left가된다
    node->left= rightFromLeftNode;

    //right 노드의 left의 부모는 가운데노드가 된다.
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
    m_Depth = 0;
    m_MaxBlackNum = 0;
    DepthCheck(m_RootNode,0);
    m_bFirst = true;
    BlackCheck(m_RootNode, 0);
    int a = m_Depth;
    
    int width = 100;
    for (int i = 0; i < m_Depth; ++i)
    {
        width += width * 0.55;
    }
    TraverseNPrint2(m_RootNode,750+x,50+y,0,0, width,40);
  
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
            // 형제 노드가 레드인경우 --> 답이 없음.
            // 형제노드를 블랙으로 만들어줘야함.
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
            // 형제노드가,블랙이고 그 왼쪽자식이 레드인경우--> 회전시켜서 6번으로만들어야함
            //-------------------------------------------------------
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->left->color == NODE_COLOR::RED)
            {
                RotateRight(sibling);
                parent->right->color = NODE_COLOR::BLACK;
                parent->right->right->color = NODE_COLOR::RED;
                if (node == m_Nill)
                {
                    node->parent = parent;
                }
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
             // 형제 노드가 레드인경우 --> 답이 없음.
             // 형제노드를 블랙으로 만들어줘야함.
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
            // 형제노드가,블랙이고 그 왼쪽자식이 레드인경우--> 회전시켜서 6번으로만들어야함
            //-------------------------------------------------------
            else if (sibling->color == NODE_COLOR::BLACK &&
                sibling->right->color == NODE_COLOR::RED)
            {
                RotateLeft(sibling);
                parent->left->color = NODE_COLOR::BLACK;
                parent->left->left->color = NODE_COLOR::RED;

                if (node == m_Nill)
                {
                    node->parent = parent;
                }
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
    if (node == nullptr)
    {
        return;
    }
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
            // 자식 노드가 없는경우
            //---------------------------------------------------------------
            if (node->left == m_Nill && node->right == m_Nill)
            {
                //-------------------------------------------------------
                // 자식노드가없는 경우는 끝단 노드이거나, 아님 루트노드 하나남았을때인데..
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
            // 자식노드가 하나만 있는 경우
            //---------------------------------------------------------------
            else if ((node->left == m_Nill && node->right != m_Nill) || (node->left != m_Nill && node->right == m_Nill))
            {
                //---------------------------------------------------------------
                // 지워야될 노드를 실제로 지우는게 아니라, 그 자식노드의 데이터를 옮기고
                // 자식도 옮긴다음 그 자식노드를 지워버린다.
                //---------------------------------------------------------------

                Node* childNode = nullptr;
                Node* parent = node->parent;

                //-----------------------------
                // Child노드 찾아내기
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
                // Child노드  <------------>노드의 부모 연결
                //-----------------------------
                childNode->parent = parent;

                //-----------------------------
                // 노드가 부모의 레프트였다면, 차일드노드를 레프트로연결
                // 그반대는 라이트로 연결
                //-----------------------------
                if (parent == nullptr)
                {
                    m_RootNode = childNode;
                }
                else
                {
                    if (parent->left == node)
                    {
                        parent->left = childNode;
                    }
                    else if (parent->right == node)
                    {
                        parent->right = childNode;
                    }
                }
                replaceNode = childNode;
                delNodeColor = node->color;

                delete node;
            }
            //---------------------------------------------------------------
            // 자식노드가 둘인 경우
            //---------------------------------------------------------------
            else if (node->left != m_Nill && node->right != m_Nill)
            {
                //---------------------------------------------------------------
                // 지워야 될노드의 자식중 오른쪽을 선택해서 그 오른쪽의 왼쪽 서브노드로 null이나올때까지 찾는다
                // 가장 왼쪽에있는 노드를 지워야될 노드의 데이터와 교환하고, 그 부모에 right를 연결한다
                //---------------------------------------------------------------
                Node* childNode = node->left;

                while (childNode->right != m_Nill)
                {
                    childNode = childNode->right;
                }

                node->data = childNode->data;

                //---------------------------------------------------------------
                // 맨 좌측에있는 노드의 부모의 왼쪽에서 기원됬다면,  그 부모 왼쪽에 오른쪽을 붙이고,
                // 오른쪽에서 기원됬다면  오른쪽에 오른쪽을 붙인다.(루트노드일 경우 조심)
                //---------------------------------------------------------------

                Node* childParent = childNode->parent;

                if (childParent->left == childNode)
                {
                    childParent->left = childNode->left;
                }
                else if (childParent->right == childNode)
                {
                    childParent->right = childNode->left;
                }

                childNode->left->parent = childParent;

                replaceNode = childNode->left;
                replaceNode->parent = childParent;
                delNodeColor = childNode->color;

                delete childNode;
            }
            //else if (node->left != m_Nill && node->right != m_Nill)
            //{
            //    //---------------------------------------------------------------
            //    // 지워야 될노드의 자식중 오른쪽을 선택해서 그 오른쪽의 왼쪽 서브노드로 null이나올때까지 찾는다
            //    // 가장 왼쪽에있는 노드를 지워야될 노드의 데이터와 교환하고, 그 부모에 right를 연결한다
            //    //---------------------------------------------------------------
            //    Node* childNode = node->right;

            //    while (childNode->left != m_Nill)
            //    {
            //        childNode = childNode->left;
            //    }

            //    node->data = childNode->data;

            //    //---------------------------------------------------------------
            //    // 맨 좌측에있는 노드의 부모의 왼쪽에서 기원됬다면,  그 부모 왼쪽에 오른쪽을 붙이고,
            //    // 오른쪽에서 기원됬다면  오른쪽에 오른쪽을 붙인다.(루트노드일 경우 조심)
            //    //---------------------------------------------------------------

            //    Node* childParent = childNode->parent;

            //    if (childParent->left == childNode)
            //    {
            //        childParent->left = childNode->right;
            //    }
            //    else if (childParent->right == childNode)
            //    {
            //        childParent->right = childNode->right;
            //    }

            //    childNode->right->parent = childParent;

            //    replaceNode = childNode->right;
            //    replaceNode->parent = childParent;
            //    delNodeColor = childNode->color;

            //    delete childNode;
            //}
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

void RedBlackTree::DepthCheck(Node* node, int32_t depth)
{
    if (node == nullptr)
    {
        if (m_Depth < depth)
        {
            m_Depth = depth;
        }
        return;
    }
    if (node == m_Nill)
    {
        if (m_Depth < depth)
        {
            m_Depth = depth;
        }
        return;
    }
    ++depth;
    DepthCheck(node->left, depth);
    DepthCheck(node->right, depth);
}

void RedBlackTree::BlackCheck(Node* node, int32_t blackNum)
{
    if (node == nullptr)
    {
        return;
    }
    if (node == m_Nill)
    {
      
        if (m_bFirst)
        {
            m_bFirst = false;
            if (m_MaxBlackNum < blackNum)
            {
                m_MaxBlackNum = blackNum;
            }
        }
        assert(m_MaxBlackNum == blackNum);
       
        return;
    }
    if (node->color == NODE_COLOR::BLACK)
    {
        blackNum++;
    }
    BlackCheck(node->left, blackNum);
    BlackCheck(node->right, blackNum);
}

int32_t RedBlackTree::GetBlackNum()
{
    return m_MaxBlackNum;
}
