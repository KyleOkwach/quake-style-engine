/*
* This code contains all file handling logic
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ecs.h"

int model_from_obj(char *filename, Mesh *mesh);