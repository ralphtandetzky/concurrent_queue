#ifndef EVENT_LOOP_HPP
#define EVENT_LOOP_HPP
#include "concurrent_queue.hpp"
#include "job.hpp"
class event_loop
{
using event = std::unique_ptr<job>;
using event_queue = concurrent_queue<event>;
private:
	event_queue events;
public:
	template <typename Arg>
	void schedule(Arg&& event)
	{
		events.push(std::forward<Arg>(event));
	}
	void process()
	{
		event e;
		if (events.pop(e)) {
			e.run();
		}
	}
};
#endif
