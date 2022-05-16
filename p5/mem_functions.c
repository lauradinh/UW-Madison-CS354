#include "mem.h"
extern BLOCK_HEADER* first_header;

// helper functions

// checks if block is free
// returns 1 if block is free, else returns 0
int Is_Free(BLOCK_HEADER* current) {
    int alloc_bit = current->size_alloc;
    if (alloc_bit % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}   

// sets alloc bit to 0 (free)
void Set_Free(BLOCK_HEADER* current) {
    if (current->size_alloc % 2 == 1) {
        current->size_alloc = current->size_alloc - 1;
    }
}

// sets alloc bit to 1 (allocated)
void Set_Allocated(BLOCK_HEADER* current) {
    if (current->size_alloc % 2 == 0) {
        current->size_alloc = current->size_alloc + 1;
    }
}

// returns the user pointer that is in the block
void* Get_User_Pointer(BLOCK_HEADER* current) {
    return (void *) ((unsigned long) current + 8);
}

// returns the next header
BLOCK_HEADER* Get_Next_Header(BLOCK_HEADER* current) {
    int block_size = current->size_alloc & 0xFFFFFFFE;
    return (BLOCK_HEADER *) ((unsigned long) current + block_size);
}

// returns padding of block
int Get_Padding(int size) {
    if ((size + 8) % 16 != 0) {
        return 16 - ((8+size) % 16);
    }
    return 0;
}

// return a pointer to the payload (header + 8 bytes)
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size) {
    // find a free block that's big enough
    BLOCK_HEADER* alloc = NULL;
    BLOCK_HEADER* current = first_header;
    int padding = Get_Padding(size); 
    while(current->size_alloc != 1) {
        if(Is_Free(current)) {
            if(current->payload >= (size + padding)) { 
                alloc = current;
                break;
            }
        }
        current = Get_Next_Header(current);
    }

    // return NULL if we didn't find a block
     if (alloc == NULL)
        return NULL;
    int free_block_size = alloc->size_alloc;
    int block_size = size + padding + 8;
    
    // allocate the block
    alloc->size_alloc = block_size;
    alloc->payload = size;
    
    // changing the allocated bit
    Set_Allocated(alloc);
    
    //split if necessary
    if ((free_block_size - block_size) >= 16) {
        BLOCK_HEADER* next = (BLOCK_HEADER*) ((unsigned long) alloc + block_size);
        next->size_alloc = free_block_size - block_size;
        next->payload = (next->size_alloc) - 8;
    }
    return Get_User_Pointer(alloc);
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    // shouldn't work with any ptrs
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    BLOCK_HEADER* current = first_header;
    BLOCK_HEADER* free = NULL; 
    while(current->size_alloc != 1) {
        if ( Get_User_Pointer(current) == ptr) {
            free = current;
            break;
        }
        current = Get_Next_Header(current);
    }

    if (free == NULL) 
        return -1;
    // free the block 
        // set size alloc bit to 0
        // getPadding to add to allocate
    Set_Free(free);
    free->payload += Get_Padding(free->payload);
    
    // coalesce adjacent free blocks
    current = first_header;
    BLOCK_HEADER * next = Get_Next_Header(current);

    while(next->size_alloc != 1) {
        if (Is_Free(current) && Is_Free(next)) {
            BLOCK_HEADER * second_next = Get_Next_Header(next);
            current->size_alloc = (unsigned long) second_next - (unsigned long) current;
            current->payload = current->size_alloc-8;
            break;
        } else {
            current = Get_Next_Header(current);
            next = Get_Next_Header(next);
        }
    }
 
    current = first_header;
    next = Get_Next_Header(current);
    while(next->size_alloc != 1) {
        if (Is_Free(current) && Is_Free(next)) {
            BLOCK_HEADER * second_next = Get_Next_Header(next);
            current->size_alloc = (unsigned long) second_next - (unsigned long) current;
            current->payload = current->size_alloc-8;
            break;
         } else {
            current = Get_Next_Header(current); 
            next = Get_Next_Header(next);
         }
    } 

    return 0;
}
    
