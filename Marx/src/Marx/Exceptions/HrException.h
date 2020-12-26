#pragma once

#include "MarxException.h"

#include <comdef.h>

namespace Marx
{
	class HrException : public MarxException
	{
	public:
		HrException(int line, const char* file, HRESULT hr, bool autoLog = true)
			: MarxException(line, file, "No message", false), m_hr(hr)
		{
			MX_EXCEPT_AUTOLOG();
		}
	public:
		virtual const char* getName() const noexcept override { return "HrException"; }
		virtual std::string getInfo() const noexcept override
		{
			_com_error err(m_hr);
			return err.ErrorMessage();
		}
	private:
		HRESULT m_hr;
	};
}