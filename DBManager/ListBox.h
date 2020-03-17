#pragma once

#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>
#include <QPointer>

// Thanks to https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720

class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
	QCheckListStyledItemDelegate(QObject* parent = 0);
	void paint(QPainter* painter_, const QStyleOptionViewItem& option_, const QModelIndex& index_) const;
};

class ListBox : public QComboBox
{
	Q_OBJECT

public:
	ListBox(QWidget* _parent = 0);
	~ListBox();

	QStandardItem* ListBox::addCheckItem(const QString& label, const QVariant& data, const Qt::CheckState checkState, const long long& id);
	QVector<long long> getAllCheckedItemIds();

private:
	//QPointer<QStandardItemModel> _model;
	QStandardItemModel _model;
	QVector<long long> _itemIds;
	
protected:
	bool eventFilter(QObject* _object, QEvent* _event);

private slots:
	void on_itemPressed(const QModelIndex &index);
	void on_modelDataChanged();

};

