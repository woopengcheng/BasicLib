#ifndef __msg_msg_common_h__
#define __msg_msg_common_h__
#include "Common.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_queue.h"
#include "tbb/concurrent_priority_queue.h"
#include "vector"

#define MSG_ID  UINT64

namespace Msg
{ 
#define tbb_unordered_map     tbb::concurrent_unordered_map 
#define tbb_hash_map          tbb::concurrent_hash_map 
#define tbb_queue             tbb::concurrent_queue 
#define tbb_priority_queue    tbb::concurrent_priority_queue

#define DEFAULT_MSG_THREAD_ID            3
#define DEFAULT_MSG_HANDLE_THREAD_ID     4

#define MAX_MSG_METHOD_NAME_LENGTH       60
#define MSG_MAX_PARAMETER_NUMBER         10 
}
#endif