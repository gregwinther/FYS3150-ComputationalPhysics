using PyPlot
using PyCall
using ODE
@pyimport matplotlib.animation as anim
@pyimport mpl_toolkits

# The y-array has shape: [position i, velocity i]

function F(t, y)

    # Number of planets
    n = int(length(y) / 6)

    # Extract current position and velocity
    r = zeros(n, 3)
    v = zeros(n, 3)

    for i=1:n
        r[i, :] = y[(i-1)*6 + 1:(i-1)*6 + 3]
        v[i, :] = y[(i-1)*6 + 1:(i-1)*6 + 6]
    end

    # Calculate spatial derivatives
    drdt = v

    # Work out velocity derivatives = accelerations
    dvdt = zeros(n, 3)
    for i = 1:n
        for j = 1:n
            if  i != j
                dvdt[i, :] += -G*m[j]*(r[i, :] - r[j, :]) / (norm(r[i, :] - r[j, :])^3)
            end
        end
    end

    # Combine into dydt
    dydt = zeros(6*n)
    for i = 1:n
        dydt[6(i-1)+1] = drdt[i,1]
        dydt[6(i-1)+2] = drdt[i,2]
        dydt[6(i-1)+3] = drdt[i,3]
        dydt[6(i-1)+4] = dvdt[i,1]
        dydt[6(i-1)+5] = dvdt[i,2]
        dydt[6(i-1)+6] = dvdt[i,3]
    end
    return dydt
end


