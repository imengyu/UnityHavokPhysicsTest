#pragma once

template <typename T>
class SimpleLinkedList
{
public:
	~SimpleLinkedList() {
		clear();
	}
	
	T* begin = nullptr;
	T* end = nullptr;

	void add(T* n) {
		if (!begin || !end) {
			begin = n;
			end = n;
			m_size = 1;
		}
		else {
			n->prev = end;
			end->next = n;
			end = n;
			m_size++;
		}
	}
	void remove(T* n) {
		if (n->prev) 
			n->prev->next = n->next;
		if (n->next)
			n->next->prev = n->prev;
		m_size--;
	}
	void clear() {
		T* ptr = begin;
		while (ptr) {
			ptr->prev = nullptr;
			T* oldPtr = ptr->next;
			ptr->next = nullptr;
			ptr = oldPtr;
		}
		begin = nullptr;
		end = nullptr;
		m_size = 0;
	}

	int getSize() {
		return m_size;
	}

private:
	int m_size = 0;
};

