//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <Python.h>

#include <opendmi/python/context.h>

static PyMethodDef methods[] = {
     { nullptr, nullptr, 0, nullptr }
};

static struct PyModuleDef module_def = {
    .m_base    = PyModuleDef_HEAD_INIT,
    .m_name    = "opendmi",
    .m_doc     = "OpenDMI module",
    .m_size    = -1,
    .m_methods = methods
};

PyMODINIT_FUNC PyInit_opendmi(void)
{
    PyObject *module;

    // Create module
    module = PyModule_Create(&module_def);
    if (!module)
        return nullptr;

    // Initialize module
    bool success = false;
    do {
        if (PyModule_AddType(module, &Context_type) < 0)
            break;

        success = true;
    } while (false);

    // Handle errors
    if (!success) {
        PyState_RemoveModule(&module_def);
        return nullptr;
    }

    return module;
}
