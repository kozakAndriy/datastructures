mkdir -p ./compiled
rm -r ./compiled/*

for file in ./src/*.c; do
    gcc -c "$file" -o "./compiled/$(basename "${file%.c}.o")"
done

for file in ./tests/*.c; do
    gcc -c "$file" -o "./compiled/$(basename "${file%.c}.o")"
done

gcc -o ./compiled/main ./compiled/*.o

./compiled/main