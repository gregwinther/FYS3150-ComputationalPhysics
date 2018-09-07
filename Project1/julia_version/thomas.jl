####################################################
#
#    Trying to solve the Poisson equation with Julia
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
n = 100

# Diagonal
bVec = ones(n+2)*2

# Numerical solution
v = zeros(n+2)

# Step size and Steps
h = 1.0 / (n + 1.0)
hh = h*h # Don't need this??
x = 1:n+2
x = x*h

# Analytic solution and right-hand side
u = zeros(n+2)
f = zeros(n+2)
for i in eachindex(x)
    u[i] = analytic_solution(x[i])
    f[i] = h*h*input_function(x[i])
end

fTilde = zeros(n+2)

# Gaussian elimination
# Forward substitution
fTilde[2] = f[2]
for i in 3:n+1
    bVec[i] -= 1/bVec[i-1]
    fTilde[i] = (f[i] + fTilde[i-1])/bVec[i]
end

# Backward substitution
v[n+1] = fTilde[n+1]/bVec[n+1]
for i in n:-1:2
    v[i] = (fTilde[i] + v[i+1])/bVec[i]
end

plot(x, v, label="Numerical solution")
plot(x, u, label="Analytical solution")
legend()
show()