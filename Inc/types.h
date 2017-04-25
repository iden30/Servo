/***************************************************************************************************
 *   Project:       
 *   Author:        Alex Borisov
 ***************************************************************************************************
 *   Distribution:
 *
 ***************************************************************************************************
 *   MCU Family:    
 *   Compiler:      
 ***************************************************************************************************
 *   File:          types.h
 *   Description:   Types definition
 *
 ***************************************************************************************************
 *   History:       15.09.2010 - [Alex Borisov] - file created
 *
 **************************************************************************************************/

#ifndef __TYPES_H
#define __TYPES_H

    #include <stddef.h>
    #include <stdint.h>
    #include <stdbool.h>

    #ifndef INLINE
    #define INLINE                  inline
    #endif

/***************************************************************************************************
    Useful definitions
 **************************************************************************************************/

#ifndef offsetof
    #define offsetof(s,m)           (size_t)&(((s *)0)->m)
#endif

#ifndef countof
    #define countof(a)              (sizeof(a) / sizeof(*(a)))
#endif

#ifndef alignof
    #define alignof(type)           offsetof(struct { char c; type member; }, member)
#endif


#define _JOIN_2_H(A,B)              A##B
#define _JOIN_2(A,B)                _JOIN_2_H(A,B)
#define _STATIC_ASSERT_H(A)         typedef int _JOIN_2(compile_time_error_in_line_,__LINE__) [(A) ? 1 : -1]
#define STATIC_ASSERT(A)            _STATIC_ASSERT_H(A)




#endif /* __TYPES_H */
/***************************************************************************************************
    end of file: types.h
 **************************************************************************************************/
