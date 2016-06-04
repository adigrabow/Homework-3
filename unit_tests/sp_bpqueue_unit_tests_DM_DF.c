#include "unit_test_util.h"
#include "../SPBPriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/*added these 3 lines so NULL will be defined*/
#ifndef NULL
#define NULL   ((void *) 0)
#endif


/* 
		
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		BE AWARE - YOU SHOULD NOT SUBMIT THIS FILE
		PART OF THE ASSIGMENT IS TO WRITE YOUR OWN TESTS

		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/ 


/**
 * - Create queue with max_size = 1;
 * - Check that the return val is not NULL
 * - Destroy Queue
 */
static bool spBPQueueCreateBasic_Test()
{
	SPBPQueue q = spBPQueueCreate(1);
	ASSERT_TRUE(q != NULL);

	spBPQueueDestroy(q);
	return true;
}

/**
 * - Create queue with max_size = 0;
 * - Check that the return val is NULL
 * - Create queue with max_size = -3;
 * - Check that the return val is NULL
 */
static bool spBPQueueCreateZero_Test()
{
	SPBPQueue q = spBPQueueCreate(0);
	ASSERT_TRUE(q == NULL);

	q = spBPQueueCreate(-3);
	ASSERT_TRUE(q == NULL);

	return true;
}

/**
 * - Create queue with max_size = 4;
 * - Check that size==0 && max_size == 4
 * - Destroy Queue
 */
static bool spBPQueueCheckSizes_Test()
{
	SPBPQueue q = spBPQueueCreate(4);
	ASSERT_TRUE(4 == spBPQueueGetMaxSize(q));
	ASSERT_TRUE(0 == spBPQueueSize(q));

	spBPQueueDestroy(q);
	return true;
}

/**
 * - Create queue with max_size = 4;
 * - newQueue = spBPQueueCopy(queue)
 * - Check newQueue: size==0 && max_size == 4
 * - Destroy Queue
 * - Destroy newQueue
 */
static bool spBPQueueCopyBasic_Test()
{
	SPBPQueue q = spBPQueueCreate(4);
	SPBPQueue newQueue = spBPQueueCopy(q);

	ASSERT_TRUE(4 == spBPQueueGetMaxSize(newQueue));
	ASSERT_TRUE(0 == spBPQueueSize(newQueue));

	spBPQueueDestroy(newQueue);
	spBPQueueDestroy(q);
	return true;
}

/**
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Check Queue: size == 1 && max_size == 4
 * - newQueue = spBPQueueCopy(queue)
 * - Check newQueue: size == 1 && max_size == 4
 * - Dequeue(queue)
 * - newQueuePeek(newQueue) == (5.0, 1)
 * - Destroy Queue
 * - newQueue Queue
 */
static bool spBPQueueCopyCheckCopiedElements_Test()
{
	SPBPQueue q = spBPQueueCreate(4);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e2 = NULL;
	SPBPQueue newQueue = NULL;

	spBPQueueEnqueue(q, e);
	ASSERT_TRUE(4 == spBPQueueGetMaxSize(q));
	ASSERT_TRUE(1 == spBPQueueSize(q));

	newQueue = spBPQueueCopy(q);
	ASSERT_TRUE(4 == spBPQueueGetMaxSize(newQueue));
	ASSERT_TRUE(1 == spBPQueueSize(newQueue));

	spBPQueueDequeue(q);

	e2 = spBPQueuePeek(newQueue);
	ASSERT_TRUE( 1 == spListElementGetIndex(e2));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e2));
	spListElementDestroy(e2);

	spListElementDestroy(e);
	spBPQueueDestroy(newQueue);
	spBPQueueDestroy(q);
	return true;
}

/**
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - newQueue = spBPQueueCopy(queue)
 * - Destroy Queue
 * - Check newQueue: size == 1 && max_size == 4
 * - newQueuePeek(newQueue) == (5.0, 1)
 * - Destroy newQueue
 */
