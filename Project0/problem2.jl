# Is this a comment?

import Base

# The forward-euler scheme
function backward(x, f::Function, h=0.1)
    (f(x + h) - f(x)) / h
end

# The midpoint euler scheme
function midpoint(x, f::Function, h=0.1)
    (f(x + h) - f(x - h)) / (2*h)
end

h_start = 1e-8
h_end = 1e-15
h_array = LinRange(h_start, h_end, 10)

println(backward(sqrt(2), atan, 0.001))
println(midpoint(sqrt(2), atan, 0.001))
