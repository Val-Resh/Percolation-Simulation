#include "PercolationTrialTesting.h"

/*
* Constructor!
* Executes the trials in parallel upon construction.
*/
PercolationTrialTesting::PercolationTrialTesting(unsigned int networkSize, unsigned int numberOfTrials)
{
	this->numberOfTrials = numberOfTrials;
	this->completed = false;
	std::random_device random;
	this->random = std::mt19937_64(random());
	this->distribution = std::uniform_int_distribution<int>(0, networkSize-1);

	auto displaying = std::async(std::launch::async,
		&PercolationTrialTesting::calculatingDisplay, this);

	for (int i = 0; i < numberOfTrials; i++)
	{
		this->allTrialsFutures.push_back(
			std::async(std::launch::async,
				&PercolationTrialTesting::runTrial, this, networkSize));
	}

	this->waitForAllResults();
	this->futuresToResultsConversion();
}

/*
* Returns whether all threads completed the trials.
*/
bool PercolationTrialTesting::hasCompleted()
{
	return this->completed;
}


/*
* Runs a trial on a new network of parameter size, opening sites at random until percolation is reached.
*/
double PercolationTrialTesting::runTrial(unsigned int networkSize)
{
	std::unique_ptr<PercolationSite> percolationTest(new PercolationSite(networkSize));
	
	while (!percolationTest->percolates())
	{
		int x = this->distribution(this->random);
		int y = this->distribution(this->random);
		percolationTest->openSite(x, y);
	}
	
	return percolationTest->getTotalOpenSites() / ((double)networkSize * networkSize);
}

/*
* Function call to wait for all futures to complete computing their results.
* Sets completed to true after all futures complete.
*/
void PercolationTrialTesting::waitForAllResults()
{
	for (auto& future : this->allTrialsFutures)
	{
		future.wait();
	}

	this->completed = true;
}

/*
* Calculates the meadian value from all trials results.
*/
double PercolationTrialTesting::resultsMeanValue()
{
	double sum = 0;
	for (double value : this->allTrialResults)
	{
		sum += value;
	}
	return sum / (double)this->numberOfTrials;
}

/*
* Calculates the standard deviation of the percolation treshold.
*/
double PercolationTrialTesting::standardDeviation()
{
	double mean = resultsMeanValue();
	double standardDeviation = 0.00;

	for (double value : this->allTrialResults)
	{
		standardDeviation += std::pow(value - mean, 2);
	}

	return std::sqrt(standardDeviation / this->numberOfTrials);
}

/*
* Returns the 95% confidence interval. Both the low and high as a pair. 
*/
std::pair<double, double> PercolationTrialTesting::confidenceInterval()
{
	double confidence = ((1.96 * this->standardDeviation()) / std::sqrt(this->numberOfTrials));
	double high = this->resultsMeanValue() + confidence;
	double low = this->resultsMeanValue() + confidence;

	return std::make_pair(low, high);
}

/*
* Simple display while computing trials.
*/
void PercolationTrialTesting::calculatingDisplay()
{
	std::cout << "Calculating";
	std::cout.flush();
	while (!this->completed)
	{
		for (int i = 0; i < 3; i++)
		{
			std::cout << ".";
			std::cout.flush();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		std::cout << "\b\b\b   \b\b\b";
	}
	std::cout << "\b\b\b\b\b\b\b\b\b\b\b                         ";
}

/*
* Places all the futures results in a results vector.
* Should only be called after all futures complete.
*/
void PercolationTrialTesting::futuresToResultsConversion()
{
	for (auto& future : this->allTrialsFutures)
	{
		this->allTrialResults.push_back(future.get());
	}

	this->allTrialsFutures.clear();
}