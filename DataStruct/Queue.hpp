#pragma once
#include "Deque.hpp"
namespace Sdalin
{
	template <class T, class Container = Deque<T> >
	class Queue {
	protected:
		Container c;
	public:
		explicit Queue(const Container& cont = Container()) 
		{
			c = cont;
		}

		Queue(const Queue& other)
		{
			c = other.c;
		}

		bool empty() const {
			return c.empty();
		}
		size_t size() const {
			return c.size();
		}
		T& front() {
			return c.front();
		}
		const T& front() const {
			return c.front();
		}
		T& back() {
			return c.back();
		}
		const T& back() const {
			return c.back();
		}
		void push(const value_type& x) {
			c.push_back(x);
		}
		void pop() {
			c.pop_front();
		}
	};
}