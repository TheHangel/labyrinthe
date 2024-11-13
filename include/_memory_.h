#ifndef MEMORY_H
#define MEMORY_H

/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by Thibaud Lebrasseur. No portion of this 
 * document may be reproduced, copied, or revised without written 
 * permission of the authors.
 */

/**
 * @file _memory_.h
 * @brief Function about memory allocation.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 */

/**
 * @brief This function frees the memory allocated for a pointer and sets it to NULL.
 * To avoid double free errors.
 * 
 * @param ptr Pointer to the memory to free.
 */
void free_and_reset(void **ptr);

#endif
