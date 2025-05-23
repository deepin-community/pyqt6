// This is the declaration of the PyQtMutexLocker class.
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

#include <QMutex>


// This class implements the Qt5 QMutexLocker on top of the Qt6 template-based
// version.
class PyQtMutexLocker
{
public:
    PyQtMutexLocker(QMutex *mutex, PyObject *wrapper);
    PyQtMutexLocker(QRecursiveMutex *mutex, PyObject *wrapper);
    ~PyQtMutexLocker();

    PyObject *mutex();
    void unlock();
    void relock();

private:
    PyObject *_wrapper;
    QMutexLocker<QMutex> *_locker;
    QMutexLocker<QRecursiveMutex> *_r_locker;

    PyQtMutexLocker(const PyQtMutexLocker &);
};
