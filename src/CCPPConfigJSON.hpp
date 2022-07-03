#pragma once

#ifndef __H_CCPPCONFIGJSON__
#define __H_CCPPCONFIGJSON__

#include <ICPPConfig.hpp>

namespace __N_CPPCONFIG__
{
	class CCPPConfigJSON : public ICPPConfig
	{
	private:
	protected:
	public:
		CCPPConfigJSON() = default;
		CCPPConfigJSON(const CCPPConfigJSON&) = delete;
		CCPPConfigJSON(CCPPConfigJSON&&) = delete;
		CCPPConfigJSON& operator = (const CCPPConfigJSON&) = delete;
		CCPPConfigJSON& operator = (CCPPConfigJSON&&) = delete;
		~CCPPConfigJSON() = default;

		bool Initialize(std::string szFilePath, std::string szFileName) noexcept final;
		bool UnInitialize() noexcept final;

		bool Add(const std::string strKey, const std::string strValue) noexcept final;
		bool Add(const std::string strKey, const std::vector<std::string> values) noexcept final;
		bool Load(const std::string strKey, std::string & strValue) noexcept final;
		bool Load(const std::string strKey, std::vector<std::string>& values) noexcept final;
		bool Delete(const std::string strKey) noexcept final;
	};
} // !__N_CPPCONFIG__

#endif // !__H_CCPPCONFIGJSON__

