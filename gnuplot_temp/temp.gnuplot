set term pngcairo font ',7' size 800,600
set out './ECHAIMOutput.png'
unset key
set contour base
set cntrparam levels 10
set cntrparam bspline
unset surface
set view map
set style data lines
set xlabel 'Latitude'
set ylabel 'Altitude'
set zlabel 'Electron Density [10^{11} m^{-3}]'
set title 'Electron Density [10^{11} m^{-3}] - Longitude = 60'
splot 'data.dat' using 1:2:($3/1e11) palette
set out
