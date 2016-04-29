#include <QApplication>
#include <QTableView>
#include <QAbstractTableModel>
#include <QDebug>


class TestModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	int rowCount(const QModelIndex&) const override { return 1000; }
	int columnCount(const QModelIndex&) const override { return 1000; }

	QModelIndex index(int row, int col, const QModelIndex& parent) const override
	{
		static quintptr id = 0;
		qDebug() << "index: row=" << row << "col=" << col << ", id=" << id;
		return createIndex(row, col, id++);

	}

	QVariant data(const QModelIndex& index, int role) const override
	{
		qDebug() << "data: row=" << index.row() << ", col=" << index.column() << ", id=" << index.internalId() << ", role=" << role;

		return {};
	}
};

#include "modeltest.moc"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QTableView view;

	TestModel model;
	view.setModel(&model);

	view.show();

	return app.exec();
}
