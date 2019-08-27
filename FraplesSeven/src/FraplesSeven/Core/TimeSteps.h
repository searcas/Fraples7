#pragma once




namespace Fraples
{
	struct TimeSteps
	{
		TimeSteps(float time = 0.0f):_mTime(time)
		{

		}
		float GetSeconds() const { return _mTime; }
		float GetMilliSeconds() const { return _mTime * 1000.0f; }
		operator float()const { return _mTime; }
	private:
		float _mTime = 0.0f;
	};
}