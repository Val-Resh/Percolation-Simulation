#include <memory>
#include <random>
#include <stdlib.h>
#include "PercolationTrialTesting.h"


int main(int agrc, char* agrv[])
{
	if (agrc != 3) return 1;
	else
	{
		int size = std::atoi(agrv[1]);
		int numberOfTrials = std::atoi(agrv[2]);
		std::unique_ptr<PercolationTrialTesting> trials(new PercolationTrialTesting(size, numberOfTrials));

		auto confidence = trials->confidenceInterval();
		std::cout.precision(17);
		std::cout << "\nResults for a network with " << size*size << " nodes.\n" << numberOfTrials << " trials ran:\n" << std::endl;
		std::cout << "Mean Percolation        = " << trials->resultsMeanValue() << std::endl;
		std::cout << "Standard Deviation      = " << trials->standardDeviation() << std::endl;
		std::cout << "95% Confidence Interval = [" << confidence.first << ", " << confidence.second << "]" << std::endl;
	}

	/*std::atexit([] {
		_CrtDumpMemoryLeaks();
		});
		*/
}


