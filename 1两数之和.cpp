class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); i++) {
			map.insert(pair<int, int>(nums[i], i));
		}
		for (int i = 0; i < nums.size(); i++) {
			auto point = map.find(target - nums[i]);
			if (point != map.end() && point->second != i) {
				return {point->second, i};
			}
		}
		return {};
	}
};
