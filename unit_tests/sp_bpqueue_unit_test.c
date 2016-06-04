/*
 * sp_bpqueue_unit_test.c
 *
 *  Created on: 23 במאי 2016
 *      Author: Maayan Sivroni
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "unit_test_util.h" //SUPPORTING MACROS ASSERT_TRUE/ASSERT_FALSE etc..
#include "../SPBPriorityQueue.h" /* inside there are includes to SPList and SPListElement */
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/*added these 3 lines so NULL will be defined*/
#ifndef NULL
#define NULL   ((void *) 0)
#endif

/* create + add 6 elements + destroy */

static bool simpleEnqueue(){
	SPBPQueue q = spBPQueueCreate(10);
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(1,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);

	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);



	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	return true;
}



/* create + insert 6 elements:
 * sort by minimal index if values are identical (indexes 7,6)
 * + check min val + max val +
 * destroy */
static bool testEnqueue1(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6 */
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {1,3,5,6,7,10} */

	ASSERT_TRUE(spBPQueueMinValue(q) == 1.0);
	ASSERT_TRUE(spBPQueueMaxValue(q) == 4.0);

	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);

	return true;

}

/* create + insert 6 elements:
 * sort by minimal index if values are identical (indexes 7,6)
 * + try to insert extra element (value too high -> full queue)
 * + try to insert extra element (value small enough -> index 10 out, index 2 in)
 * + destroy */
static bool testEnqueueWhenFull(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6 */
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {1,3,5,6,7,10} */

	SPListElement a7 = spListElementCreate(12,10.0);
	ASSERT_TRUE(spBPQueueEnqueue(q,a7) == SP_BPQUEUE_FULL); /* do not insert to q */

	SPListElement a8 = spListElementCreate(2,1.0);
	ASSERT_TRUE(spBPQueueEnqueue(q,a8) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is {1,2,3,5,6,7} */



	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(a7);
	spListElementDestroy(a8);
	return true;

}

/* create + insert 6 elements by the following order:
 * index 2 and value 5.0 (x3)
 * index 1 and value 5.0 (x3)
 * queue is: { 1,1,1,2,2,2 }
 * + check min/max
 * + destroy
 * */
static bool testEnqueue3(){
	SPBPQueue q = spBPQueueCreate(7); /*maxSize =7 */
	SPListElement a1 = spListElementCreate(3,5.0);
	SPListElement a2 = spListElementCreate(3,5.0);
	SPListElement a3 = spListElementCreate(3,5.0);
	SPListElement a4 = spListElementCreate(1,5.0);
	SPListElement a5 = spListElementCreate(1,5.0);
	SPListElement a6 = spListElementCreate(1,5.0);
	SPListElement a7 = spListElementCreate(2,5.0);
	SPListElement a8 = spListElementCreate(2,5.0);
	SPListElement a9 = spListElementCreate(2,5.0);


	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a7) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a8) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a9) == SP_BPQUEUE_SUCCESS);


	ASSERT_TRUE(spBPQueueMinValue(q) == 5.0);
	ASSERT_TRUE(spBPQueueMaxValue(q) == 5.0);




	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(a7);
	spListElementDestroy(a8);
	spListElementDestroy(a9);

	return true;

}
/* create + insert 5 elements:
 * insert a8-  sort by minimal index if values are identical (indexes 2,1)
 * sizes check - queueSize, getMax, isFull, isEmpty
 * + destroy */
static bool testEnqueueSizes(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6 */
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);

	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);

	/* list by indexes is: {1,3,5,6,7,10} */

	SPListElement a8 = spListElementCreate(2,1.0);
	ASSERT_TRUE(spBPQueueEnqueue(q,a8) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is {1,2,3,5,6,7} */


	/* Sizes check */
	ASSERT_TRUE(spBPQueueSize(q) == 6 ); /*make sure there are 6 elements */
	ASSERT_TRUE(spBPQueueGetMaxSize(q) == 6); /*check maxSize */
	ASSERT_TRUE(spBPQueueIsFull(q)); /* check if full */
	ASSERT_FALSE(spBPQueueIsEmpty(q)); /* make sure q not empty */


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a8);
	return true;

}

