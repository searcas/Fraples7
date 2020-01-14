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
}
#define FPL_PROFILER 1
#if FPL_PROFILER
	#define FPL_PROFILE_SESSION_BEGIN(name, filepath) ::Fraples::Instrumentor::Get().BeginSession(name, filepath)
	#define FPL_PROFILE_SESSION_END() ::Fraples::Instrumentor::Get().EndSession()
	#define FPL_PROFILE_SCOPE(name) ::Fraples::InstrumentationTimer timer##__LINE__(name)
	#define FPL_PROFILE_FUNCTION() FPL_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define FPL_PROFILE_SESSION_BEGIN()
	#define FPL_PROFILE_SESSION_END()
	#define FPL_PROFILE_SCOPE(name)
	#define FPL_PROFILE_FUNCTION()
#endif