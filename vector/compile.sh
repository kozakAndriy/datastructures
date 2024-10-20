
mkdir -p ./compiled
rm -r ./compiled/*

for file in ./implementation/*.c; do
    gcc -c "$file" -o "./compiled/$(basename "${file%.c}.o")" -Wno-int-conversion
done

for file in ./tests/*.c; do
    gcc -c "$file" -o "./compiled/$(basename "${file%.c}.o")" -Wno-int-conversion
done

gcc -o ./compiled/main ./compiled/*.o

./compiled/main