/* create + insert 6 elements:
 * + insert a1, assert peek (first element) and peekLast
 * (in the first case - also first element)
 * + insert 5 other elements - also assert peek and peekLast
 * + destroy */
static bool testEnqueuePeek(){
	SPBPQueue q = spBPQueueCreate(8); /*maxSize = 8*/
	SPListElement a1 = spListElementCreate(10,5.0);
	SPListElement a2 = spListElementCreate(8,7.0);
	SPListElement a3 = spListElementCreate(6,9.0);
	SPListElement a4 = spListElementCreate(4,1.5);
	SPListElement a5 = spListElementCreate(2,2.0);
	SPListElement a6 = spListElementCreate(1,1.0);

	 /*insert and check first element - both head and tail*/
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	SPListElement b1 = spBPQueuePeek(q);
	SPListElement b2 = spBPQueuePeekLast(q);

	ASSERT_TRUE(spListElementGetIndex(b1) == 10);
	ASSERT_TRUE(spListElementGetValue(b1) == 5.0);
	ASSERT_TRUE(spListElementGetIndex(b2) == 10);
	ASSERT_TRUE(spListElementGetValue(b2) == 5.0);

	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	/* list by indexes: {1,4,2,10,8,6}*/

	SPListElement b3 = spBPQueuePeek(q);
	SPListElement b4 = spBPQueuePeekLast(q);
	ASSERT_TRUE(spListElementGetIndex(b3) == 1);
	ASSERT_TRUE(spListElementGetValue(b3) == 1.0);
	ASSERT_TRUE(spListElementGetIndex(b4) == 6);
	ASSERT_TRUE(spListElementGetValue(b4) == 9.0);


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(b1);
	spListElementDestroy(b2);
	spListElementDestroy(b3);
	spListElementDestroy(b4);
	return true;

}

/* create + insert 6 elements:
 * clear queue + check size, min val, max val, maxSize, isEmpty
 * + destroy */
static bool testEnqueueClear(){
	SPBPQueue q = spBPQueueCreate(8); /*maxSize = 8 */
	SPListElement a1 = spListElementCreate(10,5.0);
	SPListElement a2 = spListElementCreate(8,7.0);
	SPListElement a3 = spListElementCreate(6,9.0);
	SPListElement a4 = spListElementCreate(4,1.5);
	SPListElement a5 = spListElementCreate(2,2.0);
	SPListElement a6 = spListElementCreate(1,1.0);

	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	/* list by indexes: {1,4,2,10,8,6} */

	spBPQueueClear(q);



	ASSERT_TRUE(spBPQueueSize(q) == 0);
	ASSERT_TRUE(spBPQueueMinValue(q) == -1.0);
	ASSERT_TRUE(spBPQueueMaxValue(q) == -1.0);
	ASSERT_TRUE(spBPQueueGetMaxSize(q) == 8); /*max is still the same*/
	ASSERT_TRUE(spBPQueueIsEmpty(q));



	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	return true;

}

/* create + insert 6 elements:
 * copy queue + check last and first element by peek
 * + destroy */
static bool testEnqueueCopy(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6*/
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {1,3,5,6,7,10}*/
	 /*copy q to q2 and make sure that first and last element are identical*/
	SPBPQueue q2 = spBPQueueCopy(q);

	SPListElement b1 = spBPQueuePeek(q2);
	SPListElement b2 = spBPQueuePeekLast(q2);
	ASSERT_TRUE(spListElementGetIndex(b1) == 1);
	ASSERT_TRUE(spListElementGetValue(b1) == 1.0);
	ASSERT_TRUE(spListElementGetIndex(b2) == 10);
	ASSERT_TRUE(spListElementGetValue(b2) == 4.0);
	ASSERT_TRUE(spBPQueueSize(q)==spBPQueueSize(q2));
	ASSERT_TRUE(spBPQueueGetMaxSize(q)==spBPQueueGetMaxSize(q2));



	spBPQueueDestroy(q2);
	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(b1);
	spListElementDestroy(b2);
	return true;

}

/* create + insert 6 elements:
 * remove first element and check first+last element by peek +
 * check size and maxSize
 * + destroy */
