all:
	gcc src/*.c -Iinclude -o Projeto-PIF

run:
	./Projeto-PIF

clean:
	rm -f Projeto-PIF
