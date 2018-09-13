# I am at it again!
#
# This is a Julia program where I try to diagonalize a matrix
# using Jacobi's method.
#
# Greg Winther

import Base

ITERATION_LIMIT = 10

# We have a matrix
A = Array{Float64}(
    [10 -1 2 0;
     -1 11 -1 3;
     2 -1 01 -1;
     0 3 -1 8])
   
# RHS vector
b = Array{Float64}(
    [6 25 -11 15])

x = zeros(size(b))

for iteration = 1:ITERATION_LIMIT

    global x
    
    println("Current solution: ", x)
    xNew = zeros(size(x))

    # println("Iteration = ", iteration)

    for i = 1:size(A)[1]
        s1 = *(transpose(A[i, 1:i-1]), x[1:i-1])
        # println(A[i, 1:i], "*", x[1:i], "=", s1)
        s2 = *(transpose(A[i, i+1:end]), x[i+1:end])
        # println(A[i, i+1:end], "*", x[i+1:end], "=", s2)
        xNew[i] = (b[i] - s1 - s2) / A[i, i]
    end
       
    if isapprox(x, xNew, atol=1e-10)
        break
    end

    x = xNew
    #println()

end

println("Solution: ")
println(x)
error = *(A, transpose(x)) - transpose(b)
println("Error: ")
println(error)
