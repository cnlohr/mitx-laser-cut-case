all : case2.svg

case2.svg : gen_svg2
	./$^ > $@

gen_svg2 : gen_svg2.c
	gcc -o $@ $^ -lm

clean :
	rm -rf case2.svg gen_svg2