static bool spBPQueueCopyCheckDestroy_Test()
{
	SPBPQueue q = spBPQueueCreate(4);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e2 = NULL;
	SPBPQueue newQueue = NULL;

	spBPQueueEnqueue(q, e);

	newQueue = spBPQueueCopy(q);

	spBPQueueDestroy(q);

	ASSERT_TRUE(4 == spBPQueueGetMaxSize(newQueue));
	ASSERT_TRUE(1 == spBPQueueSize(newQueue));

	e2 = spBPQueuePeek(newQueue);
	ASSERT_TRUE( 1 == spListElementGetIndex(e2));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e2));
	spListElementDestroy(e2);


	spBPQueueDestroy(newQueue);
	spListElementDestroy(e);
	return true;
}

/**
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - newQueue = spBPQueueCopy(queue)
 * - Clear Queue
 * - Check newQueue: size == 1 && max_size == 4
 * - newQueuePeek(newQueue) == (5.0, 1)
 * - Destroy newQueue
 */
static bool spBPQueueCopyCheckClear_Test()
{
	SPBPQueue q = spBPQueueCreate(4);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e2 = NULL;
	SPBPQueue newQueue = NULL;

	spBPQueueEnqueue(q, e);

	newQueue = spBPQueueCopy(q);

	spBPQueueClear(q);
	ASSERT_TRUE(0 == spBPQueueSize(q));

	ASSERT_TRUE(4 == spBPQueueGetMaxSize(newQueue));
	ASSERT_TRUE(1 == spBPQueueSize(newQueue));

	e2 = spBPQueuePeek(newQueue);
	ASSERT_TRUE( 1 == spListElementGetIndex(e2));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e2));
	spListElementDestroy(e2);

	spListElementDestroy(e);
	spBPQueueDestroy(newQueue);
	spBPQueueDestroy(q);
	return true;
}

/**
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (6.0, 2)
 * - Insert Element(Val,Index) = (7.0, 2)
 * - Destroy Queue
 * - Check queue == NULL
 */
static bool spBPQueueDestroyBasic_Test()
{
	SPBPQueue q = spBPQueueCreate(4);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 6.0);
	SPListElement e2 = spListElementCreate(2, 7.0);

	spBPQueueEnqueue(q, e);
	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e2);

	spBPQueueDestroy(q);

	spListElementDestroy(e);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}

/**
 * - Create queue with max_size = 5;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (6.0, 2)
 * - Insert Element(Val,Index) = (7.0, 2)
 * - Clear Queue
 * - Check Queue != NULL
 * - Check Queue: size == 0 && max_size == 5
 * - Destroy Queue
 */
static bool spBPQueueClear_Test()
{
	SPBPQueue q = spBPQueueCreate(5);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 6.0);
	SPListElement e2 = spListElementCreate(2, 7.0);

	spBPQueueEnqueue(q, e);
	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e2);

	spBPQueueClear(q);
	ASSERT_TRUE(NULL != q);

	ASSERT_TRUE(5 == spBPQueueGetMaxSize(q));
	ASSERT_TRUE(0 == spBPQueueSize(q));

	spBPQueueDestroy(q);
	spListElementDestroy(e);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}

/*
 * - Create queue with max_size = 5;
 * - Check Queue: size == 0
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Check Queue: size == 1
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Check Queue: size == 2
 * - Insert Element(Val,Index) = (3.0, 2)
 * - Check Queue: size == 3
 * - Destroy Queue
 */
