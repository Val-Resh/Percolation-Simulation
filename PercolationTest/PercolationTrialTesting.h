#pragma once
#include "PercolationSite.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <random>
#include <future>

class PercolationTrialTesting
{
public:
	PercolationTrialTesting(unsigned int networkSize, unsigned int numerOfTrials);
	double resultsMeanValue();
	double standardDeviation();
	bool hasCompleted();
	std::pair<double, double> confidenceInterval();

private:
	unsigned int numberOfTrials;
	std::vector<std::future<double>> allTrialsFutures;
	std::uniform_int_distribution<int> distribution;
	std::mt19937_64 random;
	std::vector<double> allTrialResults;
	double runTrial(unsigned int networkSize);
	bool completed;
	void futuresToResultsConversion();
	void calculatingDisplay();
	void waitForAllResults();
};

