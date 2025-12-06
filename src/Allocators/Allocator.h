#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>

#define DYNAMIC_SELECTION_ALLOCATORS 1

#if DYNAMIC_SELECTION_ALLOCATORS

typedef struct Allocator {
    void* (*allocate)( struct Allocator* self, const unsigned size );
    void (*free)( struct Allocator* self );
} Allocator;

#else

typedef struct Allocator {
    void* (*allocate)( const unsigned size );
    void (*free)( void );
} Allocator;

#endif

#if DYNAMIC_SELECTION_ALLOCATORS
extern Allocator InitAllocator( Allocator* self );
#else
extern Allocator InitAllocator ( void );
#endif

#endif //ALLOCATOR_H
