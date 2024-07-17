// This contains the definitions for the implementation of dataCache.
//
// Copyright (c) 2024 Riverbank Computing Limited <info@riverbankcomputing.com>
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


#ifndef _QPYOPENGL_DATACACHE_H
#define _QPYOPENGL_DATACACHE_H


#include <Python.h>

#include <QHash>

#include "sipAPIQtOpenGL.h"


// The wrapper around the actual array memory.
struct Array
{
    Array();
    ~Array();

    // Clear the array.
    void clear();

    // Traverse the array for the garbage collector.
    int traverse(visitproc visit, void *arg);

    // The data.  If it is 0 then any data is provided by an object that
    // implements the buffer protocol.
    void *data;

    // The buffer information.  The obj element is a reference to the object
    // that implements the buffer protocol.
    sipBufferInfoDef buffer;
};

typedef QHash<unsigned, Array *> SecondaryCache;


// The cache for all value arrays for a particular primary key.
struct PrimaryCacheEntry
{
    PrimaryCacheEntry();
    ~PrimaryCacheEntry();

    // The cache entry for a secondary key of zero.
    Array skey_0;

    // The cache entries for all non-zero secondary keys.
    SecondaryCache *skey_n;
};

typedef QHash<const char *, PrimaryCacheEntry *> PrimaryCache;


extern "C" {

// This defines the structure of a data cache for OpenGL.
typedef struct {
    PyObject_HEAD

    // The most recent uncached array, if any.
    Array *uncached;

    // The primary cache.
    PrimaryCache *pcache;
} qpyopengl_dataCache;

}


// The type object.
extern PyTypeObject *qpyopengl_dataCache_TypeObject;


bool qpyopengl_dataCache_init_type();
qpyopengl_dataCache *qpyopengl_dataCache_New();


#endif
