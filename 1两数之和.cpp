class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> map; // 一枚举，一维护，因答案唯一，不用考虑重复
		for (int i = 0; i < nums.size(); i++) {
			map.insert(pair<int, int>(
									  nums[i],
									  i)); // 将原数组放入哈希表，因为要查找的是map的键且元素不同，所以将原数组的值作为键，下标作为值
		}
		for (int i = 0; i < nums.size(); i++) {
			auto point = map.find(target - nums[i]);
			if (point != map.end() && point->second != i) {
				return {point->second, i};
			}
		}
		return {};
	} // 利用哈希表，将第二次查找时间由n变为1
};
