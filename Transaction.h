#pragma once
#include <memory>

template <class T>
class Transaction
{
public:
	Transaction(std::shared_ptr<T> ptr) : ptr(ptr), safePtr(ptr) {}

	std::shared_ptr<T> getPtr() { return std::make_shared<T>(*ptr); }
	void setPtr(std::shared_ptr<T> ptr) { this->ptr = ptr; }
	void rollback() { ptr = safePtr; }
	void commit() { safePtr = ptr; }
private:
	std::shared_ptr<T> ptr;
	std::shared_ptr<T> safePtr;
};