static bool spBPQueueSize_Test()
{
	SPBPQueue q = spBPQueueCreate(5);

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	SPListElement e3 = spListElementCreate(2, 3.0);

	ASSERT_TRUE(0 == spBPQueueSize(q));

	spBPQueueEnqueue(q, e);
	ASSERT_TRUE(1 == spBPQueueSize(q));

	spBPQueueEnqueue(q, e1);
	ASSERT_TRUE(2 == spBPQueueSize(q));

	spBPQueueEnqueue(q, e3);
	ASSERT_TRUE(3 == spBPQueueSize(q));

	spListElementDestroy(e);
	spListElementDestroy(e1);
	spListElementDestroy(e3);
	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 1;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Check Queue: max_size == 1
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Check Queue: max_size == 1
 * - Dequeue
 * - Check Queue: max_size == 1
 * - Destroy Queue
 */
static bool spBPQueueGetMaxSize_Test()
{
	SPBPQueue q = spBPQueueCreate(1);
	ASSERT_TRUE(1 == spBPQueueGetMaxSize(q));

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);

	spBPQueueEnqueue(q, e);
	ASSERT_TRUE(1 == spBPQueueGetMaxSize(q));

	spBPQueueEnqueue(q, e1);
	ASSERT_TRUE(1 == spBPQueueGetMaxSize(q));

	spBPQueueDequeue(q);
	ASSERT_TRUE(1 == spBPQueueGetMaxSize(q));

	spListElementDestroy(e);
	spListElementDestroy(e1);
	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 1;
 * - IsFull == false
 * - Insert Element(Val,Index) = (5.0, 1)
 * - IsFull == true
 * - Insert Element(Val,Index) = (4.0, 2)
 * - IsFull == true
 * - Dequeue
 * - IsFull == false
 * - Dequeue
 * - IsFull == false
 * - Destroy Queue
 */
static bool spBPQueueIsFull_Test()
{
	SPBPQueue q = spBPQueueCreate(1);
	ASSERT_TRUE(false == spBPQueueIsFull(q));

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);

	spBPQueueEnqueue(q, e);
	ASSERT_TRUE(true == spBPQueueIsFull(q));

	spBPQueueEnqueue(q, e1);
	ASSERT_TRUE(true == spBPQueueIsFull(q));

	spBPQueueDequeue(q);
	ASSERT_TRUE(false == spBPQueueIsFull(q));

	spBPQueueDequeue(q);
	ASSERT_TRUE(false == spBPQueueIsFull(q));


	spListElementDestroy(e);
	spListElementDestroy(e1);
	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 1;
 * - IsEmpty == true
 * - Insert Element(Val,Index) = (5.0, 1)
 * - IsEmpty == false
 * - Insert Element(Val,Index) = (4.0, 2)
 * - IsEmpty == false
 * - Dequeue
 * - IsEmpty == true
 * - Insert Element(Val,Index) = (4.0, 2)
 * - IsEmpty == false
 * - Destroy Queue
 */
static bool spBPQueueIsEmpty_Test()
{
	SPBPQueue q = spBPQueueCreate(1);
	ASSERT_TRUE(true == spBPQueueIsEmpty(q));

	SPListElement e = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	SPListElement e3 = spListElementCreate(2, 4.0);

	spBPQueueEnqueue(q, e);
	ASSERT_TRUE(false == spBPQueueIsEmpty(q));

	spBPQueueEnqueue(q, e1);
	ASSERT_TRUE(false == spBPQueueIsEmpty(q));

	spBPQueueDequeue(q);
	ASSERT_TRUE(true == spBPQueueIsEmpty(q));

	spBPQueueEnqueue(q, e3);
	ASSERT_TRUE(false == spBPQueueIsEmpty(q));

	spListElementDestroy(e);
	spListElementDestroy(e1);
	spListElementDestroy(e3);

	spBPQueueDestroy(q);
	return true;
}


/*
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Dequeue == (4.0, 2)
 * - Dequeue == (5.0, 1)
 * - Dequeue == EmptyMessage
 * - Destroy Queue
 */
static bool spBPQueueEnqueueDequeuePeek_Basic_Test()
{
	SPBPQueue q = spBPQueueCreate(4);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == msg);

	spBPQueueDestroy(q);
	spListElementDestroy(e2);
	spListElementDestroy(e1);

	return true;
}

/*
 * - Create queue with max_size = 2;
 * - Insert Element(Val,Index) = (5.0, 2)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Dequeue == (4.0, 2)
 * - Dequeue == (5.0, 1)
 * - Destroy Queue
 */
static bool spBPQueueEnqueueDequeuePeek_WhenFullRemove_Test()
{
	SPBPQueue q = spBPQueueCreate(2);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(2, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	SPListElement e3 = spListElementCreate(1, 5.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e3);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);


	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);


	spListElementDestroy(e2);
	spListElementDestroy(e1);
	spListElementDestroy(e3);

	spBPQueueDestroy(q);
	return true;
}


static bool spBPQueueEnqueueDequeuePeek_InsertByIndex_Test()
{
	SPBPQueue q = spBPQueueCreate(4);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e1 = spListElementCreate(2, 5.0);
	SPListElement e2 = spListElementCreate(3, 5.0);
	SPListElement e3 = spListElementCreate(2, 6.0);
	SPListElement e4 = spListElementCreate(5, 5.0);
	SPListElement e5 = spListElementCreate(4, 5.0);

	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e3);
	spBPQueueEnqueue(q, e4);
	spBPQueueEnqueue(q, e5);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);


	e = spBPQueuePeek(q);
	ASSERT_TRUE( 3 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 4 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 5 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);
	
	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == msg);
	
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	spListElementDestroy(e4);
	spListElementDestroy(e5);

	spBPQueueDestroy(q);
	return true;
}


