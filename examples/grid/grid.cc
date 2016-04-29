#include <QApplication>
#include <QTableView>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QTableView view;

	view.show();

	return app.exec();
}
