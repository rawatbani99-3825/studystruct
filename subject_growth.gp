set title 'Subject-wise Performance'
set ylabel 'Performance (%)'
set yrange [0:115]
set ytics 0,20,100
set xrange [0:3]
set boxwidth 0.6
set style fill solid
set grid y
set xtics rotate by -30 ("english" 1, "dsa" 2)
plot 'subject_growth.dat' using 1:2 with boxes notitle, '' using 1:($2+4):(sprintf("%d%%", $2)) with labels notitle
