#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#ifndef Core_H
#define Core_H

#include "Europa/Core.h"
#endif






namespace Eu {

	class EUROPA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
//Core Log Marco
#define EU_CORE_FATAL(...)		::Eu::Log::GetCoreLogger()->fatal(__VA_ARGS__);
#define EU_CORE_ERROR(...)		::Eu::Log::GetCoreLogger()->error(__VA_ARGS__);
#define EU_CORE_WARN(...)		::Eu::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define EU_CORE_INFO(...)		::Eu::Log::GetCoreLogger()->info(__VA_ARGS__);
#define EU_CORE_TRACE(...)		::Eu::Log::GetCoreLogger()->trace(__VA_ARGS__);
//Client Log Macros
#define EU_CLIENT_FATAL(...)	::Eu::Log::GetClientLogger()->fatal(__VA_ARGS__);
#define EU_CLIENT_ERROR(...)	::Eu::Log::GetClientLogger()->error(__VA_ARGS__);
#define EU_CLIENT_WARN(...)		::Eu::Log::GetClientLogger()->warn(__VA_ARGS__);
#define EU_CLIENT_INFO(...)		::Eu::Log::GetClientLogger()->info(__VA_ARGS__);
#define EU_CLIENT_TRACE(...)	::Eu::Log::GetClientLogger()->trace(__VA_ARGS__);
