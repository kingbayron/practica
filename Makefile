all: pokestop

%: %.cc
	g++ -std=gnu++11 $< -o $@

%: %.c
	gcc $< -o  $@ -lm

