#pragma once

#include "qt-grid-model.hh"

#include <QAbstractTableModel>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

namespace QtGridModel { namespace Detail {

struct random_access_tag {};
struct hashed_tag {};

namespace bmi = boost::multi_index;

template<typename T>
using multiindex_container_t = boost::multi_index_container<
	T,
	bmi::indexed_by<
		bmi::random_access<bmi::tag<random_access_tag>>,
		bmi::hashed_non_unique<bmi::tag<hashed_tag>, bmi::identity<T>>
		>
	>;

template<typename T>
class BidiContainer
{
public:

	void reserve(size_t s) { mMI.reserve(s); }
	void push_back(const T& v) { mMI.push_back(v); }
	size_t size() const { return mMI.size(); }

	size_t index_of(const T& v)
	{
		auto& hash_index = boost::get<hashed_tag>(mMI);
		auto& random_index = boost::get<random_access_tag>(mMI);

		auto hash_it = hash_index.find(v);
		if (hash_it == hash_index.end())
			throw std::runtime_error("no such element: " + std::to_string(v));

		const T& found = *hash_it;
		auto random_it = random_index.iterator_to(found);
		return random_it - random_index.begin();
	}

	template<typename It>
	void insert(size_t pos, It first, It last)
	{
		auto& random_access_index = boost::get<random_access_tag>(mMI);
		auto it = random_access_index.begin() + pos;
		random_access_index.insert(it, first, last);
	}

	const T& operator[] (size_t idx) const
	{
		auto& random_access_index = boost::get<random_access_tag>(mMI);
		return random_access_index[idx];
	}

private:

	multiindex_container_t<T> mMI;
};

/// Internal. Type-erased data model
class GridModelBase : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit GridModelBase(int recordTypeId, RecordType& recordType, QObject *parent = nullptr);

	int rowCount(const QModelIndex&) const final override { return mRecords.size(); }
	int columnCount(const QModelIndex&) const final override { return mColumns.size(); }
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:

	using RecordContainer = BidiContainer<void*>;

	template<typename It>
	void insertRecords(size_t pos, It first, It last)
	{
		if (pos > mRecords.size())
			throw std::runtime_error("insertRecords out of bounds");

		size_t count = std::distance(first, last);

		beginInsertRows(QModelIndex(), pos, pos+count-1);
		mRecords.insert(pos, first, last);
		endInsertRows();
	}

	template<typename It>
	void insertColumns(size_t pos, It first, It last)
	{
		if (pos > mColumns.size())
			throw std::runtime_error("insertColumns out of bounds");

		size_t count = std::distance(first, last);

		beginInsertColumns(QModelIndex(), pos, pos+count-1);
		mColumns.insert(mColumns.begin() + pos, first, last);
		endInsertColumns();
	}

	// meta-type-id of the data record. For runtime type-correctes checks
	int mRecordTypeId;

	RecordType& mRecordType;

	// current set of columns
	std::vector<Field*> mColumns;

	// current set of rows
	RecordContainer mRecords;
};

} /// Detail


/// Grid data model, storing pointers to rcords of type T.
template<typename T>
class GridModel : public Detail::GridModelBase
{
public:
	explicit GridModel(RecordType& recordType, QObject *parent = nullptr)
		: Detail::GridModelBase(qMetaTypeId<T>(), recordType, parent)
	{ }

	void appendRow(T* row)
	{
		//insertRecords(mRecords.size(), &row, &row+1);
		void* vp = row;
		mRecords.push_back(vp);
	}

	void appendColumn(Field* field)
	{
		insertColumns(mColumns.size(), &field, &field+1);
	}

	void appendColumns(QList<Field*> fields)
	{
		insertColumns(mColumns.size(), fields.begin(), fields.end());
	}
};

}

