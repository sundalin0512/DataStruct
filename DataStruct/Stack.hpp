#pragma once
#include "Deque.hpp"

namespace Sdalin
{
	template <class T, class Container = Deque<T> >
	class Stack {
	protected:
		Container c;

	public:
		explicit Stack(const Container& cont = Container())
		{
			c = cont;
		}
		Stack(const Stack& other)
		{
			c = other.c;
		}

		bool empty() const {
			return c.empty();
		}
		size_t size() const {
			return c.size();
		}
		T& top() {
			return c.back();
		}
		const T& top() const {
			return c.back();
		}
		void push(const value_type& x) {
			c.push_back(x);
		}

		void pop() {
			c.pop_back();
		}

	};
}