static bool testEnqueueDequeue1(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6*/
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {1,3,5,6,7,10}*/
	/* dequeue first element, check that the first element is changed ,
	 * sizes, and check that the last element is the same.*/

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);

	SPListElement b1 = spBPQueuePeek(q);
	SPListElement b2 = spBPQueuePeekLast(q);

	ASSERT_TRUE(spListElementGetIndex(b1) == 3);
	ASSERT_TRUE(spListElementGetValue(b1) == 2.0);
	ASSERT_TRUE(spBPQueueSize(q) == 5);
	ASSERT_TRUE(spBPQueueGetMaxSize(q) == 6);
	ASSERT_TRUE(spListElementGetIndex(b2) == 10);
	ASSERT_TRUE(spListElementGetValue(b2) == 4.0);


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(b1);
	spListElementDestroy(b2);
	return true;

}

/* create + insert 6 elements:
 * all elements, after each removal check peek and peekLast
 * + destroy */
static bool testEnqueueDequeue2(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6*/
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {1,3,5,6,7,10}*/
	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {3,5,6,7,10}*/
	SPListElement b1 = spBPQueuePeek(q);
	SPListElement b2 = spBPQueuePeekLast(q);


	ASSERT_TRUE(spListElementGetIndex(b1)  == 3);
	ASSERT_TRUE(spListElementGetValue(b1) == 2.0);
	ASSERT_TRUE(spListElementGetIndex(b2)  == 10);
	ASSERT_TRUE(spListElementGetValue(b2) == 4.0);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {5,6,7,10}*/
	SPListElement b3 = spBPQueuePeek(q);
	SPListElement b4 = spBPQueuePeekLast(q);
	ASSERT_TRUE(spListElementGetIndex(b3) == 5);
	ASSERT_TRUE(spListElementGetValue(b3)  == 3.0);
	ASSERT_TRUE(spListElementGetIndex(b4) == 10);
	ASSERT_TRUE(spListElementGetValue(b4) == 4.0);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {6,7,10}*/
	SPListElement b5 = spBPQueuePeek(q);
	SPListElement b6 = spBPQueuePeekLast(q);
	ASSERT_TRUE(spListElementGetIndex(b5) == 6);
	ASSERT_TRUE(spListElementGetValue(b5) == 3.5);
	ASSERT_TRUE(spListElementGetIndex(b6) == 10);
	ASSERT_TRUE(spListElementGetValue(b6) == 4.0);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {7,10}*/
	SPListElement b7 = spBPQueuePeek(q);
	SPListElement b8 = spBPQueuePeekLast(q);
	ASSERT_TRUE(spListElementGetIndex(b7) == 7);
	ASSERT_TRUE(spListElementGetValue(b7) == 3.5);
	ASSERT_TRUE(spListElementGetIndex(b8) == 10);
	ASSERT_TRUE(spListElementGetValue(b8) == 4.0);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	 /*list by indexes is: {10}*/
	SPListElement b9 = spBPQueuePeek(q);
	SPListElement b10 = spBPQueuePeekLast(q);
	ASSERT_TRUE(spListElementGetIndex(b9) == 10);
	ASSERT_TRUE(spListElementGetValue(b9)== 4.0);
	ASSERT_TRUE(spListElementGetIndex(b10) == 10);
	ASSERT_TRUE(spListElementGetValue(b10)== 4.0);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {} - EMPTY*/
	ASSERT_TRUE(spBPQueuePeek(q) == NULL);
	ASSERT_TRUE(spBPQueuePeekLast(q) == NULL);


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(b1);
	spListElementDestroy(b2);
	spListElementDestroy(b3);
	spListElementDestroy(b4);
	spListElementDestroy(b5);
	spListElementDestroy(b6);
	spListElementDestroy(b7);
	spListElementDestroy(b8);
	spListElementDestroy(b9);
	spListElementDestroy(b10);
	return true;

}

/* checks all unvalid arguments in all functions (but enqueue, dequeue)
 * by creating NULL queue - maxSize = (-1)*/
