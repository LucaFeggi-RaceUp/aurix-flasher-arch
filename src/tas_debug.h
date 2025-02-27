/*
 * ********************************************************************************************************************
 *  Copyright 2022 Infineon Technologies AG
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * ******************************************************************************************************************** */
#pragma once

#undef TAS_DBG
#ifdef TAS_DEBUG
#define TAS_DBG 1
#else
#define TAS_DBG 0
#endif

// Inspired by StackOverflow answer: https://stackoverflow.com/a/1644898

#define tas_debug_print(fmt, ...) \
	{ if (TAS_DBG) fprintf(stderr, fmt, ##__VA_ARGS__); }

#define tas_debug_printloc(fmt, ...) \
	{ if (TAS_DBG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); }
	