#pragma once
#include <cassert>
#include <vector>
#include <list>

using namespace std;

template<typename T>
class ObjectPool {
public:
	//Constructor del pool
	ObjectPool(size_t size) {
		size_ = size;
		objs_ = new T[size_];
		for (auto i(0u); i < size_; i++) {
			objsPtrs_.push_back(&objs_[i]);
			free_.push_back(&objs_[i]);
		}
	}

	//Destructor del pool
	virtual ~ObjectPool() {
		delete[] objs_;
	}

	//Devuelve el primer elemento del pool libre
	T* getObj() {
		if (!free_.empty()) {
			T* o = free_.front();
			free_.pop_front();
			return o;
		} else
			return nullptr;
	}
	//Elimina un objeto 
	void relObj(T* p) {
		size_t idx = p-objs_;
		assert(idx >=0 && idx<size_);
		free_.push_back(p);
	}
	
	//Devuelve el pool
	const std::vector<T*>& getPool() {
		return objsPtrs_;
	}



private:
	//Tamañp del pool
	size_t size_;
	//Puntero al array dinámico
	T *objs_;
	//Punteros a los objetos
	vector<T*> objsPtrs_;
	//Objetos a eliminar
	list<T*> free_;
};

