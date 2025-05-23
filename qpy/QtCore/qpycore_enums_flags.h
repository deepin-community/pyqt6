// This defines the interfaces to the pyqtEnum support.
//
// Copyright (c) 2025 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of PyQt6.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#ifndef _QPYCORE_ENUMS_FLAGS_H
#define _QPYCORE_ENUMS_FLAGS_H


#include <QByteArray>
#include <QList>
#include <QMetaType>
#include <QPair>


// Encapsulate the definition of a Python enum as required by QMetaEnum.
struct EnumFlag
{
    QByteArray name;
    bool isFlag;
    QMetaType metaType;
    QList<QPair<QByteArray, int> > keys;
};


EnumFlag qpycore_pop_enum_flag(PyObject *enum_cls);


#endif
