#ifndef TEST_H
#define TEST_H

#include "envvar.h"
#include "assert.h"
#include "builtin.h"

#include <stdio.h>

__attribute__((destructor))
static void destructor()
{
	system("leaks test > leak.log");
}

#endif
