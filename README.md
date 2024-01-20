# Spherix1D
Spherix is a 1D spherical hydro solver designed for studying the shock structure emerging from the interaction between a spherically symmetric wind and an ambient medium with any specified density, velocity and temperature structure.

## Key Highlights

- **Spherical Modeling:** Simulate hydrodynamics in a 1D spherical framework.
- **Shock Structure Study:** Explore and analyze shock structures resulting from wind and ambient medium interaction.

## Euler Equations
SpheriX is based on the spherical symmetric form of the Euler equations, governing fluid dynamics in a 1D radial direction. The set of equations solved by Spherix1D are as follows:

1. **Continuity Equation:**
   $$\ \frac{\partial \rho}{\partial t} + \frac{1}{r^2} \frac{\partial}{\partial r}(r^2 \rho v_r) = 0 \$$

2. **Radial Momentum Equation:**
   $$\ \frac{\partial (\rho v_r)}{\partial t} + \frac{1}{r^2} \frac{\partial}{\partial r}(r^2 \rho v_r^2 + P) = 0 \$$

3. **Energy Equation:**
   $$\ \frac{\partial E}{\partial t} + \frac{1}{r^2} \frac{\partial}{\partial r}\left(r^2 (E + P) v_r\right) = 0 \$$

Where:
- \(\rho\) is the density
- \(v_r\) is the radial velocity component
- \(P\) is the pressure
- \(E\) is the total energy per unit volume
