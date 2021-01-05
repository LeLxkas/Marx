#pragma once

#include <chrono>

namespace Marx
{
	class Timestep
	{
	public:
		Timestep(float time)
			: m_currTime(time), m_diffTime(0.0001f)
		{}
	public:
		operator float() const { return m_diffTime; } // Returns the relative and not the absolute time!!!
	public:
		inline void update(float newTime) { m_diffTime = newTime - m_currTime; m_currTime = newTime; }
		inline float getSeconds() const { return m_currTime; }
		inline float getMilliseconds() const { return getSeconds() * 1000.0f; }
		inline float getPassedSeconds() const { return m_diffTime; }
		inline float getPassedMilliseconds() const { return getPassedSeconds() * 1000.0f; }
	public:
		inline static float secondsSinceProgramStartup() { return std::chrono::duration<float>(std::chrono::steady_clock::now() - s_startup).count(); }
	private:
		float m_currTime;
		float m_diffTime;
		inline static std::chrono::steady_clock::time_point s_startup = std::chrono::steady_clock::now();
	};
}