#include "data_model.hh"
#include "function.hh"

#include <qt-grid-model/grid_model.hh>

#include <QApplication>
#include <QTableView>



int main(int argc, char** argv)
{
	using namespace QtGridModel::Examples::Grid;

	QApplication app(argc, argv);

	QSharedPointer<QtGridModel::RecordType> recordType = InitFunctionRecordType();
	QtGridModel::GridModel<Function> model(*recordType);

	// add all columns
	model.appendColumns(recordType->allFields());

	// add some data
	QList<Function> functions;
	for(int i = 0; i < 5; i++)
	{
		Function f;
		f.InitWithRandomParams();
		functions.push_back(f);

		model.appendRow(&functions.back());
	}


	QTableView view;
	view.setModel(&model);

	view.show();

	return app.exec();
}
