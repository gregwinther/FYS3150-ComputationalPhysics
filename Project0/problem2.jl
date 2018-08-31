# Is this a comment?

import Base
using PyPlot

# The forward-euler scheme
function backward(x, f::Function, h=0.1)
    (f(x + h) - f(x)) / h
end

# The midpoint euler scheme
function midpoint(x, f::Function, h=0.1)
    (f(x + h) - f(x - h)) / (2*h)
end

n = 10
h_start = -1
h_end = -8
h_powers = LinRange(h_start, h_end, n)
h_array = zeros(n)

for i in eachindex(h_array)
    h_array[i] = exp10(h_powers[i])
end

backward_results = zeros(n)
midpoint_results = zeros(n)

for i in eachindex(h_array)
    backward_results[i] = backward(sqrt(2), atan, h_array[i])
    midpoint_results[i] = midpoint(sqrt(2), atan, h_array[i]) 
    i += 1
end

backward_errors = backward_results - ones(n)*(1/3)
for i in eachindex(backward_errors)
    backward_errors[i] = abs(backward_errors[i])
end

plot(h_array, backward_errors, label="Backward errors")
#plot(h_array, midpoint_results)
println(backward_results)
show()