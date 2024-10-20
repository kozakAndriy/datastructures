mkdir -p ./compiled
rm -r ./compiled/*

for file in ../vector/implementation/*.c; do
    gcc -o "./compiled/vector_$(basename "${file%.c}.o")" -c "$file"
done

for file in ./src/*.c; do
    gcc -o "./compiled/$(basename "${file%.c}.o")" -c "$file"
done

for file in ./tests/*.c; do
    gcc -o "./compiled/$(basename "${file%.c}.o")" -c "$file" -Wno-int-conversion
done


gcc -o ./compiled/main ./compiled/*.o

./compiled/main