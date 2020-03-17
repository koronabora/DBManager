#include "VectorWrapper.h"


VectorWrapper::VectorWrapper()
{};


VectorWrapper::~VectorWrapper()
{};

Task VectorWrapper::at(const size_t& pos)
{
	Task res;
	if (pos < _vec.size())
		res = _vec.at(pos);
	return res;
}

void VectorWrapper::removeAt(const size_t& pos)
{
	if (pos < _vec.size())
		_vec.removeAt(pos);
	emit removed(pos);
}

void VectorWrapper::append(Task data)
{
	_vec.append(data);
	emit inserted(data);
}


size_t VectorWrapper::size() const
{
	return _vec.size();
}