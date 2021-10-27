#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>


using std::cin;
using std::string;
using std::vector;
using std::map;

void SortCharacters(const string& text, vector<int>& order)
{
	vector<int> count(5, 0);
	map<char, int> charToIdx;
	charToIdx['$'] = 0;
	charToIdx['A'] = 1;
	charToIdx['C'] = 2;
	charToIdx['G'] = 3;
	charToIdx['T'] = 4;
	for (int i = 0; i < text.size(); i++)
	{
		count[charToIdx[text[i]]]++;
	}
	for (int i = 1; i < count.size(); i++)
	{
		count[i] += count[i - 1];
	}
	for (int i = text.size() - 1; i >= 0; i--)
	{
		int idx = charToIdx[text[i]];
		count[idx] -= 1;
		order[count[idx]] = i;
	}
}

void ComputeCharlabeles(const string& text, const vector<int>& order, vector<int>& label)
{
	label[order[0]] = 0;
	for (int i = 1; i < text.size(); i++)
	{
		if (text[order[i]] != text[order[i - 1]])
		{
			label[order[i]] = label[order[i - 1]] + 1;
		}
		else
		{
			label[order[i]] = label[order[i - 1]];
		}
	}
}

void SortedDoubled(const string& text, int L, vector<int>& order, const vector<int>& label)
{
	vector<int> newOrder(text.size());
	vector<int> count(text.size(), 0);
	for (int i = 0; i < text.size(); i++)
	{
		count[label[i]]++;
	}
	for (int i = 1; i < count.size(); i++)
	{
		count[i] += count[i - 1];
	}
	for (int i = text.size() - 1; i >= 0; i--)
	{
		int start = (order[i] - L + text.size()) % text.size();
		int cl = label[start];
		count[cl] -= 1;
		newOrder[count[cl]] = start;
	}
	order = newOrder;
}

void Updatelabeles(const vector<int>& newOrder, vector<int>& label, int L)
{
	vector<int> newlabel(newOrder.size());
	newlabel[newOrder[0]] = 0;
	for (int i = 1; i < newOrder.size(); i++)
	{
		int cur = newOrder[i];
		int prev = newOrder[i - 1];
		int mid = cur + L;
		int midPrev = (prev + L) % newOrder.size();
		if (label[cur] != label[prev] || label[mid] != label[midPrev])
		{
			newlabel[cur] = newlabel[prev] + 1;
		}
		else
		{
			newlabel[cur] = newlabel[prev];
		}
	}
	label = newlabel;
}

vector<int> BuildSuffixArray(const string& text) {
	vector<int> result;
	vector<int> order(text.size());
	vector<int> label(text.size());
	SortCharacters(text, order);
	ComputeCharlabeles(text, order, label);
	int L = 1;
	while (L < text.size())
	{
		SortedDoubled(text, L, order, label);
		Updatelabeles(order, label, L);
		L *= 2;
	}
	result = order;
	return result;
}



void FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array, vector<int>& result) {

	int minIndex = 0;
	int maxIndex = text.size();
	while(minIndex < maxIndex)
	{
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag < 0)
		{
			minIndex = midIndex + 1;
		}
		else
		{
			maxIndex = midIndex;
		}

	}

	int start = minIndex;
	maxIndex = text.size();
	while(minIndex < maxIndex)
	{
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag > 0)
		{
			maxIndex = midIndex;
		}
		else
		{
			minIndex = midIndex + 1;
		}

	}

	int end = maxIndex;
	if (start <= end)
	{
		for (int i = start; i < end; i++)
		{
			result.push_back(suffix_array[i]);
		}

	}

}

int main() {
	char buffer[100001];
	scanf("%s", buffer);
	string text = buffer;
	text += '$';
	vector<int> suffix_array = BuildSuffixArray(text);
	int pattern_count;
	scanf("%d", &pattern_count);
	vector<bool> occurs(text.length(), false);
	for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
		scanf("%s", buffer);
		string pattern = buffer;
		vector<int> occurrences;
		FindOccurrences(pattern, text, suffix_array, occurrences);
		for (int j = 0; j < occurrences.size(); ++j) {
			occurs[occurrences[j]] = true;
		}
	}
	for (int i = 0; i < occurs.size(); ++i) {
		if (occurs[i]) {
			printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}