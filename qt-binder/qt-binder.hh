// (C) Maciej Gajewski, 2016
#pragma once

#include <QVariant>
#include <QMap>
#include <QSharedPointer>

#include <memory>
#include <stdexcept>

namespace QtBinder {

using Record = QVariant;

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
	virtual QString asString(const Record& record) const = 0;

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


private:

	QString mName;
	QMap<QString, QSharedPointer<Field>> mFields;

};

}
