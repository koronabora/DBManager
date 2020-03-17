#include "ListBox.h"

ListBox::ListBox(QWidget* _parent) : QComboBox(_parent)
{
	//_model = new QStandardItemModel();
	setModel(&_model);

	setEditable(true);
	lineEdit()->setReadOnly(true);
	lineEdit()->installEventFilter(this);
	setItemDelegate(new QCheckListStyledItemDelegate(this));

	connect(lineEdit(), &QLineEdit::selectionChanged, lineEdit(), &QLineEdit::deselect);
	connect((QListView*)view(), SIGNAL(pressed(QModelIndex)), this, SLOT(on_itemPressed(QModelIndex)));
	connect(&_model, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this, SLOT(on_modelDataChanged()));
}

ListBox::~ListBox()
{
	//_model->deleteLater();
}

QStandardItem* ListBox::addCheckItem(const QString &label, const QVariant &data, const Qt::CheckState checkState, const long long& id)
{
	QStandardItem* item = new QStandardItem(label);
	item->setCheckState(checkState);
	item->setData(data);
	item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

	_model.appendRow(item);
	_itemIds.append(id);

	return item;
}

bool ListBox::eventFilter(QObject* _object, QEvent* _event)
{
	if (_object == lineEdit() && _event->type() == QEvent::MouseButtonPress)
	{
		showPopup();
		return true;
	}
	return false;
}


void ListBox::on_itemPressed(const QModelIndex &index)
{
	QStandardItem* item = _model.itemFromIndex(index);
	if (item)
		if (item->checkState() == Qt::Checked)
			item->setCheckState(Qt::Unchecked);
		else
			item->setCheckState(Qt::Checked);
}

void ListBox::on_modelDataChanged()
{}

QVector<long long> ListBox::getAllCheckedItemIds()
{
	QVector<long long> res;
	for (int i = 0; i < _model.rowCount(); ++i) {
		if (_model.item(i)->checkState() == (Qt::CheckState::Checked)) {
			if (i <= _itemIds.size())
				res.append(_itemIds.at(i-1));
		}
	}
	return res;
}

QCheckListStyledItemDelegate::QCheckListStyledItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void QCheckListStyledItemDelegate::paint(QPainter* painter_, const QStyleOptionViewItem& option_, const QModelIndex& index_) const
{
	QStyleOptionViewItem & refToNonConstOption = const_cast<QStyleOptionViewItem &>(option_);
	refToNonConstOption.showDecorationSelected = false;
	QStyledItemDelegate::paint(painter_, refToNonConstOption, index_);
}