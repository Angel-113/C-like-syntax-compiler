#include "Allocator.h"

static unsigned long __arena_init_size = 100;

static void* reallocate_buffer ( unsigned char* buffer, unsigned* current_size ) {
    *current_size += (*current_size << 1) + (*current_size << 3);
    buffer = realloc(buffer, *current_size * sizeof(unsigned char));
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file\n");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

#if DYNAMIC_SELECTION_ALLOCATORS /* Is this necessary for what I need to work with? */

static const unsigned __hash_size = 100;
static void* static_allocate ( Allocator* self, unsigned size );
static void static_free ( Allocator* self );

static typedef struct AllocData { /* An allocators data */
    void* instance_address;
    unsigned char* buffer;
    unsigned size;
    unsigned pos;
    struct AllocData* next;
    struct AllocData* prev;
} AllocData;

AllocData allocators_data[__hash_size] = { 0 }; /* All allocators data */

static unsigned hash ( void* address ) { /* MurmurHash3 */
    unsigned hash_value = (unsigned) address;
    hash_value = (hash_value ^ hash_value >> 30) * 0xbf58476d1ce4e5b9;
    hash_value = (hash_value ^ hash_value >> 27) * 0x94d049bb133111eb;
    hash_value = hash_value ^ hash_value >> 31;
    return hash_value;
}

Allocator InitAllocator( Allocator* self ) {
    self->allocate = &static_allocate;
    self->free = &static_free;
    unsigned const hash_value = hash(self);

    AllocData alloc_data = allocators_data[hash_value];

    if ( alloc_data.buffer ) {
        unsigned char recycle_alloc_data = 0;
        AllocData* current = &alloc_data;

        while ( current->next ) {
            if ( current && !current->instance_address ) {
                recycle_alloc_data = 1;
                break;
            }
            current = current->next;
        }

        if ( !recycle_alloc_data ) {
            current->next = malloc(sizeof(AllocData));
            current->next->prev = current;
            current = current->next;
        }

        alloc_data = *current;
    }

    alloc_data.instance_address = (void *) self;
    alloc_data.buffer = malloc( __arena_init_size * sizeof(unsigned char) );
    alloc_data.pos = 0;
    alloc_data.size = __arena_init_size;

    return *self;
}

static void* static_allocate ( Allocator* self, const unsigned size ) {
    unsigned const hash_value = hash(self);
    AllocData* alloc_data = &allocators_data[hash_value];

    while ( alloc_data->next->instance_address != (void *) self ) alloc_data = alloc_data->next;

    if ( alloc_data->pos + size >= alloc_data->size - 1 )
        alloc_data->buffer = reallocate_buffer(alloc_data->buffer, &alloc_data->size);

    const unsigned char* buffer = alloc_data->buffer;
    void* result = (void *)buffer[alloc_data->pos];
    alloc_data->pos += size;

    return result;
}

static void static_free ( Allocator* self ) {
    unsigned const hash_value = hash(self);
    AllocData* alloc_data = &allocators_data[ hash_value ];
    while ( alloc_data->instance_address != (void *) self ) alloc_data = alloc_data->next;

    alloc_data->instance_address = NULL;
    alloc_data->pos = 0;
    for ( unsigned long i = 0; i < alloc_data->size; i++ ) alloc_data->buffer[i] = 0;
    alloc_data->size = 0;

    free( alloc_data->buffer );
}

#else

/* Allocator metadata */
unsigned char* main_buffer = ( unsigned char* ) NULL;
unsigned pos = 0;
unsigned current_size = 0;
static void* static_allocate ( const unsigned size );
static void static_free ( void );

/* Allocator's functions */
Allocator InitAllocator( void ) {
    main_buffer = malloc ( __arena_init_size * sizeof(unsigned char) );
    current_size = __arena_init_size;
    return (Allocator){ &static_allocate, &static_free };
}

static void* static_allocate ( const unsigned size ) {
    if ( pos + size >= current_size - 1 ) main_buffer = reallocate_buffer(main_buffer, &current_size);
    void* result = (void *) main_buffer[pos];
    pos += size;
    return result;
}

static void static_free ( void ) {
    for ( unsigned long i = 0; i < current_size; i++ ) main_buffer[i] = 0;
    free( main_buffer );
    current_size = 0;
    pos = 0;
    main_buffer = NULL;
}

#endif