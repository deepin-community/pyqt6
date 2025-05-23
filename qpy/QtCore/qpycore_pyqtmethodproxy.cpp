// This contains the implementation of the pyqtMethodProxy type.
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


#include <Python.h>

#include <sip.h>

#include <QGenericArgument>
#include <QGenericReturnArgument>
#include <QMetaMethod>
#include <QObject>

#include "qpycore_chimera.h"
#include "qpycore_pyqtmethodproxy.h"


// The type object.
PyTypeObject *qpycore_pyqtMethodProxy_TypeObject;


// Forward declarations.
extern "C" {
static PyObject *pyqtMethodProxy_call(PyObject *self, PyObject *args,
        PyObject *kw_args);
static void pyqtMethodProxy_dealloc(PyObject *self);
}

static void parse_arg(PyObject *args, int arg_nr,
        const QList<QByteArray> &types, QGenericArgument &arg,
        Chimera::Storage **storage, bool &failed, const char *py_name);


// Define the slots.
static PyType_Slot qpycore_pyqtMethodProxy_Slots[] = {
    {Py_tp_new,         (void *)PyType_GenericNew},
    {Py_tp_dealloc,     (void *)pyqtMethodProxy_dealloc},
    {Py_tp_call,        (void *)pyqtMethodProxy_call},
    {0,                 0}
};


// Define the type.
static PyType_Spec qpycore_pyqtMethodProxy_Spec = {
    "PyQt6.QtCore.pyqtMethodProxy",
    sizeof (qpycore_pyqtMethodProxy),
    0,
    Py_TPFLAGS_DEFAULT,
    qpycore_pyqtMethodProxy_Slots
};


// The type dealloc slot.
static void pyqtMethodProxy_dealloc(PyObject *self)
{
    qpycore_pyqtMethodProxy *mp = (qpycore_pyqtMethodProxy *)self;

    delete mp->py_name;

    PyObject_Del(self);
}


// The type call slot.
static PyObject *pyqtMethodProxy_call(PyObject *self, PyObject *args,
        PyObject *kw_args)
{
    qpycore_pyqtMethodProxy *mp = (qpycore_pyqtMethodProxy *)self;

    const char *py_name = mp->py_name->constData();

    // Check for keyword arguments.
    if (kw_args)
    {
        PyErr_Format(PyExc_TypeError,
                "%s() does not support keyword arguments", py_name);
        return 0;
    }

    QMetaMethod method = mp->qobject->metaObject()->method(mp->method_index);
    QList<QByteArray> arg_types = method.parameterTypes();

    if (PyTuple_Size(args) != arg_types.size())
    {
        PyErr_Format(PyExc_TypeError,
                "%s() called with %zd arguments but %d expected",
                py_name, PyTuple_Size(args), arg_types.size());
        return 0;
    }

    // Parse the return type and the arguments.
    QGenericReturnArgument ret;
    QGenericArgument a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    Chimera::Storage *return_storage, *storage[10];
    QByteArray return_type(method.typeName());
    bool failed = false;

    return_storage = 0;

    if (!return_type.isEmpty())
    {
        const Chimera *ct = Chimera::parse(return_type);

        if (!ct)
        {
            PyErr_Format(PyExc_TypeError,
                    "unable to convert return value of %s from '%s' to a Python object",
                    py_name, return_type.constData());
            return 0;
        }

        return_storage = ct->storageFactory();

        ret = QGenericReturnArgument(return_type.constData(),
                return_storage->address());
    }

    parse_arg(args, 0, arg_types, a0, storage, failed, py_name);
    parse_arg(args, 1, arg_types, a1, storage, failed, py_name);
    parse_arg(args, 2, arg_types, a2, storage, failed, py_name);
    parse_arg(args, 3, arg_types, a3, storage, failed, py_name);
    parse_arg(args, 4, arg_types, a4, storage, failed, py_name);
    parse_arg(args, 5, arg_types, a5, storage, failed, py_name);
    parse_arg(args, 6, arg_types, a6, storage, failed, py_name);
    parse_arg(args, 7, arg_types, a7, storage, failed, py_name);
    parse_arg(args, 8, arg_types, a8, storage, failed, py_name);
    parse_arg(args, 9, arg_types, a9, storage, failed, py_name);

    // Invoke the method.
    PyObject *result = 0;

    if (!failed)
    {
        Py_BEGIN_ALLOW_THREADS
        failed = !method.invoke(mp->qobject, Qt::DirectConnection, ret, a0, a1,
                a2, a3, a4, a5, a6, a7, a8, a9);
        Py_END_ALLOW_THREADS

        if (failed)
        {
            PyErr_Format(PyExc_TypeError, "invocation of %s() failed", py_name);
        }
        else if (return_storage)
        {
            result = return_storage->toPyObject();
        }
        else
        {
            result = Py_None;
            Py_INCREF(result);
        }
    }

    // Release any storage.
    if (return_storage)
    {
        delete return_storage->type();
        delete return_storage;
    }

    for (int i = 0; i < 10; ++i)
    {
        Chimera::Storage *st = storage[i];

        if (st)
        {
            delete st->type();
            delete st;
        }
    }

    return result;
}


// Convert a Python object to a QGenericArgument.
static void parse_arg(PyObject *args, int arg_nr,
        const QList<QByteArray> &types, QGenericArgument &arg,
        Chimera::Storage **storage, bool &failed, const char *py_name)
{
    // Initialise so that we can safely release later.
    storage[arg_nr] = 0;

    // If we have already failed then there is nothing to do.
    if (failed)
        return;

    // If we have run out of arguments then there is nothing to do.
    if (arg_nr >= types.size())
        return;

    PyObject *py_arg = PyTuple_GetItem(args, arg_nr);
    const QByteArray &cpp_type = types.at(arg_nr);

    const Chimera *ct = Chimera::parse(cpp_type);
    Chimera::Storage *st;

    if (ct)
        st = ct->fromPyObjectToStorage(py_arg);
    else
        st = 0;

    if (!st)
    {
        if (ct)
            delete ct;

        PyErr_Format(PyExc_TypeError,
                "unable to convert argument %d of %s from '%s' to '%s'",
                arg_nr, py_name, sipPyTypeName(Py_TYPE(py_arg)),
                cpp_type.constData());

        failed = true;
        return;
    }

    storage[arg_nr] = st;

    arg = QGenericArgument(cpp_type.constData(), st->address());
}


// Initialise the type and return true if there was no error.
bool qpycore_pyqtMethodProxy_init_type()
{
    qpycore_pyqtMethodProxy_TypeObject = (PyTypeObject *)PyType_FromSpec(
            &qpycore_pyqtMethodProxy_Spec);

    return qpycore_pyqtMethodProxy_TypeObject;
}


// Create a proxy for a bound introspected method.
PyObject *qpycore_pyqtMethodProxy_New(QObject *qobject, int method_index,
        const QByteArray &py_name)
{
    qpycore_pyqtMethodProxy *mp;

    mp = (qpycore_pyqtMethodProxy *)PyType_GenericAlloc(
            qpycore_pyqtMethodProxy_TypeObject, 0);

    if (!mp)
        return 0;

    mp->qobject = qobject;
    mp->method_index = method_index;
    mp->py_name = new QByteArray(py_name);

    return (PyObject *)mp;
}
