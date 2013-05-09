all:
	gcc  -c fdatefunc.c
	gcc  test_sun_to_lunar.c fdatefunc.o -o sun_to_lunar
	gcc  test_lunar_to_sun.c fdatefunc.o -o lunar_to_sun
	strip sun_to_lunar lunar_to_sun

clean:
	rm *.o sun_to_lunar lunar_to_sun
