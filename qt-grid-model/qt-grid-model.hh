// (C) Maciej Gajewski, 2016
#pragma once

#include <QVariant>
#include <QMap>
#include <QSharedPointer>

#include <memory>
#include <stdexcept>

namespace QtGridModel {

class BadRecordPtrCast : public std::bad_cast
{
public:
	BadRecordPtrCast(int fromTypeId, int toTypeId)
	{
		const char* from = QMetaType::metaObjectForType(fromTypeId)->className();
		const char* to = QMetaType::metaObjectForType(toTypeId)->className();
		mWhat = std::string("bad cast of RecordPtr from ") + from + " to " + to;
	}

	const char* what() const noexcept override { return mWhat.c_str(); }

private:
	std::string mWhat;
};

// type-erased record pointer
class RecordPtr
{
public:
	RecordPtr() = default;
	RecordPtr(const void* ptr, int type) : mTypeId(type), mPtr(ptr) {}

	template<typename T>
	const T* as() const
	{
		if (mTypeId != qMetaTypeId<T>())
		{
			throw BadRecordPtrCast(mTypeId, qMetaTypeId<T>());
		}
		return reinterpret_cast<const T*>(mPtr);
	}

private:

	int mTypeId = QMetaType::UnknownType;
	const void* mPtr = nullptr;
};

/// General information about the data type
enum class FieldClass {
	Numeric,	// can be converted to double
	Text,		// text data, can be converted to QString
	Other		// other
};

/// Record field. Fields is a gateway between the actual data, and data binding.
class Field
{
public:

	Field(const QString& name) : mName(name) {}
	Field(const Field&) = delete;

	const QString& name() const { return mName; }


	// data getters
	virtual QVariant gridData(RecordPtr recordPtr, int role) const = 0;

private:

	QString mName;
};

/// Describes a record type, by providing collection of fields
class RecordType
{
public:

	RecordType(const QString& name) : mName(name) {}
	RecordType(const RecordType&) = delete;

	void addField(Field* f) { addField(QSharedPointer<Field>(f)); }

	void addField(const QSharedPointer<Field>& field)
	{
		if (mFields.contains(field->name()))
		{
			throw std::logic_error("field " + field->name().toStdString() + " already defined");
		}
		mFields.insert(field->name(), field);
	}

	QList<Field*> allFields() const
	{
		QList<Field*> out;
		out.reserve(mFields.size());
		for(const auto& p : mFields)
		{
			out.push_back(p.data());
		}
		return out;
	}

private:

	QString mName;
	QMap<QString, QSharedPointer<Field>> mFields;

};

}
