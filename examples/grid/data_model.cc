// (C) Maciej Gajewski, 2016
#include "data_model.hh"

#include "function.hh"

namespace QtGridModel { namespace Examples { namespace Grid {

class AngularFreqField final : public Field
{
public:
	AngularFreqField() : Field("Angular frequency") {}

	QVariant gridData(RecordPtr recordPtr, int role) const override
	{
		const Function* p = recordPtr.as<Function>();
		if (role == Qt::DisplayRole)
		{
			return QString::number(p->GetW());
		}

		return {};
	}

};


QSharedPointer<RecordType> InitFunctionRecordType()
{
	qRegisterMetaType<QtGridModel::Examples::Grid::Function>();

	QSharedPointer<RecordType> record(new RecordType("3 step harmonic"));

	record->addField(new AngularFreqField);

	return record;
}

}}}


