
#ifndef __FRAME_H__
#define __FRAME_H__

#include "main.h"

typedef std::function<void(uint32_t)>  PropertyNotification;

class PropertyTrigger
{
public:
	PropertyTrigger() noexcept
	{
	}
	PropertyTrigger(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept
	{
	}

	PropertyTrigger& operator=(const PropertyTrigger&) = delete;

	void clear_notifications() noexcept
	{
		m_vec_nf.clear();
	}

	uintptr_t add_notification(PropertyNotification&& pn);
	void remove_notification(uintptr_t cookie) noexcept
	{
		assert( cookie > 0 && cookie <= m_vec_nf.size() );
		m_vec_nf[cookie - 1] = nullptr;
	}

protected:
	void fire(uint32_t id);

private:
	std::vector<PropertyNotification> m_vec_nf;
};

#endif
