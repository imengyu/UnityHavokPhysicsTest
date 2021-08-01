#pragma once

template <typename T>
class SimpleLinkedList
{
public:
	SimpleLinkedList() {
		begin = nullptr;
		end = nullptr;
		m_size = 0;
	}
	~SimpleLinkedList() {
		clear();
	}

	T* begin;
	T* end;

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
		begin = nullptr;
		end = nullptr;
		m_size = 0;
	}

	int getSize() {
		return m_size;
	}

private:
	int m_size;
};

