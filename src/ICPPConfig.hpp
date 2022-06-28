#pragma once

#ifndef __H_ICPPCONFIG__
#define __H_ICPPCONFIG__

#ifdef __cplusplus
    #define EXTERNC extern "C"
#else
    #define EXTERNC 
#endif // !__cplusplus

#ifdef CPPCONFIG_EXPORTS
    #define CPPCONFIGFILE_API EXTERNC __declspec(dllexport)
#else
    #define CPPCONFIGFILE_API EXTERNC __declspec(dllimport)
    #pragma comment(lib, "cppconfig")
#endif // !CPPCONFIG_EXPORTS

#include <string>
#include <vector>

namespace __N_CPPCONFIG__
{
	class ICPPConfig
	{
	private:
	protected:
        bool m_bInitialized{ false };
        std::string m_strLastError{};
		std::string m_strFilePath{};
		std::string m_strFileName{};

	public:
		ICPPConfig() = default;
		ICPPConfig(const ICPPConfig&) = delete;
		ICPPConfig(ICPPConfig&&) = delete;
		ICPPConfig& operator = (const ICPPConfig&) = delete;
		ICPPConfig& operator = (ICPPConfig&&) = delete;
		~ICPPConfig() = default;

		virtual bool Initialize(std::string strPath, std::string strName) noexcept = 0;
		virtual bool UnInitialize() noexcept = 0;
		bool IsInitialized() const noexcept { return this->m_bInitialized; }

		virtual bool Add(const std::string strKey, const std::string strValue) noexcept = 0;
		virtual bool Add(const std::string strKey, const std::vector<std::string> values) noexcept = 0;
		virtual bool Load(const std::string strKey, std::string & strValue) noexcept = 0;
		virtual bool Load(const std::string strKey, std::vector<std::string>& values) noexcept = 0;
		virtual bool Delete(const std::string strKey) noexcept = 0;

        std::string getLastError() const noexcept { return this->m_strLastError; }
	};

	CPPCONFIGFILE_API ICPPConfig* CreateCPPConfigXML() noexcept;
	CPPCONFIGFILE_API void DestroyPPConfigXML(ICPPConfig**) noexcept;

	CPPCONFIGFILE_API ICPPConfig* CreateCPPConfigJSON() noexcept;
	CPPCONFIGFILE_API void DestroyCPPConfigJSON(ICPPConfig**) noexcept;
} // !__N_CPPCONFIG__

#endif  //!__H_ICPPCONFIG__


