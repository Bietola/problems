aFacts = {}
bFacts = {}
function solve(input, curr, a, b, aFacts, bFacts)
    -- defaults
    a = a or {}
    b = b or {}
    aFacts = aFacts or {}
    bFacts = bFacts or {}

    -- cache things
    local factors = {decompose(input[curr])}
    local inA = any_of(factors, function(ele)
        return aFacts[ele]
    end)
    local inB = any_of(factors, function(ele)
        return bFacts[ele]
    end)

    -- base cases
    if inA and inB then
        return 0
    else
        local numA, numB = 0, 0
        if not inA then
            numB = solve(input, curr + 1, a, b:insert())
        end
        if not inB then

        end
    end
end
