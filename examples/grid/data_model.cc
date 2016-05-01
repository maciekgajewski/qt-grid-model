// (C) Maciej Gajewski, 2016
#include "data_model.hh"

#include "function.hh"

namespace QtGridModel { namespace Examples { namespace Grid {

using FunctionPtr = Function*;

class AngularFreqField final : public Field
{
public:
	AngularFreqField() : Field("Angular frequency") {}

	QString asString(const Record& record) const override
	{
		FunctionPtr p = record.value<FunctionPtr>();
		return QString::number(p->GetW());
	}
};


QSharedPointer<RecordType> InitFunctionRecordType()
{
	QSharedPointer<RecordType> record(new RecordType("3 step harmonic"));

	record->addField(new AngularFreqField);

	return record;
}

}}}


Q_DECLARE_METATYPE(QtGridModel::Examples::Grid::FunctionPtr)
