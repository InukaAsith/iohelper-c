/*
 * Copyright (C) 2025  Inuka Asith (github.com/InukaAsith)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "iohelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// mem list memory tracking (private)
typedef struct mem_node 
{
    void *ptr;
    struct mem_node *next;
} mem_node;

static mem_node *mem_list = NULL;

// Adds a pointer to the mem list
static void track_allocation(void *ptr) 
{
    if (ptr == NULL) return;
    mem_node *node = malloc(sizeof(mem_node));
    if (node == NULL) return;
    node->ptr = ptr;
    node->next = mem_list;
    mem_list = node;
}

// change the pointer in the mem list 
static void update_allocation(void *old_ptr, void *new_ptr) 
{
    mem_node *current = mem_list;
    while (current) 
    {
        if (current->ptr == old_ptr) 
        {
            current->ptr = new_ptr;
            return;
        }
        current = current->next;
    }
}

// remove pointer from mem list 
static void remove_allocation(void *ptr) 
{
    mem_node **current = &mem_list;
    while (*current) 
    {
        if ((*current)->ptr == ptr) 
        {
            mem_node *to_delete = *current;
            *current = to_delete->next;
            free(to_delete);
            return;
        }
        current = &((*current)->next);
    }
    // mem_node *current = mem_list;
    // mem_node *prev = NULL;
    // while (current) 
    //     {
    //     if (current->ptr == ptr) 
    //      {
    //         if (prev) 
    //         {
    //             prev->next = current->next;
    //         } else 
    //         {
    //             mem_list = current->next;
    //         }
    //         free(current);
    //         return;
    //     }
    //     prev = current;
    //     current = current->next;
    // }
}

// on exit 
static void cleanup_memory(void) 
{
    mem_node *current = mem_list;
    while (current) 
    {
        mem_node *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    mem_list = NULL;
}

// Automatically register cleanup at program exit
static void __attribute__((constructor)) init_memory_tracking(void) 
{
    atexit(cleanup_memory);
}

// free string function to manually free string memory
void free_string(char *str)
{
    mem_node *current = mem_list;
    while (current)
    {
        if (current -> ptr == str)
        {
            remove_allocation(str);
            free(str);
            return;
        }
        current = current -> next;
    }
}

// get string function
char *get_string(char *output, ...) 
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);

    size_t size = 128;
    size_t length = 0;
    char *buffer = malloc(size + 1);
    if (buffer == NULL) return NULL;
    track_allocation(buffer);

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') 
    {
        buffer[length++] = (char)c;
        if (length >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size + 1);
            if (new_buffer == NULL) return NULL;
            update_allocation(buffer, new_buffer);
            buffer = new_buffer;
        }
    }

    if (length == 0) 
    {
        // Remove the pointer from tracking list before freeing it manually
        remove_allocation(buffer);
        free(buffer);
        return get_string(output);
    }

    buffer[length] = '\0';
    char *final_buffer = realloc(buffer, length + 1);
    update_allocation(buffer, final_buffer);
    return final_buffer;
}



// get_int, get_float, get_double, get_long functions

int get_int(char *output, ...)
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);
    int out;
    if (scanf("%i", &out) != 1) {
        while (getchar() != '\n'); 
        return get_int(output); 
    }
    while (getchar() != '\n'); 
    return out;
}

float get_float(char *output, ...)
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);
    float out;
    scanf("%f",&out);
    while (getchar() != '\n');
    return out;
}
long get_long(char *output, ...)
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);
    long out;
    scanf("%ld",&out);
    while (getchar() != '\n');
    return out;
}
double get_double(char *output, ...)
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);
    double out;
    scanf("%lf",&out);
    while (getchar() != '\n');
    return out;
}
char get_char(char *output, ...)
{
    va_list args;
    va_start(args, output);
    vprintf(output, args);
    va_end(args);
    char out;
    scanf("%c",&out);
    while (getchar() != '\n');
    return out;
}