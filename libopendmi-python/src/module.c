//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <Python.h>

static PyMethodDef methods[] = {
     { nullptr, nullptr, 0, nullptr }
};

static struct PyModuleDef module = {
    .m_base    = PyModuleDef_HEAD_INIT,
    .m_name    = "opendmi",
    .m_doc     = "OpenDMI module",
    .m_size    = -1,
    .m_methods = methods
};

PyMODINIT_FUNC PyInit_opendmi(void)
{
    PyObject *mod;

    mod = PyModule_Create(&module);
    if (!mod)
        return nullptr;

    return mod;
}
