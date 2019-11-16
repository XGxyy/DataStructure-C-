#include <iostream>
using namespace std;

template<class T>
class smart_ptr{
	T* m_ptr;
	int* m_pcount;
public:
	smart_ptr(T* ptr = nullptr) :
		m_ptr(ptr),
		m_pcount(new int(1))
		{}

	~smart_ptr(){
		if (*m_pcount > 1){
			(*m_pcount)--;
		}
		else if (m_ptr){
			delete[] m_ptr;
			delete[] m_pcount;
			m_ptr = nullptr;
		}
	}

	T& operator *(){
		return *m_ptr;
	}

	T* operator ->(){
		return m_ptr;
	}

	T& operator [](int i){
		return m_ptr[i];
	}
	smart_ptr(const smart_ptr& o){
		m_ptr = o.m_ptr;
		m_pcount = o.m_pcount;
		(*m_pcount)++;
	}
	smart_ptr& operator = (const smart_ptr& o){
		
		~smart_ptr();

		m_ptr = o.m_ptr;
		m_pcount = o.m_pcount;
		(*m_pcount)++;

		return *this;
	}
};

class Test{
public:
	int m_a;
};


int main(){
	smart_ptr<Test> sp(new Test);

	sp->m_a = 5;

	smart_ptr<Test> sp2(sp);
	cout << sp->m_a;
	cout << sp2->m_a;
	system("pause");
	return 0;
}
