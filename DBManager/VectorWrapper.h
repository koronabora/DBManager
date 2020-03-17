#pragma once

#include <QVector>
#include <QObject>
#include "Types.h"

class VectorWrapper : public QObject
{
	Q_OBJECT
public:
	VectorWrapper();
	~VectorWrapper();

	Task at(const size_t& pos);
	void removeAt(const size_t& pos);
	void append(Task data);
	size_t size() const;

private:
	QVector<Task> _vec;
	
signals:
	void removed(const size_t& pos);
	void inserted(const Task& data);
};