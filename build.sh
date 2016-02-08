#! /bin/sh

mkdir build
cd build
cmake ..

make

lcov --zerocounters --directory .
lcov --capture --initial --directory . --output-file app

./tests/test001
./tests/test002

for i in ../tests/samples/*.bson; do
	./bin/bson $i
done

lcov --no-checksum --directory . --capture --output-file app.info
genhtml app.info -o genhtml
