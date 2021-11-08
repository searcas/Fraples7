#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Fraples {
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* _mCurrentSession;
		std::ofstream _mOutputStream;
		int m_ProfileCount;
	public:
		Instrumentor()
			: _mCurrentSession(nullptr), m_ProfileCount(0)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			_mOutputStream.open(filepath);
			WriteHeader();
			_mCurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			_mOutputStream.close();
			delete _mCurrentSession;
			_mCurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				_mOutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			_mOutputStream << "{";
			_mOutputStream << "\"cat\":\"function\",";
			_mOutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			_mOutputStream << "\"name\":\"" << name << "\",";
			_mOutputStream << "\"ph\":\"X\",";
			_mOutputStream << "\"pid\":0,";
			_mOutputStream << "\"tid\":" << result.ThreadID << ",";
			_mOutputStream << "\"ts\":" << result.Start;
			_mOutputStream << "}";

			_mOutputStream.flush();
		}

		void WriteHeader()
		{
			_mOutputStream << "{\"otherData\": {},\"traceEvents\":[";
			_mOutputStream.flush();
		}

		void WriteFooter()
		{
			_mOutputStream << "]}";
			_mOutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: _mName(name), _mStopped(false)
		{
			_mStartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!_mStopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_mStartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ _mName, start, end, threadID });

			_mStopped = true;
		}
	private:
		const char* _mName;
		std::chrono::time_point<std::chrono::high_resolution_clock> _mStartTimepoint;
		bool _mStopped;
	};

	namespace InstrumentorUtils
	{
		template<size_t N>
		struct ChangeResult
		{
			char Data[N];
		};
		template<size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};
			size_t srcIndex = 0;
			size_t dstIndex = 0;

			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					++matchIndex;
				if (matchIndex == K - 1)
				{
					srcIndex += matchIndex;
				}
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				++srcIndex;
			}
			return result;
		}
	}
}
#define FPL_PROFILE 0
#if FPL_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define FPL_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define FPL_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define FPL_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define FPL_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define FPL_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define FPL_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define FPL_FUNC_SIG __func__
#else
#define FPL_FUNC_SIG "FPL_FUNC_SIG unknown!"
#endif

#define FPL_PROFILE_BEGIN_SESSION(name, filepath) ::Fraples::Instrumentor::Get().BeginSession(name, filepath)
#define FPL_PROFILE_END_SESSION() ::Fraples::Instrumentor::Get().EndSession()
#define FPL_PROFILE_SCOPE(name) constexpr auto fixedName = ::Fraples::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
									::Fraples::InstrumentationTimer timer##__LINE__(fixedName.Data)
#define FPL_PROFILE_FUNCTION() FPL_PROFILE_SCOPE(FPL_FUNC_SIG)
#else
#define FPL_PROFILE_BEGIN_SESSION(name, filepath)
#define FPL_PROFILE_END_SESSION()
#define FPL_PROFILE_SCOPE(name)
#define FPL_PROFILE_FUNCTION()
#endif