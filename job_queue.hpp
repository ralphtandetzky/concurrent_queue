#ifndef JOB_QUEUE_HPP
#define JOB_QUEUE_HPP
#include "concurrent_queue.hpp"
#include <memory>
using job_queue = concurrent_queue<std::unique_ptr<job>>;
#endif
