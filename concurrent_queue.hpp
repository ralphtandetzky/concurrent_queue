#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP
template <typename T>
class concurrent_queue
{
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
public:
	template <typename Arg>
	void push(Arg&& item) /* support perfect forwarding */
	{
		{ /* scope-based lock */
			std::unique_lock<std::mutex> lock(m_mutex);
			m_queue.push(std::forward<Arg>(item));
		}
		m_cond.notify_one();
	}
	void wait_and_pop(T& item)
	{
		/* scope-based lock */
		std::unique_lock<std::mutex> lock(m_mutex);
		/* wait for sig, loop incase of spur. sig */
		while (m_queue.empty()) {
			m_cond.wait(lock);
		}
		item = m_queue.front();
		m_queue.pop();
	}
	bool pop(T& item)
	{
		/* scope-based lock */
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty()) {
			return false;
		}
		item = m_queue.front();
		m_queue.pop();
		return true;
	}
};
#endif
