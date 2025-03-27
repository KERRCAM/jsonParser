
build:
	gcc src/*.c -o buildTest/parser

run:
	./buildTest/parser

clean:
	rm buildTest/parser