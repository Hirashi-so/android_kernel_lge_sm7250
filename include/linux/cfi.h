/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Clang Control Flow Integrity (CFI) support.
 *
 * Copyright (C) 2019 Google LLC
 */
#ifndef _LINUX_CFI_H
#define _LINUX_CFI_H

#include <linux/stringify.h>

#ifdef CONFIG_CFI_CLANG
#ifdef CONFIG_MODULES

typedef void (*cfi_check_fn)(uint64_t id, void *ptr, void *diag);

/* Compiler-generated function in each module, and the kernel */
#define CFI_CHECK_FN		__cfi_check
#define CFI_CHECK_FN_NAME	__stringify(CFI_CHECK_FN)

extern void CFI_CHECK_FN(uint64_t id, void *ptr, void *diag);

#ifdef CONFIG_CFI_CLANG_SHADOW
extern void cfi_module_add(struct module *mod, unsigned long min_addr,
	unsigned long max_addr);

extern void cfi_module_remove(struct module *mod, unsigned long min_addr,
	unsigned long max_addr);
#else
static inline void cfi_module_add(struct module *mod, unsigned long min_addr,
	unsigned long max_addr)
{
}

static inline void cfi_module_remove(struct module *mod, unsigned long min_addr,
	unsigned long max_addr)
{
}
#endif /* CONFIG_CFI_CLANG_SHADOW */

#endif /* CONFIG_MODULES */
#endif /* CONFIG_CFI_CLANG */

/*
 * Preserve CFI jump table addresses for module entry points.
 */
#ifdef CONFIG_CFI_CLANG
#define __CFI_ADDRESSABLE(fn, __attr) \
	const void *__cfi_jt_ ## fn __visible __attr = (void *)&fn
#else
#define __CFI_ADDRESSABLE(fn, __attr)
#endif

#endif /* _LINUX_CFI_H */
