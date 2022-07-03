#pragma once

#ifndef __H_CCPPCONFIGXML__
#define __H_CCPPCONFIGXML__

#include <ICPPConfig.hpp>

namespace __N_CPPCONFIG__
{
	class CCPPConfigXML : public ICPPConfig
	{
	private:
	protected:
	public:
		CCPPConfigXML() = default;
		CCPPConfigXML(const CCPPConfigXML&) = delete;
		CCPPConfigXML(CCPPConfigXML&&) = delete;
		CCPPConfigXML& operator = (const CCPPConfigXML&) = delete;
		CCPPConfigXML& operator = (CCPPConfigXML&&) = delete;
		~CCPPConfigXML() = default;

		bool Initialize(std::string szFilePath, std::string szFileName) noexcept final;
		bool UnInitialize() noexcept final;

		bool Add(const std::string strKey, const std::string strValue) noexcept final;
		bool Add(const std::string strKey, const std::vector<std::string> values) noexcept final;
		bool Load(const std::string strKey, std::string & strValue) noexcept final;
		bool Load(const std::string strKey, std::vector<std::string>& values) noexcept final;
		bool Delete(const std::string strKey) noexcept final;
	};
} // !__N_CPPCONFIG__

#endif // !__H_CCPPCONFIGXML__

