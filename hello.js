let nums = [10, 20, 30, 40]


let new_num = 90

for (let i = 0; i < nums.length; i++) {
	temp = nums[i]
	nums[i] = new_num
	new_num = temp
}

console.log(nums)
