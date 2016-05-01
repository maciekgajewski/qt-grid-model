// (C) Maciej Gajewski, 2016
#pragma once

#include "function.hh"

#include <qt-grid-model/qt-grid-model.hh>

namespace QtGridModel { namespace Examples { namespace Grid {

QSharedPointer<RecordType> InitFunctionRecordType();

}}}

Q_DECLARE_METATYPE(QtGridModel::Examples::Grid::Function)

