//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_DEFS_H
#define OPENDMI_DEFS_H

#pragma once

#ifndef _WIN32
#   include <sys/cdefs.h>
#else // _WIN32
#   if defined(__cplusplus)
#       define __BEGIN_DECLS extern "C" {
#       define __END_DECLS   }
#   else
#       define __BEGIN_DECLS
#       define __END_DECLS
#   endif
#endif // _WIN32

#include <iso646.h>

// Modern features support on MSVC
#ifdef _MSC_VER

// Zero-sized array in struct/union
#pragma warning(disable: 4200)

// Nameless struct/union
#pragma warning(disable: 4201)

// Nullptr emulation
#if !defined(__cplusplus)
#   define nullptr ((void *)0)
#endif // !__cplusplus

#endif // _MSC_VER

// Array size macro
#define dmi_array_size(x) (sizeof(x) / sizeof((x)[0]))

// Value pointer macro
#define dmi_value_ptr(x) &(typeof(x)){ (x) }

// Cross-platform attribute unused macro
#define dmi_unused(x) (void)(x)

// Cross-compiler packed structures support
#ifdef _MSC_VER
#   define dmi_packed_struct(...) __pragma(pack(push, 1)) struct __VA_ARGS__ __pragma(pack(pop))
#   define dmi_packed_union(...) __pragma(pack(push, 1)) union __VA_ARGS__ __pragma(pack(pop))
#else
#   define dmi_packed_struct(...) struct __attribute__((packed)) __VA_ARGS__
#   define dmi_packed_union(...) union __attribute__((packed)) __VA_ARGS__
#endif

// Cross-compiler thread-local specifier support
#if !defined(thread_local) && !defined(__cplusplus)
#   if (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_THREADS__)
#       define thread_local _Thread_local
#   elif defined(_WIN32) && (defined(_MSC_VER) || defined(__ICL))
#       define thread_local __declspec(thread)
#   elif defined(__GNUC__) || defined(__clang__)
#       define thread_local __thread
#   else
#       error "Cannot define thread_local"
#   endif
#endif // !thread_local && !__cplusplus

#define dmi_member_size(type, member)   sizeof(((type *)0)->member)
#define dmi_element_size(type, member)  sizeof(*((type *)0)->member)
#define dmi_member_offset(type, member) offsetof(type, member)

#endif // !OPENDMI_DEFS_H
