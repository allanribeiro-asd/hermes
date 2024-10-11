#include "buffer.h"

buffer_t * buffer_init(uint16_t size)
{
	buffer_t *buffer = (buffer_t *)malloc(sizeof(buffer_t));

	buffer->ptr = (uint8_t *)malloc(size*sizeof(uint8_t));
	if(buffer->ptr == NULL)
	{
		free(buffer);
		return NULL;
	}

	buffer->size = size;
	buffer->start = buffer->end = 0;
	return buffer;
}

uint8_t buffer_isEmpty(buffer_t * buffer)
{
	if(buffer == NULL) return 0;

	return (buffer->start == buffer->end);
}

/** Check if given buffer is full
 *
 * Returns true if all bytes from buffer are writted
 */

uint8_t buffer_isFull(buffer_t * buffer)
{
	if(buffer == NULL) return 0;

	if(buffer->end < buffer->start)
	{
		return ((buffer->start - 1) == buffer->end);
	}
	else
	{
		return (buffer->start == 0 && (buffer->end == (buffer->size-1)));
	}
}

/** Write from pointer to buffer
 *
 * If the buffer lacks space, returns immediatly.
 *
 * returns the number of written bytes to buffer.
 */

uint16_t buffer_write(buffer_t * buffer, uint8_t *ptr, uint16_t bytes)
{
	if(buffer == NULL || ptr == NULL)
	{
		return 0;
	}

	uint16_t counter = 0;
	while(!buffer_isFull(buffer))
	{
		if(counter == bytes)
		{
			break;
		}
		buffer->ptr[buffer->end++] = ptr[counter++];
		if(buffer->end == buffer->size)
		{
			buffer->end = 0;
		}
	}
	return counter;
}

/** Read from buffer to pointer
 *
 * The function expects *ptr to have enough size.
 *
 * returns the number of read bytes from buffer
 */

uint16_t buffer_read(buffer_t * buffer, uint8_t *ptr, uint16_t bytes)
{
	if(buffer == NULL || ptr == NULL)
	{
		return 0;
	}

	int counter = 0;
	while(!buffer_isEmpty(buffer))
	{
		if(counter == bytes)
		{
			break;
		}
		ptr[counter++] = buffer->ptr[buffer->start++];
		if(buffer->start == buffer->size)
		{
			buffer->start = 0;
		}
		
	}
	return counter;
}


int main(void)
{
	
}
