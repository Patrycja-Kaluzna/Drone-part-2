CXXFLAGS = -g -Iinc -Wall -pedantic -std=c++11

__start__: ./dron_etap_1
	./dron_etap_1

./dron_etap_1: obj/main.o obj/lacze_do_gnuplota.o obj/odcinek.o obj/powierzchnia.o obj/powierzchnia_wody.o\
			   obj/powierzchnia_dna.o obj/wieloscian.o obj/prostopadloscian.o obj/dron.o obj/scena.o  
	g++ -Wall -pedantic -std=c++11 -o ./dron_etap_1 obj/main.o obj/lacze_do_gnuplota.o obj/odcinek.o obj/powierzchnia.o\
			   obj/powierzchnia_wody.o obj/powierzchnia_dna.o obj/wieloscian.o obj/prostopadloscian.o obj/dron.o obj/scena.o 

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh 
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh inc/scena.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/odcinek.o: src/odcinek.cpp inc/odcinek.hh inc/SWektor.hh
	g++ -c ${CXXFLAGS} -o obj/odcinek.o src/odcinek.cpp

obj/powierzchnia.o: src/powierzchnia.cpp inc/powierzchnia.hh inc/odcinek.hh
	g++ -c ${CXXFLAGS} -o obj/powierzchnia.o src/powierzchnia.cpp

obj/powierzchnia_wody.o: src/powierzchnia_wody.cpp inc/powierzchnia_wody.hh inc/powierzchnia.hh
	g++ -c ${CXXFLAGS} -o obj/powierzchnia_wody.o src/powierzchnia_wody.cpp

obj/powierzchnia_dna.o: src/powierzchnia_dna.cpp inc/powierzchnia_dna.hh inc/powierzchnia.hh
	g++ -c ${CXXFLAGS} -o obj/powierzchnia_dna.o src/powierzchnia_dna.cpp

obj/wieloscian.o: src/wieloscian.cpp inc/wieloscian.hh inc/powierzchnia.hh inc/SMacierz.hh
	g++ -c ${CXXFLAGS} -o obj/wieloscian.o src/wieloscian.cpp

obj/prostopadloscian.o: src/prostopadloscian.cpp inc/prostopadloscian.hh inc/wieloscian.hh
	g++ -c ${CXXFLAGS} -o obj/prostopadloscian.o src/prostopadloscian.cpp

obj/dron.o: src/dron.cpp inc/dron.hh inc/wieloscian.hh inc/prostopadloscian.hh
	g++ -c ${CXXFLAGS} -o obj/dron.o src/dron.cpp

obj/scena.o: src/scena.cpp inc/scena.hh inc/powierzchnia_wody.hh inc/powierzchnia_dna.hh inc/dron.hh inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/scena.o src/scena.cpp

clean:
	rm -f obj/*.o ./dron_etap_1