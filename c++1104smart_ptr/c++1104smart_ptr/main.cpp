#include <iostream>

using namespace std;
/*
template<class T>
class smart_ptr{
	T* m_ptr;
public:
	smart_ptr(T* ptr = nullptr) :
		m_ptr(ptr){}

	~smart_ptr(){
		if (m_ptr){
			delete[] m_ptr;
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
};

class Test{
public:
	int m_a;
};


int main(){
	smart_ptr<Test> sp(new Test);

	sp->m_a = 5;

	cout << sp->m_a;
	system("pause");
	return 0;
}
*/