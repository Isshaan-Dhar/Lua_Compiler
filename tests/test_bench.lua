-- Testing Constant Folding Optimization
-- The compiler should calculate these values at compile time
a = 10 + 20 * 2
b = 100 / (2 + 3)

-- Testing Control Flow
if a then
    print b + 5
end

-- Testing embedded loop structure
while b do
    b = b - 1
end