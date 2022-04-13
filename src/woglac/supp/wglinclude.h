#pragma once

#ifdef emit
#error Qt must be included AFTER wgl stuff
#endif

// Must be before Qt imports because of "emit" defines clash
#include "../parser/WoglacParser.h"
#include "../parser/WoglacBaseListener.h"
#include "../parser/WoglacLexer.h"

#define QT_NO_FLOAT16_OPERATORS
