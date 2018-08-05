function solve(board)
	local even = #board % 2
	local prev
	for _,row in ipairs(board) do
		for _,ele in ipairs(row) do
			if prev == nil then 
				prev = ele
			elseif prev == ele then
				return false
			end
		end
		prev = even and (prev + 1) or prev
		prev = prev % 2
	end
	return true
end

tst = {{0, 1}, {1, 0}}
print(solve(tst))
