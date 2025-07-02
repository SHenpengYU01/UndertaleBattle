
#include "frame.h"

uintptr_t PropertyTrigger::AddNotification(PropertyNotification&& pn)
{
	uintptr_t index = 0;
	for (auto& fn : m_vec_nf) {
		if (fn == nullptr) {
			fn = std::move(pn);
			return index + 1;
		}
		index ++;
	}
	m_vec_nf.push_back(std::move(pn));
	return index + 1;
}

void PropertyTrigger::fire(uint32_t nf_id, const std::any& any_para)
{
    if( nf_id >=0 && nf_id < m_vec_nf.size() && m_vec_nf[nf_id]){
        m_vec_nf[nf_id](any_para);
    }
}