/*
 * - Create queue with max_size = 2;
 * - Insert Element(Val,Index) = (5.0, 2)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Insert Element(Val,Index) = (5.0, 3)
 * 		should return SP_BPQUEUE_FULL (the element was not added since the queue is full)
 * - Dequeue == (4.0, 2)
 * - Dequeue == (5.0, 2)
 * - Destroy Queue
 */
static bool spBPQueueEnqueueDequeuePeek_WhenFullNoRemove_Test()
{
	SPBPQueue q = spBPQueueCreate(2);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(2, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	SPListElement e3 = spListElementCreate(3, 5.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);

	msg = spBPQueueEnqueue(q, e3);
	ASSERT_TRUE(SP_BPQUEUE_FULL == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);


	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);


	spBPQueueDestroy(q);
	spListElementDestroy(e2);
	spListElementDestroy(e1);
	spListElementDestroy(e3);

	return true;
}

/*
 * - Create queue with max_size = 3;
 * - Insert Element(Val,Index) = (5.0, 2)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - Insert Element(Val,Index) = (5.0, 3)
 * - Insert Element(Val,Index) = (4.0, 3)
 * - Dequeue == (4.0, 2)
 * - Dequeue == (4.0, 3)
 * - Dequeue == (5.0, 2)
 * - Destroy Queue
 */
static bool spBPQueueEnqueueDequeuePeek_WhenFullInsertMiddle_Test()
{
	SPBPQueue q = spBPQueueCreate(3);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(2, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);
	SPListElement e3 = spListElementCreate(3, 5.0);
	SPListElement e4 = spListElementCreate(3, 4.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e3);
	spBPQueueEnqueue(q, e4);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 3 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	spListElementDestroy(e2);
	spListElementDestroy(e1);
	spListElementDestroy(e3);
	spListElementDestroy(e4);
	spBPQueueDestroy(q);
	return true;
}


/*
 * - Create queue with max_size = 2;
 * - Insert Element(Val,Index) = (6.0, 2)
 * - PeekLast == (6.0, 2)
 * - Insert Element(Val,Index) = (5.0, 2)
 * - PeekLast == (6.0, 2)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - PeekLast == (5.0, 2)
 * - Insert Element(Val,Index) = (3.0, 2)
 * - PeekLast == (4.0, 2)
 * - Destroy Queue
 */
