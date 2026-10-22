set title 'Overall Progress: 1 of 2 tasks done (50%)'
set size square
set xrange [-1.3:1.3]
set yrange [-1.3:1.3]
unset border
unset tics
unset key
set object 1 circle at 0,0 size 1 arc [0:180] fc rgb 'green' fs solid
set object 2 circle at 0,0 size 1 arc [180:360] fc rgb 'red' fs solid
set label 1 'Completed: 1' at -1.2,-1.2 tc rgb 'dark-green'
set label 2 'Pending: 1' at 0.3,-1.2 tc rgb 'red'
plot NaN notitle
