compile: PaillierKeys.cpp PaillierPublicParameters.cpp PaillierAdapter.cpp PaillierPublicParameters.cpp HomomorphicCrypto.cpp AbstractPublicParameters.cpp base64.cpp
	g++ -c -fPIC -std=c++0x base64.cpp -o base64.o
	g++ -c -fPIC -std=c++0x AbstractPublicParameters.cpp -o AbstractPublicParameters.o
	g++ -c -fPIC -std=c++0x PaillierKeys.cpp -o PaillierKeys.o
	g++ -c -fPIC -std=c++0x PaillierPublicParameters.cpp -o PaillierPublicParameters.o
	g++ -c -fPIC -std=c++0x PaillierAdapter.cpp -o PaillierAdapter.o
	g++ -c -fPIC -std=c++0x PaillierPrivateParameters.cpp -o PaillierPrivateParameters.o
	g++ -c -fPIC -std=c++0x HomomorphicCrypto.cpp -o HomomorphicCrypto.o

link: PaillierKeys.o AbstractPublicParameters.o HomomorphicCrypto.o PaillierPrivateParameters.o PaillierPublicParameters.o PaillierAdapter.o PaillierKeys.o base64.o
	g++ -shared -Wl,-soname,libPaillierPublicParameters.so -Wl,--no-undefined -o libPaillierPublicParameters.so AbstractPublicParameters.o PaillierKeys.o PaillierPublicParameters.o -lpython2.7 -lboost_python -lgmp -fopenmp
	g++ -shared -Wl,-soname,libPaillierAdapter.so -Wl,--no-undefined -o libPaillierAdapter.so HomomorphicCrypto.o PaillierPrivateParameters.o PaillierAdapter.o PaillierKeys.o AbstractPublicParameters.o PaillierPublicParameters.o base64.o -lpython2.7 -lboost_python -lgmp -lgmpxx -fopenmp