static bool spBPQueuePeekLast_Test()
{
	SPBPQueue q = spBPQueueCreate(2);

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(2, 6.0);
	SPListElement e1 = spListElementCreate(2, 5.0);
	SPListElement e3 = spListElementCreate(2, 4.0);
	SPListElement e4 = spListElementCreate(2, 3.0);

	spBPQueueEnqueue(q, e2);
	e = spBPQueuePeekLast(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 6.0 == spListElementGetValue(e));
	spListElementDestroy(e);


	spBPQueueEnqueue(q, e1);
	e = spBPQueuePeekLast(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 6.0 == spListElementGetValue(e));
	spListElementDestroy(e);


	spBPQueueEnqueue(q, e3);
	e = spBPQueuePeekLast(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);


	spBPQueueEnqueue(q, e4);
	e = spBPQueuePeekLast(q);
	ASSERT_TRUE( 2 == spListElementGetIndex(e));
	ASSERT_TRUE( 4.0 == spListElementGetValue(e));
	spListElementDestroy(e);


	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	spListElementDestroy(e4);
	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 2;
 * - PeekLast == NULL
 * - Destroy Queue
 */
static bool spBPQueuePeekLastEmpty_Test()
{
	SPBPQueue q = spBPQueueCreate(2);
	SPListElement e = spBPQueuePeekLast(q);

	ASSERT_TRUE( NULL == e);

	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 2;
 * - Peek == NULL
 * - Destroy Queue
 */
static bool spBPQueuePeekEmpty_Test()
{
	SPBPQueue q = spBPQueueCreate(2);
	SPListElement e = spBPQueuePeek(q);

	ASSERT_TRUE( NULL == e);

	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 4;
 * - Dequeue == EmptyMessage
 * - Destroy Queue
 */
static bool spBPQueueDequeueEmpty_Test()
{
	SPBPQueue q = spBPQueueCreate(2);
	SP_BPQUEUE_MSG msg;

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == msg);

	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (4.0, 2)
 * - MinValue == 4.0
 * - MinValue == 5.0
 * - MinValue == -1.0
 * - Destroy Queue
 */
static bool spBPQueueMinValue_Test()
{
	SPBPQueue q = spBPQueueCreate(4);
	SP_BPQUEUE_MSG msg;

	SPListElement e2 = spListElementCreate(2, 5.0);
	SPListElement e1 = spListElementCreate(2, 4.0);

	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);

	ASSERT_TRUE( 4 == spBPQueueMinValue(q));

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	ASSERT_TRUE( 5 == spBPQueueMinValue(q));

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	ASSERT_TRUE( -1 == spBPQueueMinValue(q)); // empty queue

	spListElementDestroy(e2);
	spListElementDestroy(e1);
	spBPQueueDestroy(q);
	return true;
}

/*
 * - Create queue with max_size = 2;
 * - Insert Element(Val,Index) = (6.0, 2)
 * - PeekLast == 6.0
 * - Insert Element(Val,Index) = (5.0, 2)
 * - PeekLast == 6.0
 * - Insert Element(Val,Index) = (4.0, 2)
 * - PeekLast == 5.0
 * - Insert Element(Val,Index) = (3.0, 2)
 * - PeekLast == 4.0
 * - Destroy Queue
 */
static bool spBPQueueMaxValue_Test()
{
	SPBPQueue q = spBPQueueCreate(2);

	SPListElement e = spListElementCreate(2, 6.0);
	SPListElement e1 = spListElementCreate(2, 5.0);
	SPListElement e3 = spListElementCreate(2, 4.0);
	SPListElement e4 = spListElementCreate(2, 3.0);


	spBPQueueEnqueue(q, e);
	ASSERT_TRUE( 6 == spBPQueueMaxValue(q));

	spBPQueueEnqueue(q, e1);
	ASSERT_TRUE( 6 == spBPQueueMaxValue(q));

	spBPQueueEnqueue(q, e3);
	ASSERT_TRUE( 5 == spBPQueueMaxValue(q));

	spBPQueueEnqueue(q, e4);
	ASSERT_TRUE( 4 == spBPQueueMaxValue(q));


	spBPQueueDequeue(q);
	spBPQueueDequeue(q);
	ASSERT_TRUE( -1 == spBPQueueMaxValue(q)); // empty queue

	spListElementDestroy(e);
	spListElementDestroy(e1);
	spListElementDestroy(e3);
	spListElementDestroy(e4);
	spBPQueueDestroy(q);
	return true;
}

/*
 * Call all functions with (queue == NULL) - check return value
 */
static bool checkNULLS_Test()
{
	SPBPQueue qReal = spBPQueueCreate(2);
	SPBPQueue q;
	SP_BPQUEUE_MSG msg;
	int res = 0;
	SPListElement e = NULL;
	SPListElement eReal = spListElementCreate(2, 6.0);
	double resD = 0;

	q = spBPQueueCopy(NULL);
	ASSERT_TRUE(NULL == q);

	spBPQueueDestroy(NULL);
	spBPQueueClear(NULL);


	res = spBPQueueSize(NULL);
	ASSERT_TRUE(-1 == res);

	res = spBPQueueGetMaxSize(NULL);
	ASSERT_TRUE(-1 == res);

	msg = spBPQueueEnqueue(NULL, eReal);
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == msg);

	msg = spBPQueueEnqueue(qReal, NULL);
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == msg);

	msg = spBPQueueDequeue(NULL);
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == msg);

	e = spBPQueuePeek(NULL);
	ASSERT_TRUE(NULL == e);

	e = spBPQueuePeekLast(NULL);
	ASSERT_TRUE(NULL == e);

	resD = spBPQueueMinValue(NULL);
	ASSERT_TRUE(-1.0 == resD);

	resD = spBPQueueMaxValue(NULL);
	ASSERT_TRUE(-1.0 == resD);

	spListElementDestroy(eReal);
	spBPQueueDestroy(qReal);
	return true;
}

