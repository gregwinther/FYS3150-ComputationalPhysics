####################################################
#
#  Trying to solve the Poisson equation with Julia
#
#####################################################

using PyPlot

function analytic_solution(x)
    1.0 - (1-exp(-10))*x - exp(-10*x)
end

function input_function(x)
    100*exp(-10*x)
end

# Steps
n = 10

# Command line argument, setting no of steps
if length(ARGS) > 0
    n = parse(Int64, ARGS[1])
end

# Diagonal
bVec = ones(n+2)*2

# Numerical solution
v = zeros(n+2)

# Step size and steps
h = 1.0 / (n + 1.0)
hh = h*h
x = 0:n+1
x = x*h

# Analytic solution and right-hand side
u = zeros(n+2)
f = zeros(n+2)

# Alternative to for-loop, a mapping
u = map(analytic_solution, x)
f = map(x_ -> hh*input_function(x_), x)
#for i in eachindex(x)
#    u[i] = analytic_solution(x[i])
#    f[i] = hh*input_function(x[i])
#end

fTilde = zeros(n+2)

t1 = time_ns()
# Gaussian elimination
# Forward substitution
fTilde[2] = f[2]
for i in 3:n+1
    bVec[i] -= 1/bVec[i-1]
    fTilde[i] = f[i] + fTilde[i-1]/bVec[i-1]
end

# Backward substitution
v[n+1] = fTilde[n+1]/bVec[n+1]
for i in n+1:-1:2
    v[i] = (fTilde[i] + v[i+1])/bVec[i]
end
t2 = time_ns()

elapsed_time = (t2-t1)/1.0e9
println("Elapsed time: ", elapsed_time, " s")

if n < 1.0e6
    plot(x, v, label="Numerical solution")
    plot(x, u, label="Analytical solution")
    legend()
    show()
end