/* @Author
*  Student Name: Iskender Akyuz
*  Student ID : 150150150
*  Date: 23.05.2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Part1Result {
	int detectedBugs;
	vector<int> selectedTestSuites;
};

struct TestCaseDistance { 
	int id, distance;
	bool operator<(const TestCaseDistance& a) const { return distance < a.distance; }
};

class TestSuite {
private:
	static int ID;
	int thisId;
	int bugsDetected;
	int runningTime;
	vector<vector<int>> testCaseFreqProfiles;
public:
	TestSuite(int, int, vector<vector<int>>);
	int getId() const;
	int getBugsDetected() const;
	int getRunningTime() const;
	vector<vector<int>> getTestCaseFreqProfiles() const;
	vector<int> GetOrderedSequenceOfStatementExecutionFreq(int);
	int GetIndexOfHighestCoverage() const;
};

TestSuite::TestSuite(int bugsDetected, int runningTime, vector<vector<int>> testCaseFreqProfiles) {
	this->thisId = ID++;
	this->bugsDetected = bugsDetected;
	this->runningTime = runningTime;
	this->testCaseFreqProfiles = testCaseFreqProfiles;
}

int TestSuite::getId() const { return thisId; }
int TestSuite::getBugsDetected() const { return bugsDetected; }
int TestSuite::getRunningTime() const { return runningTime; }
vector<vector<int>> TestSuite::getTestCaseFreqProfiles() const { return testCaseFreqProfiles; }

vector<int> TestSuite::GetOrderedSequenceOfStatementExecutionFreq(int index) {
	vector<int> result;

	int freqProfileLength = testCaseFreqProfiles[index].size();
	int i = 0, currFreq = 0;

	while (result.size() < freqProfileLength) {
		if (testCaseFreqProfiles[index][i] == currFreq)
			result.push_back(i);
		i++;
		if (i == freqProfileLength) {
			i = 0;
			currFreq++;
		}
	}
	return result;
}

int TestSuite::GetIndexOfHighestCoverage() const {
	int max = 0, indexOfMax = 0;

	int temp = 0;
	for (int i = 0; i < testCaseFreqProfiles.size(); i++) {
		for (int j = 0; j < testCaseFreqProfiles[i].size(); j++)
			if (testCaseFreqProfiles[i][j] > 0)	
				temp++;
		if (temp > max) {
			max = temp;
			indexOfMax = i;
		}
		temp = 0;
	}
	return indexOfMax;
}

vector<int> Part1(int, vector<TestSuite>);
int KnapSackRec(int, vector<TestSuite>, int i, int**);
Part1Result KnapSack(int, vector<TestSuite>);
void Part2(vector<TestSuite>, vector<int>);
void GetTestCaseOrder(vector<TestCaseDistance>, vector<int>&);
int LevensteinDistance(const vector<int>, const vector<int>, unsigned int insertCost = 1, unsigned int deleteCost = 1, unsigned int replaceCost = 1);
void PrintOrderedTestCases(int, const vector<int>);
void ReadFile(string, int&, vector<TestSuite>&);
int GetNumberOfTestCaseFreqProfiles(string);
vector<int> ConvertFreqProfileToInt(string);

int TestSuite::ID = 1;

int main(int argc, char* argv[]) {
	// necessary variables
	string filename(argv[1]);
	int maxRunningTime;
	vector<TestSuite> testSuites;
	ReadFile(filename, maxRunningTime, testSuites);

	vector<int> selectedTestSuites = Part1(maxRunningTime, testSuites);
	Part2(testSuites, selectedTestSuites);
	return 0;
}

vector<int> Part1(int maxRunningTime, vector<TestSuite> testSuites) {
	Part1Result result = KnapSack(maxRunningTime, testSuites);
	cout << "Detected bugs: " << result.detectedBugs << endl;
	return result.selectedTestSuites;
}

// Returns the value of maximum detected bugs
int KnapSackRec(int W, vector<TestSuite> testSuites, int i, int** dp) {
	if (i < 0)		// base condition 
		return 0;
	if (dp[i][W] != -1)
		return dp[i][W];

	int weight = testSuites[i].getRunningTime();
	int value = testSuites[i].getBugsDetected();

	if (weight > W) {
		dp[i][W] = KnapSackRec(W, testSuites, i - 1, dp);
		return dp[i][W];
	}
	else {
		dp[i][W] = max(value + KnapSackRec(W - weight, testSuites, i - 1, dp), KnapSackRec(W, testSuites, i - 1, dp));
		return dp[i][W];
	}
}
// Returns the value of maximum detected bugs and selected test suites 
Part1Result KnapSack(int maxRunningTime, vector<TestSuite> testSuites) {
	int n = testSuites.size();
	int** dp;
	dp = new int* [n];					// memory allocation

	for (int i = 0; i < n; i++)
		dp[i] = new int[maxRunningTime + 1];		// memory allocation

	for (int i = 0; i < n; i++)
		for (int j = 0; j < maxRunningTime + 1; j++)
			dp[i][j] = -1;							// filling the table with -1's

	int detectedBugs = KnapSackRec(maxRunningTime, testSuites, n - 1, dp);

	vector<int> selectedTestSuites;
	int res = detectedBugs;
	int w = maxRunningTime;
	// finding the selected test suites
	for (int i = n - 1; i >= 0 && res > 0; i--) {
		if (i > 0 && res == dp[i - 1][w])
			continue;
		else {
			selectedTestSuites.push_back(i + 1);
			// Since this weight is included, its value is deducted 
			res -= testSuites[i].getBugsDetected();
			w -= testSuites[i].getRunningTime();
		}
	}

	for (int i = 0; i < n; ++i)
		delete[] dp[i];		// deleting memory
	delete[] dp;			// deleting memory

	Part1Result result = { detectedBugs, selectedTestSuites };

	return result;
}

void Part2(vector<TestSuite> testSuites, vector<int> selectedTestSuites) {
	vector<int> testCaseOrder;
	vector<TestCaseDistance> distances;
	for (int i = selectedTestSuites.size() - 1; i >= 0; i--) {
		TestSuite testSuite = testSuites[selectedTestSuites[i] - 1];
		vector<vector<int>> freqProfiles = testSuite.getTestCaseFreqProfiles();
		int indexOfHighestCoverage = testSuite.GetIndexOfHighestCoverage();
		testCaseOrder.push_back(indexOfHighestCoverage + 1);
		vector<int> sourceOrderedSeq = testSuite.GetOrderedSequenceOfStatementExecutionFreq(indexOfHighestCoverage);
		for (int j = 0; j < testSuite.getTestCaseFreqProfiles().size(); j++) {
			if (indexOfHighestCoverage == j)	continue;
			vector<int> targetOrderedSeq = testSuite.GetOrderedSequenceOfStatementExecutionFreq(j);
			int distance = LevensteinDistance(sourceOrderedSeq, targetOrderedSeq);
			distances.push_back({j, distance});
		}
		GetTestCaseOrder(distances, testCaseOrder);
		PrintOrderedTestCases(testSuite.getId(), testCaseOrder);
		distances.clear();
		testCaseOrder.clear();
	}
}

void GetTestCaseOrder(vector<TestCaseDistance> distances, vector<int>& testCaseOrder) {
	sort(distances.rbegin(), distances.rend());
	for (int i = 0; i < distances.size(); i++)
		testCaseOrder.push_back(distances[i].id + 1);
}

int LevensteinDistance(const vector<int> source, const vector<int> target, unsigned int insertCost, unsigned int deleteCost, unsigned int replaceCost) {
	if (source.size() > target.size())
		return LevensteinDistance(target, source, deleteCost, insertCost, replaceCost);

	int min_size = source.size(), max_size = target.size();
	vector<int> levDist(min_size + 1);

	levDist[0] = 0;
	for (int i = 1; i <= min_size; ++i)
		levDist[i] = levDist[i - 1] + deleteCost;

	for (int j = 1; j <= max_size; ++j) {
		int prevDiagonal = levDist[0], prevDiagonalSave;
		levDist[0] += insertCost;

		for (int i = 1; i <= min_size; ++i) {
			prevDiagonalSave = levDist[i];
			if (source[i - 1] == target[j - 1])
				levDist[i] = prevDiagonal;
			else
				levDist[i] = min(min(levDist[i - 1] + deleteCost, levDist[i] + insertCost), prevDiagonal + replaceCost);
			prevDiagonal = prevDiagonalSave;
		}
	}

	return levDist[min_size];
}

void PrintOrderedTestCases(int id, const vector<int> testCaseOrder) {
	cout << "TS" << id << ": ";
	for (int i = 0; i < testCaseOrder.size(); i++)
		cout << testCaseOrder[i] << " ";
	cout << endl;
}

void ReadFile(string fileName, int& maxRunningTime, vector<TestSuite>& testSuites) {
	ifstream testFile(fileName);	// opening the file to read
	string line;
	int lineNo = 0;
	while (getline(testFile, line)) {	// reading the file line by line
		istringstream ss(line);
		lineNo++;
		if (lineNo == 1) {
			string temp, temp2, temp3, temp4;
			int maxAllowedRunningTime;
			ss >> temp >> temp2 >> temp3 >> temp4 >> maxAllowedRunningTime;
			maxRunningTime = maxAllowedRunningTime;
			continue;
		}
		else if (lineNo > 3) {
			int numberOfFreqProfiles = GetNumberOfTestCaseFreqProfiles(line);
			string testSuiteId, freqProfileAsString;
			int bugsDetected, runningTime;
			vector<vector<int>> testCaseFreqProfiles;
			ss >> testSuiteId >> bugsDetected >> runningTime;
			for (int i = 0; i < numberOfFreqProfiles; i++) {
				ss >> freqProfileAsString;
				testCaseFreqProfiles.push_back(ConvertFreqProfileToInt(freqProfileAsString));
			}
			testSuites.push_back(TestSuite(bugsDetected, runningTime, testCaseFreqProfiles));
		}
	}
	return;
}

int GetNumberOfTestCaseFreqProfiles(string line) {
	int i = 0, length = line.length(), numberOfSpaces = 0;
	while (i < length) {
		if (line[i] == ' ')
			numberOfSpaces++;
		i++;
	}
	return numberOfSpaces - 2;
}

vector<int> ConvertFreqProfileToInt(string freqProfile) {
	vector<int> freqProfileAsInt;
	stringstream ss(freqProfile);

	for (int i; ss >> i;) {
		freqProfileAsInt.push_back(i);
		if (ss.peek() == '-')
			ss.ignore();
	}
	return freqProfileAsInt;
}