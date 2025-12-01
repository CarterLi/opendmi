//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <Python.h>

typedef struct
{
    PyObject_HEAD
} Context;

static void Context_dealloc(Context *self)
{
    PyObject *obj = (PyObject *)self;

    obj->ob_type->tp_free(obj);
}

static PyObject *Context_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Context *self;

    (void)args;
    (void)kwds;

    self = (Context *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static int Context_init(Context *self, PyObject *args, PyObject *kwds)
{
    (void)self;
    (void)args;
    (void)kwds;

    return 0;
}

static PyMemberDef Context_members[] =
{
    { nullptr, 0, 0, 0, nullptr }
};

static PyMethodDef Context_methods[] =
{
    { nullptr, nullptr, 0, nullptr }
};

PyTypeObject Context_type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name           = "opendmi.Context",
    .tp_basicsize      = sizeof(Context),
    .tp_itemsize       = 0,
    .tp_dealloc        = (destructor)Context_dealloc,
    .tp_getattr        = 0,
    .tp_setattr        = 0,
    .tp_repr           = 0,
    .tp_as_number      = 0,
    .tp_as_sequence    = 0,
    .tp_as_mapping     = 0,
    .tp_hash           = 0,
    .tp_call           = 0,
    .tp_str            = 0,
    .tp_getattro       = 0,
    .tp_setattro       = 0,
    .tp_as_buffer      = 0,
    .tp_flags          = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
    .tp_doc            = "OpenDMI context",
    .tp_traverse       = 0,
    .tp_clear          = 0,
    .tp_richcompare    = 0,
    .tp_weaklistoffset = 0,
    .tp_iter           = 0,
    .tp_iternext       = 0,
    .tp_methods        = Context_methods,
    .tp_members        = Context_members,
    .tp_getset         = 0,
    .tp_base           = 0,
    .tp_dict           = 0,
    .tp_descr_get      = 0,
    .tp_descr_set      = 0,
    .tp_dictoffset     = 0,
    .tp_init           = (initproc)Context_init,
    .tp_alloc          = 0,
    .tp_new            = (newfunc)Context_new
};
