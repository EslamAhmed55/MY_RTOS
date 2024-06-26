/*
 * CortexM_OS_Porting.c
 *
 *  Created on: Apr 4, 2024
 *      Author: eslam
 */

#include "MYRTOS_FIFO.h"

Buffer_status FIFO_init (FIFO_Buf_t* fifo, element_type* buff , unsigned int length)
{
	if(!buff)
		return FIFO_NULL;

	fifo->base = buff;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length = length;
	fifo->counter = 0;

	return FIFO_NO_ERROR;
}

Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo, element_type item)
{
	// FIFO null
	if ( !fifo->base || !fifo->length )
		return FIFO_NULL;

	// FIFO full
	if ((fifo->head == fifo->length) && (fifo->counter == fifo->length))
		return FIFO_FULL;

	*(fifo->tail) = item;
	fifo->counter++;

	// for circular fifo enqueue
	if (fifo->tail == (((unsigned int)fifo->base + (4*fifo->length)) -4 ))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_NO_ERROR;
}


Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo, element_type* item)
{
	// FIFO null
	if ( !fifo->base || !fifo->length )
		return FIFO_NULL;

	// FIFO empty
	if ( fifo->head == fifo->tail )
		return FIFO_EMPTY;

	*item = *(fifo->head);
	fifo->counter--;


	// for circular fifo dequeue
	if (fifo->head == (((unsigned int)fifo->base + (4*fifo->length)) -4 ))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_NO_ERROR;
}


Buffer_status FIFO_is_full (FIFO_Buf_t* fifo)
{
	if( !fifo->head || !fifo->base || !fifo->tail )
		return FIFO_NULL;
	if (fifo->counter == fifo->length)
		return FIFO_FULL;

	return FIFO_NO_ERROR;
}




void FIFO_print (FIFO_Buf_t* fifo)
{
	/*element_type* temp
	 int i;
	 if(fifo->counter == 0)
	 	 printf("fifo is empty");
	 else
	 {
	 temp = fifo->tail;
	 printf("\n ==== fifo print ==== \n");
	 for(i=0; i<fifo->length ; i++)
	 {
	 printf("\t %x	\n",*temp");
	 temp++;
	 }

	 }

	 */
}
