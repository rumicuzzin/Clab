/**
 * @file digital_io_common.h
 * @brief Common include file for digital I/O modules
 */

#ifndef DIGITAL_IO_COMMON_H
#define DIGITAL_IO_COMMON_H

/* Include the appropriate header based on which demo is active */
#ifdef DEMO_PART_A
#include "digital_io_a.h"
#endif

#ifdef DEMO_PART_B
#include "digital_io_b.h"
#endif

#ifdef DEMO_PART_C
#include "digital_io_c.h"
#endif

#ifdef DEMO_PART_D
#include "digital_io_d.h"
#endif

#endif /* DIGITAL_IO_COMMON_H */
