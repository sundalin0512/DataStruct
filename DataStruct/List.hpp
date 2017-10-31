#pragma once
namespace Sdalin
{
	template <class T>
	class list {
	private:

		struct Node
		{
			Node* m_pNext;
			Node* m_pPre;
			T m_data;
			Node() = default;
			Node(const T& other)
			{
				m_data = other;
			}
		};
		Node m_node;
		size_t m_size;
	public:

		class iterator
		{
		public:
			iterator()
			{
				node = nullptr;
			}
			iterator(iterator& other)
			{
				node = other.node;
			}
			iterator(Node* node)
			{
				this->node = node;
			}

			~iterator()
			{

			}
			iterator& operator ++ ()
			{
				node = node->m_pNext;
				return *this;
			}
			iterator operator ++ (int)
			{
				iterator tmp = *this;
				node = node->m_pNext;
				return tmp;
			}
			bool operator == (iterator & other) const
			{
				return this->node == other.node;
			}
			bool operator != (iterator & other) const
			{
				return this->node != other.node;
			}

			const T& operator * () const
			{
				return node->m_data;
			}
			Node* operator -> () const
			{
				return node;
			}

			T& operator * ()
			{
				return node->m_data;
			}
			Node* operator -> ()
			{
				return node;
			}

			operator Node*() const
			{
				return node;
			}
		protected:
			Node* node;
		};
	public:
		// construct/copy/destroy:
		list()
		{
			m_node.m_pNext = &m_node;
			m_node.m_pPre = &m_node;
			m_node.m_data = T();
			m_size = 0;
		}
		explicit list(int  n) : list()
		{
			insert(end(), n, T());
		}
		list(size_t n, const T& value) : list()
		{
			insert(end(), n, value);
		}
		list(const list<T>& x)
		{
			for (auto iter = x.begin(); iter != x.end(); iter++)
			{
				insert(end(), *iter);
			}
		}
		~list()
		{
			for (auto iter = begin(); iter != end(); )
			{
				erase(iter++);
			}
		}

		list<T>& operator=(const list<T>& x)
		{
			erase(begin(), end());
			for (auto iter = x.begin(); iter != x.end(); iter++)
			{
				insert(end(), *iter);
			}
			return *this;
		}
		void assign(size_t n, const T& t)
		{
			erase(begin(), end());
			insert(end(), n, t);
		}

		// iterators:
		iterator                begin() noexcept
		{
			return m_node.m_pNext;
		}
		iterator          begin() const noexcept
		{
			return m_node.m_pNext;
		}

		iterator                end() noexcept
		{
			return m_node.m_pPre;
		}
		iterator          end() const noexcept
		{
			return m_node.m_pPre;
		}

		// capacity:
		size_t size() const noexcept
		{
			return m_size;
		}

		size_t max_size() const noexcept
		{
			return (size_t() - 1) / sizeof(T);
		}

		void      resize(size_t sz)
		{
			if (size() > sz)
			{
				auto iter = begin();
				for (size_t i = 0; i < size(); i++)
					iter++;
				auto tmp = iter;
				while (++tmp != end())
				{
					erase(tmp);
					tmp = iter;
				}
				erase(iter);
			}
			else
			{
				insert(end(), sz - size(), T());
			}
		}

		void      resize(size_t sz, const T& c)
		{
			if (size() > sz)
			{
				auto iter = begin();
				for (size_t i = 0; i < size(); i++)
					iter++;
				auto tmp = iter;
				while (++tmp != end())
				{
					erase(tmp);
					tmp = iter;
				}
				erase(iter);
			}
			else
			{
				insert(end(), sz - size(), T(c));
			}
		}
		bool      empty() const noexcept
		{
			return size() == 0;
		}

		// element access:
		T&       front()
		{
			return m_node.m_pNext->m_data;
		}
		const T& front() const
		{
			return m_node.m_pNext->m_data;
		}
		T&       back()
		{
			return m_node.m_pPre->m_data;
		}
		const T& back() const
		{
			return m_node.m_pPre->m_data;
		}

		// modifiers:
		void pop_front()
		{
			erase(begin());
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void pop_back()
		{
			erase(end());
		}

		iterator insert(iterator position, const T& x)
		{
			auto tmp = new Node(x);
			position->m_pPre->m_pNext = tmp;
			tmp->m_pPre = position->m_pPre;
			position->m_pPre = tmp;
			tmp->m_pNext = position;
			m_size++;
			return tmp;
		}
		iterator insert(iterator position, size_t n, const T& x)
		{
			iterator ret;
			for (size_t i = 0; i < n; i++)
			{
				ret = insert(position, x);
			}
			return ret;
		}

		iterator erase(iterator position)
		{
			auto ret = position->m_pNext;
			position->m_pNext->m_pPre = position->m_pPre;
			position->m_pPre->m_pNext = position->m_pNext;
			delete (Node*)position;
			m_size--;
			return ret;
		}
		iterator erase(iterator first, iterator last)
		{
			auto ret = last->m_pNext;
			last->m_pNext->m_pPre = first->m_pPre;
			first->m_pPre->m_pNext = last->m_pNext;
			for (auto iter = first; iter != last;)
			{
				delete (Node*)++iter;
				m_size--;
			}
			delete (Node*)first;
			m_size--;
			return ret;
		}
		void     swap(list<T>& right)
		{
			auto temp = right;
			right = *this;
			*this = temp;
		}
		void     clear() noexcept
		{
			for (auto iter = begin(); iter != end();)
			{
				delete (Node*)++iter;
			}
			delete (Node*)begin();
			m_size = 0;
			m_node.m_pNext = &m_node;
			m_node.m_pPre = &m_node;
		}


	};

}


