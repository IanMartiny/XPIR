compile: PaillierKeys.cpp PaillierPublicParameters.cpp PaillierAdapter.cpp PaillierPublicParameters.cpp HomomorphicCrypto.cpp AbstractPublicParameters.cpp
	g++ -c -fPIC -std=c++0x -lgmpxx AbstractPublicParameters.cpp -o AbstractPublicParameters.o
	g++ -c -fPIC -std=c++0x -lgmpxx PaillierKeys.cpp -o PaillierKeys.o
	g++ -c -fPIC -std=c++0x -lgmpxx PaillierPublicParameters.cpp -o PaillierPublicParameters.o
	g++ -c -fPIC -std=c++0x -lgmpxx PaillierAdapter.cpp -o PaillierAdapter.o
	g++ -c -fPIC -std=c++0x -lgmpxx PaillierPrivateParameters.cpp -o PaillierPrivateParameters.o
	g++ -c -fPIC -std=c++0x -lgmpxx HomomorphicCrypto.cpp -o HomomorphicCrypto.o

link: HomomorphicCrypto.o PaillierPrivateParameters.o PaillierPublicParameters.o PaillierAdapter.o PaillierKeys.o
	g++ -shared -Wl,-soname,libPaillierAdapter.so -Wl,--no-undefined -o libPaillierAdapter.so HomomorphicCrypto.o PaillierPrivateParameters.o PaillierPublicParameters.o PaillierAdapter.o PaillierKeys.o AbstractPublicParameters.o -lpython2.7 -lboost_python -lgmp -fopenmp