static bool unvalidArguments(){
	ASSERT_TRUE(spBPQueueCreate(-1) == NULL);
	ASSERT_TRUE(spBPQueueCopy(spBPQueueCreate(-1)) == NULL);
	//ASSERT_TRUE(spBPQueueDestroy(spBPQueueCreate(-1)) == NULL);
	//ASSERT_TRUE(spBPQueueClear(spBPQueueCreate(-1)) == NULL);
	ASSERT_TRUE(spBPQueueSize(spBPQueueCreate(-1)) == -1);
	ASSERT_TRUE(spBPQueueGetMaxSize(spBPQueueCreate(-1)) == -1);
	ASSERT_TRUE(spBPQueuePeek(spBPQueueCreate(-1)) == NULL);
	ASSERT_TRUE(spBPQueuePeekLast(spBPQueueCreate(-1)) == NULL);
	ASSERT_TRUE(spBPQueueMinValue(spBPQueueCreate(-1)) == -1.0);
	ASSERT_TRUE(spBPQueueMaxValue(spBPQueueCreate(-1)) == -1.0);


	return true;
}

/* check all types of messages:
 * (but SP_BPQUEUE_OUT_OF_MEMORY - how to create allocation error?)
 * 	SP_BPQUEUE_FULL,
	SP_BPQUEUE_EMPTY,
	SP_BPQUEUE_INVALID_ARGUMENT,
	SP_BPQUEUE_SUCCESS
 */
static bool testQueueMsg(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6 */
	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_EMPTY);
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(3,2.0);
	SPListElement a3 = spListElementCreate(5,3.0);
	SPListElement a4 = spListElementCreate(7,3.5);
	SPListElement a5 = spListElementCreate(10,4.0);
	SPListElement a6 = spListElementCreate(6,3.5);
	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a5) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,NULL) == SP_BPQUEUE_INVALID_ARGUMENT);
	ASSERT_TRUE(spBPQueueEnqueue(q,a6) == SP_BPQUEUE_SUCCESS);
	/* list by indexes is: {1,3,5,6,7,10} */

	SPListElement a7 = spListElementCreate(12,4.0);
	ASSERT_TRUE(spBPQueueEnqueue(q,a7) == SP_BPQUEUE_FULL); /* index not low enough */
	SPListElement a8 = spListElementCreate(8,4.0);
	ASSERT_TRUE(spBPQueueEnqueue(q,a8) == SP_BPQUEUE_SUCCESS); /* index low enough */


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	spListElementDestroy(a5);
	spListElementDestroy(a6);
	spListElementDestroy(a7);
	spListElementDestroy(a8);
	return true;
}
/*try to insert elements with the same value but different index
 * to make sure we insert by increasing index
 * after all inserts are done we excpect the Q to be (1,4,6,7) */
static bool IdenticalValuesTest(){
	SPBPQueue q = spBPQueueCreate(6); /*maxSize =6 */
	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_EMPTY);
	SPListElement a1 = spListElementCreate(1,1.0);
	SPListElement a2 = spListElementCreate(4,1.0);
	SPListElement a3 = spListElementCreate(6,1.0);
	SPListElement a4 = spListElementCreate(5,1.0);

	ASSERT_TRUE(spBPQueueEnqueue(q,a1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a3) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q,a4) == SP_BPQUEUE_SUCCESS);


	spBPQueueDestroy(q);
	spListElementDestroy(a1);
	spListElementDestroy(a2);
	spListElementDestroy(a3);
	spListElementDestroy(a4);
	return true;
}

int main() {
	RUN_TEST(simpleEnqueue);
	RUN_TEST(testEnqueue1);
	RUN_TEST(testEnqueueWhenFull);
	RUN_TEST(testEnqueue3);
	RUN_TEST(testEnqueueSizes);
	RUN_TEST(testEnqueuePeek);
	RUN_TEST(testEnqueueClear);
	RUN_TEST(testEnqueueCopy);
	RUN_TEST(testEnqueueDequeue1);
	RUN_TEST(testEnqueueDequeue2);
	RUN_TEST(unvalidArguments);
	RUN_TEST(testQueueMsg);
	RUN_TEST(IdenticalValuesTest);

	printf("-----Done!-----");

	return 0;
}

