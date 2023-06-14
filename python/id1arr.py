from typing import List


class Solution643: # ERROR
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        n = len(nums)
        sum_ = sum(nums[:k])
        ans = sum_
        
        for i in range(k, n): 
            sum_ = ans + nums[i] - nums[i - k]
            if sum_ > ans:
                ans = sum_ 

        return ans / k


def main():
    so = Solution643()
    nums = [1,12,-5,-6,50,3]
    k = 4
    res = so.findMaxAverage(nums, k)
    print(res)
    
    
if __name__ == '__main__':
    main()