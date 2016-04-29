// (C) Maciej Gajewski, 2016
#pragma once

#include <cstdint>

namespace QtBinder { namespace Examples { namespace Grid {

// Example "active" objkect, object with changing and modifiable state, whihc wil be displayed in the grid.
// The function it's a simple, 3-step harmonic, just ot have some values and nice-looking graph
class Function
{
public:

	void InitWithRandomParams();

	double GetT() const { return mT; }
	std::uint64_t GetTicks() const { return mTicks; }

	double GetW() const { return mW; }
	void SetW(double v) { mW = v; }

	double GetA1() const { return mA1; }
	void SetA1(double v) { mA1 = v; }
	double GetO1() const { return mO1; }
	void SetO1(double v) { mO1 = v; }

	double GetA2() const { return mA2; }
	void SetA2(double v) { mA2 = v; }
	double GetO2() const { return mO2; }
	void SetO2(double v) { mO2 = v; }

	double GetA3() const { return mA3; }
	void SetA3(double v) { mA3 = v; }
	double GetO3() const { return mO3; }
	void SetO3(double v) { mO3 = v; }

	double GetValue() const;

	void AddToTime(double dt) { mT += dt; mTicks++; }

private:

	// state
	double mT =  0.0;
	std::uint64_t mTicks = 0;

	// params

	double mW = 1.0; // base pulsation

	// 1st harmonic
	double mA1 = 10.0; // amplitude
	double mO1 = 0.0; // phase

	double mA2 = -5.0;
	double mO2 = 0.0;

	double mA3 = 2.5;
	double mO3 = 0.0;
};

}}}

