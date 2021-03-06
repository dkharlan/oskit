/*
 * Copyright (c) 2001 The University of Utah and the Flux Group.
 * All rights reserved.
 * 
 * This file is part of the Flux OSKit.  The OSKit is free software, also known
 * as "open source;" you can redistribute it and/or modify it under the terms
 * of the GNU General Public License (GPL), version 2, as published by the Free
 * Software Foundation (FSF).  To explore alternate licensing terms, contact
 * the University of Utah at csl-dist@cs.utah.edu or +1-801-585-3271.
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */

#include <oskit/io/absio.h>
#include <oskit/uvm.h>

/* XXX: someone cleanup me */

extern void
svm_init(oskit_absio_t *pager_absio)
{
    /*
     * Since oskit_uvm_init() does nothing if pthread is not initialized. 
     * if svm_init() is called from the pthread init code, this will do nothing.
     * the mprotect() calls issued the pthread library during its initialization
     * are just stored in a buffer and it is done after uvm is initialized.
     */
    oskit_uvm_init();
}
