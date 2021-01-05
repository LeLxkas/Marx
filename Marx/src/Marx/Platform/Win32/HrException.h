#pragma once

#include "Marx/Exceptions/MarxException.h"

namespace Marx
{
	inline std::string hrToString(HRESULT hr)
	{
		_com_error err(hr);
		return err.ErrorMessage();
	}

	class HrException : public MarxException
	{
	public:
		HrException(int line, const char* file, HRESULT hr, bool autoLog = true)
			: MarxException(line, file, hrToString(hr), false)
		{
			MX_EXCEPT_AUTOLOG();
		}
	public:
		virtual const char* getName() const noexcept override { return "HrException"; }
		virtual std::string getInfo() const noexcept override
		{
			return "No info";
		}
	};
}