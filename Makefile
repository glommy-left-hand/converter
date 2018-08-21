all:
	gcc converter.c -o converter -lm
	gcc converter-v1.0.c -o converter-v1.0
	gcc converter-v2.0.c -o converter-v2.0
	gcc converter-v3.0.c -o converter-v3.0 -lpthread
clean:
	rm -f converter converter-v1.0 converter-v2.0 converter-v3.0
test:
	time ./converter 63
	time ./converter-v1.0 10000
	time ./converter-v2.0 10000
	time ./converter-v3.0 10000
