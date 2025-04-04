for i in {01..16}; do
  cp ./tests/$i.in ./aventura.in
  cp ./tests/$i.ok ./aventura.ok
  ./aventura
  diff -w ./aventura.out ./aventura.ok
  if [ $? -ne 0 ]; then
    echo "Test $i: WA"
  else
    echo "Test $i: Ok"
  fi
done