/*
 * - Create queue with max_size = 4;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Dequeue == (5.0, 1)
 * - Dequeue == (5.0, 1)
 * - Dequeue == EmptyMessage
 * - Destroy Queue
 */
static bool sameVal_Test1()
{
	SPBPQueue q = spBPQueueCreate(4);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(1, 5.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == msg);

	spBPQueueDestroy(q);
	spListElementDestroy(e2);
	spListElementDestroy(e1);

	return true;
}

/*
 * - Create queue with max_size = 2;
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Insert Element(Val,Index) = (5.0, 2)
 * - Insert Element(Val,Index) = (5.0, 1)
 * - Dequeue == (5.0, 1)
 * - Dequeue == (5.0, 1)
 * - Dequeue == EmptyMessage
 * - Destroy Queue
 */
static bool sameVal_Test2()
{
	SPBPQueue q = spBPQueueCreate(2);
	SP_BPQUEUE_MSG msg;

	SPListElement e = NULL;
	SPListElement e2 = spListElementCreate(1, 5.0);
	SPListElement e1 = spListElementCreate(2, 5.0);
	SPListElement e3 = spListElementCreate(1, 5.0);
	spBPQueueEnqueue(q, e2);
	spBPQueueEnqueue(q, e1);
	spBPQueueEnqueue(q, e3);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	e = spBPQueuePeek(q);
	ASSERT_TRUE( 1 == spListElementGetIndex(e));
	ASSERT_TRUE( 5.0 == spListElementGetValue(e));
	spListElementDestroy(e);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == msg);

	msg = spBPQueueDequeue(q);
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == msg);

	spBPQueueDestroy(q);
	spListElementDestroy(e2);
	spListElementDestroy(e1);
	spListElementDestroy(e3);

	return true;
}



/*** those test asserts - so run it separately ***/
/*
static bool checkNULLAssertEmpty_Test()
{
	spBPQueueIsEmpty(NULL);

	return true;
}


static bool checkNULLSAssertFull_Test()
{
	spBPQueueIsFull(NULL);

	return true;
}
*/
/*


int main()
{
	RUN_TEST(spBPQueueCreateBasic_Test);
	RUN_TEST(spBPQueueCreateZero_Test);
	RUN_TEST(spBPQueueCheckSizes_Test);

	RUN_TEST(spBPQueueDestroyBasic_Test);
	RUN_TEST(spBPQueueClear_Test);

	RUN_TEST(spBPQueueCopyBasic_Test);
	RUN_TEST(spBPQueueCopyCheckCopiedElements_Test);
	RUN_TEST(spBPQueueCopyCheckDestroy_Test);
	RUN_TEST(spBPQueueCopyCheckClear_Test);

	RUN_TEST(spBPQueueSize_Test);
	RUN_TEST(spBPQueueGetMaxSize_Test);

	RUN_TEST(spBPQueueIsFull_Test);
	RUN_TEST(spBPQueueIsEmpty_Test);

	RUN_TEST(spBPQueueEnqueueDequeuePeek_Basic_Test);
	RUN_TEST(spBPQueueEnqueueDequeuePeek_WhenFullRemove_Test);
	RUN_TEST(spBPQueueEnqueueDequeuePeek_WhenFullNoRemove_Test);
	RUN_TEST(spBPQueueEnqueueDequeuePeek_WhenFullInsertMiddle_Test);
	RUN_TEST(spBPQueueEnqueueDequeuePeek_InsertByIndex_Test);

	RUN_TEST(spBPQueuePeekLast_Test);
	RUN_TEST(spBPQueuePeekLastEmpty_Test);
	RUN_TEST(spBPQueuePeekEmpty_Test);

	RUN_TEST(spBPQueueDequeueEmpty_Test);

	RUN_TEST(spBPQueueMinValue_Test);
	RUN_TEST(spBPQueueMaxValue_Test);

	RUN_TEST(sameVal_Test1);
	RUN_TEST(sameVal_Test2);

	RUN_TEST(checkNULLS_Test);

	* those tests asserts - so run it separately *

	RUN_TEST(checkNULLAssertEmpty_Test);
	RUN_TEST(checkNULLSAssertFull_Test);



	printf("-----FINISHED-----");
	return 0;
}


*/
