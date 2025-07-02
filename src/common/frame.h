
#ifndef __FRAME_H__
#define __FRAME_H__

#include "../main.h"
#include <functional>
#include <any>

typedef std::function<void(const std::any&)>  PropertyNotification;

class PropertyTrigger
{
public:
	PropertyTrigger() noexcept {}
	PropertyTrigger(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept {}

	PropertyTrigger& operator=(const PropertyTrigger&) = delete;

	void ClearNotifications() noexcept
	{
		m_vec_nf.clear();
	}

	uintptr_t AddNotification(PropertyNotification&& pn);
	void RemoveNnotification(uintptr_t cookie) noexcept
	{
		if( cookie > 0 && cookie <= m_vec_nf.size() )
			m_vec_nf[cookie - 1] = nullptr;
	}

protected:

void fire(uint32_t nf_id, const std::any& any_para);

private:
	std::vector<PropertyNotification> m_vec_nf;
};

#endif
