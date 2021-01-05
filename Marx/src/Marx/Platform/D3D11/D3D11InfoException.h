#pragma once

#include "Marx/Platform/Win32/HrException.h"

namespace Marx
{
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