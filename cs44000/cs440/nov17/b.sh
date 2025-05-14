for r in 1 2 3 4 5
do
  convert -size 600x600 xc:#000 -channel red -fx "($r*i/w)*($r*j/h)" b$r.png
done
