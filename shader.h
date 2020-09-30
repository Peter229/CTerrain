#pragma once
#include "gl_includes.h"
#include <stdio.h>

void shader_delete(unsigned int *program);

void shader_gen(unsigned int *program);

void shader_use(unsigned int *program);