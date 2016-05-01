#include "grid_model.hh"

namespace QtGridModel { namespace Detail {

GridModelBase::GridModelBase(int recordTypeId, RecordType& recordType, QObject *parent) :
	QAbstractTableModel(parent),
	mRecordTypeId(recordTypeId),
	mRecordType(recordType)
{
}

QVariant GridModelBase::data(const QModelIndex& index, int role) const
{
	assert(size_t(index.column()) < mColumns.size());
	assert(size_t(index.row()) < mRecords.size());

	const void* p = mRecords[index.row()];
	RecordPtr recordPtr(p, mRecordTypeId);
	return mColumns[index.column()]->gridData(recordPtr, role);
}

QVariant GridModelBase::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return mColumns[section]->name();
	}
	return {};
}

}}
