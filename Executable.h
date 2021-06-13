#pragma once
class Executable
{
public:
	Executable() {};
	virtual ~Executable() {};
	virtual void execute() = 0;

	template <class T>
	static Executable* from(T func);
};

template <class T>
class __ExecutableImpl : public Executable
{
public:
	__ExecutableImpl(T func) : Executable(), func(func) {};
	void execute() { func(); };
private:
	T func;
};

template <class T>
Executable* Executable::from(T func)
{
	return new __ExecutableImpl<T>(func);
}

