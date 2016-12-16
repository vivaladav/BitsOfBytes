#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

const int NUM_CPU_STATES = 10;

enum CPUStates
{
	S_USER = 0,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

typedef struct CPUData
{
	std::string cpu;
	size_t times[NUM_CPU_STATES];
} CPUData;

void ReadStats(std::vector<CPUData> & entries);

size_t GetIdleTime(const CPUData & entry1, const CPUData & entry2);
size_t GetActiveTime(const CPUData & entry1, const CPUData & entry2);

int main(int argc, char * argv[])
{
	std::vector<CPUData> entries1;
	std::vector<CPUData> entries2;

	// snapshot 1
	ReadStats(entries1);

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	ReadStats(entries2);

	// -- PRINT TIMES --
	for(unsigned int i = 0; i < entries1.size(); ++i)
	{
		CPUData & entry1 = entries1[i];
		CPUData & entry2 = entries2[i];

		std::cout << entry1.cpu << std::endl; 
			
		const size_t ACTIVE_TIME	= GetActiveTime(entry1, entry2);
		const size_t IDLE_TIME		= GetIdleTime(entry1, entry2);
		const size_t TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

		std::cout << "active: ";
		std::cout.setf(std::ios::fixed, std:: ios::floatfield);
        std::cout.width(6);
        std::cout.precision(2);
		std::cout << (100.f * static_cast<float>(ACTIVE_TIME) / static_cast<float>(TOTAL_TIME)) << "%" << std::endl;

		std::cout << "idle:   ";
		std::cout.setf(std::ios::fixed, std:: ios::floatfield);
        std::cout.width(6);
        std::cout.precision(2);
		std::cout << (100.f * static_cast<float>(IDLE_TIME) / static_cast<float>(TOTAL_TIME)) << "%" << std::endl;

		std::cout << std::endl;
	}

	return 0;
}

void ReadStats(std::vector<CPUData> & entries)
{
    std::ifstream fileStat("/proc/stat");

	std::string line;

	const std::string STR_CPU("cpu");
	const std::size_t LEN_STR_CPU = STR_CPU.size();
	const std::string STR_TOT("tot");

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
		if(0 == line.compare(0, LEN_STR_CPU, STR_CPU))
		{
			std::istringstream ss(line);

			CPUData entry;

			// read cpu label
			ss >> entry.cpu;

			// remove "cpu" from the label when it's a processor number
			if(entry.cpu.size() > LEN_STR_CPU)
				entry.cpu.erase(0, LEN_STR_CPU);
			// replace "cpu" with "tot" when it's total values
			else
				entry.cpu = STR_TOT;

			// read times
			for(int i = 0; i < NUM_CPU_STATES; ++i)
				ss >> entry.times[i];

			// store entry
			entries.emplace_back(entry);
		}
	}
}

size_t GetIdleTime(const CPUData & entry1, const CPUData & entry2)
{
	return (entry2.times[S_IDLE] - entry1.times[S_IDLE]) + (entry2.times[S_IOWAIT] - entry1.times[S_IOWAIT]);
}

size_t GetActiveTime(const CPUData & entry1, const CPUData & entry2)
{
	return	(entry2.times[S_USER] - entry1.times[S_USER]) +
			(entry2.times[S_NICE] - entry1.times[S_NICE]) +
			(entry2.times[S_SYSTEM] - entry1.times[S_SYSTEM]) +
			(entry2.times[S_IRQ] - entry1.times[S_IRQ]) +
			(entry2.times[S_SOFTIRQ] - entry1.times[S_SOFTIRQ]) +
			(entry2.times[S_STEAL] - entry1.times[S_STEAL]) +
			(entry2.times[S_GUEST] - entry1.times[S_GUEST]) + 
			(entry2.times[S_GUEST_NICE] - entry1.times[S_GUEST_NICE]);
}

