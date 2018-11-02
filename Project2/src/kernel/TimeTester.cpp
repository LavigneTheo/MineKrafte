#include "TimeTester.h"



void TimeTester::save() {
	if (mTimes.size() == 0) return;
	double avg, max = 0, min = 10000, sum = 0;
	for (int i = 0; i < mTimes.size(); i++) {
		double v = mTimes.at(i);
		sum += v;
		if (max < v)
			max = v;
		if (min > v)
			min = v;
	}
	avg = sum / mTimes.size();
	std::cout << mTimes.size() << std::endl;
	FILE* f = NULL;
	std::string path = std::string("TimeTester/").append(testName).append(".txt");
	fopen_s(&f, path.c_str(), "w");

	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	fprintf(f, "#Size = %d - avg = %lf - sum = %lf\n", mTimes.size(), avg, sum);
	fprintf(f, "#Min = %lf - Max = %lf\n", min, max);
	for (int y = 0; y < mTimes.size(); y++) {
		fprintf(f, "%f\n", mTimes.at(y));
	}
	
	fclose(f);
}