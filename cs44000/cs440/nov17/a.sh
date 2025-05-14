for r in  50 100 150 200 250
do
  convert -size 600x600 xc:wheat -strokewidth 10 -stroke red -fill blue -draw "circle 300,300 $r,300" a$r.png
done
