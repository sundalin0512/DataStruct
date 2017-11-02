#pragma once

#include "Queue.hpp"
#include "Stack.hpp"


namespace Sdalin {
	template<class T>
	class BTree
	{

	public:
		struct Node
		{
			Node* m_pParent;
			Node* m_pLeft;
			Node* m_pRight;
			T m_data;
			Node()
			{
				m_pParent = nullptr;
				m_pLeft = nullptr;
				m_pRight = nullptr;
			}

			explicit Node(const Node& other) : Node()
			{
				m_data = other.m_data;
			}
			explicit Node(const T& data) : Node()
			{
				m_data = data;
			}
			~Node() = default;
		};
		Node* m_root;
		size_t m_size;

	public:
		BTree()
			: m_root(new Node), m_size(0)
		{
			m_root->m_pParent = nullptr;
		}
		BTree(const BTree& other)
		{
			m_size = 0;
			Queue<Node*> nodes = other.layer();
			while (!nodes.empty())
			{
				insert(*(nodes.front()));
				nodes.pop();
			}
		}
		~BTree()
		{
			Queue<Node*> nodes = layer();
			while (!nodes.empty())
			{
				delete nodes.front();
				nodes.pop();
			}
			delete m_root;
		}
		bool isEmpty() const
		{
			return m_size == 0;
		}

		Node* insert(const T& data)
		{
			Node* node = new Node(data);
			if (m_root->m_pParent == nullptr)
			{
				m_root->m_pParent = node;
				m_root->m_pParent->m_pParent = m_root;
				return m_root->m_pParent;
			}
			Node* parent = m_root->m_pParent;
			Node* nextNode = parent;
			while (nextNode != nullptr)
			{
				parent = nextNode;
				if (parent->m_data == data)
				{
					return parent;
				}
				else if (parent->m_data > data)
				{
					nextNode = parent->m_pLeft;
				}
				else if (parent->m_data < data)
				{
					nextNode = parent->m_pRight;
				}
			}
			if (parent->m_data > data)
			{
				parent->m_pLeft = node;
			}
			else if (parent->m_data < data)
			{
				parent->m_pRight = node;
			}
			m_size++;
			return node;
		}

		bool erase(const T& data)
		{
			Node* node = query(data);
			if (node == nullptr)
				return false;
			erase(node);
			m_size--;
			return true;
		}

		bool modify(const T& oldData, const T& newData)
		{
			if (!erase(oldData))
			{
				return false;
			}
			insert(newData);
			return true;
		}

		Node* query(const T& data)
		{
			Node* parent = m_root->m_pParent;
			if (parent == nullptr)
				return nullptr;
			Node* nextNode = parent;
			while (nextNode != nullptr)
			{
				parent = nextNode;
				if (parent->m_data == data)
				{
					return parent;
				}
				else if (parent->m_data > data)
				{
					nextNode = parent->m_pLeft;
				}
				else if (parent->m_data < data)
				{
					nextNode = parent->m_pRight;
				}
			}
			return nullptr;
		}

		//层序遍历
		Queue<Node*> layer()
		{
			Queue<Node*> myQueue;
			Queue<Node*> retQueue;
			if (m_root->m_pParent == nullptr)
			{
				return myQueue;
			}

			myQueue.push(m_root->m_pParent);
			retQueue.push(m_root->m_pParent);

			while (!myQueue.empty())
			{
				Node* pNode = myQueue.front();
				if (pNode->m_pLeft != nullptr)
				{
					myQueue.push(pNode->m_pLeft);
					retQueue.push(pNode->m_pLeft);
				}

				if (pNode->m_pRight != nullptr)
				{
					myQueue.push(pNode->m_pRight);
					retQueue.push(pNode->m_pRight);
				}

				myQueue.pop();
			}
			return retQueue;

		}

		//先序遍历
		Queue<Node*> DLR()
		{
			Stack<Node*> myStack;
			Queue<Node*> retQueue;
			if (m_root->m_pParent == nullptr)
			{
				return retQueue;
			}
			myStack.push(m_root->m_pParent);
			Node* pNode = myStack.top();
			while (!myStack.empty())
			{
				while (pNode != nullptr)
				{
					retQueue.push(pNode);
					myStack.push(pNode);
					pNode = pNode->m_pLeft;
				}
				if (!myStack.empty())
				{
					pNode = myStack.top();
					myStack.pop();
					pNode = pNode->m_pRight;
				}
			}
			return retQueue;
		}

		//中序遍历
		Queue<Node*> LDR()
		{
			Stack<Node*> myStack;
			Queue<Node*> retQueue;
			if (m_root->m_pParent == nullptr)
			{
				return retQueue;
			}
			myStack.push(m_root->m_pParent);
			Node* pNode = myStack.top();
			while (!myStack.empty())
			{
				while (pNode != nullptr)
				{

					myStack.push(pNode);
					pNode = pNode->m_pLeft;
				}
				if (!myStack.empty())
				{
					pNode = myStack.top();
					retQueue.push(pNode);
					myStack.pop();
					pNode = pNode->m_pRight;
				}
			}
			retQueue.pop();
			return retQueue;
		}

		//后序遍历
		Queue<Node*> LRD()
		{
			Stack<Node*> myStack;
			Stack<Node*> myStack2;
			Queue<Node*> retQueue;
			if (m_root->m_pParent == nullptr)
			{
				return retQueue;
			}
			myStack.push(m_root->m_pParent);
			Node* pNode = myStack.top();
			while (!myStack.empty())
			{
				while (pNode != nullptr)
				{
					myStack.push(pNode);
					myStack2.push(pNode);
					pNode = pNode->m_pRight;
				}

				if (!myStack.empty())
				{
					pNode = myStack.top();
					myStack.pop();
					pNode = pNode->m_pLeft;
					
				}
			}
			while (!myStack2.empty())
			{
				retQueue.push(myStack2.top());
				myStack2.pop();
			}
			return retQueue;
		}

	private:
		void erase(const Node* node)
		{
			Node* maxLeftNode = node->m_pLeft;
			if (maxLeftNode == nullptr)
			{
				node->m_data = node->m_pRight->m_data;
				node->m_pRight = node->m_pRight->m_pRight;
				node->m_pLeft = node->m_pRight->m_pLeft;
				delete node->m_pRight;
			}
			while (maxLeftNode->m_pRight != nullptr)
			{
				maxLeftNode = maxLeftNode->m_pRight;
			}
			if (maxLeftNode->m_pParent == node)
			{
				node->m_data = maxLeftNode->m_data;
				node->m_pRight = maxLeftNode->m_pRight;
				node->m_pLeft = maxLeftNode->m_pLeft;
				delete maxLeftNode;
			}
			else
			{
				node->m_data = maxLeftNode->m_data;
				maxLeftNode->m_pParent->m_pRight = maxLeftNode->m_pLeft;
				maxLeftNode->m_pLeft->m_pParent = maxLeftNode->m_pParent;
				delete maxLeftNode;
			}
		}
	};
}
