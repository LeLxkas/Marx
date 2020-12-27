#pragma once

#include "MarxException.h"

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

	class HrInfoException : public HrException
	{
	public:
		HrInfoException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs, bool autoLog = true)
			: HrException(line, file, hr, false), m_msgs(infoMsgs)
		{
			MX_EXCEPT_AUTOLOG();
		}
	public:
		virtual const char* getName() const noexcept override { return "HrInfoException"; }
		virtual std::string getInfo() const noexcept override
		{
			std::string outMsg;
			for (const std::string& msg : m_msgs)
			{
				outMsg += msg + "\n";
			}
			if (outMsg.size() > 0)
				outMsg.pop_back();
			return outMsg;
		}
	private:
		std::vector<std::string> m_msgs;
	};
}