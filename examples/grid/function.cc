// (C) Maciej Gajewski, 2016

#include "function.hh"

#include <cmath>
#include <random>

namespace QtGridModel { namespace Examples { namespace Grid {

void Function::InitWithRandomParams()
{
	std::default_random_engine engine;

	std::normal_distribution<double> amplitudeDistr(6, 2);
	std::normal_distribution<double> freqDistribution(10, 5);
	std::uniform_real_distribution<double> phaseDistribution(0, 2*M_PI);

	mW = freqDistribution(engine);

	mA1 = amplitudeDistr(engine);
	mA2 = amplitudeDistr(engine);
	mA3 = amplitudeDistr(engine);

	mO1 = phaseDistribution(engine);
	mO2 = phaseDistribution(engine);
	mO3 = phaseDistribution(engine);
}

double Function::GetValue() const
{
	return
		mA1 * std::sin(mT*mW + mO1) +
		mA2 * std::sin(mT*mW*2 + mO3) +
		mA3 * std::sin(mT*mW*4 + mO3);
}

}}}

