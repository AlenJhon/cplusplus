#ifndef WRAPPER_H_
#define WRAPPER_H_

#include "except.h"

template <class Object>
class Cref
{
public:
	Cref() : obj(NULL) {}
	explicit Cref(const Object & x) : obj(&x) {}

	const Object & get() const
	{
		if(isNull()) throw NullPointerException(); else return *obj;
	}

	bool isNull() const
	{
		return obj == NULL;
	}
private:
	const Object *obj;
};

#endif
