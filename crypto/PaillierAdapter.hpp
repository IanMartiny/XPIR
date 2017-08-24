/* Copyright (C) 2014 Carlos Aguilar Melchor, Joris Barrier, Marc-Olivier Killijian
 * This file is part of XPIR.
 *
 *  XPIR is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  XPIR is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XPIR.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEF_PAILLIERADAPTER
#define DEF_PAILLIERADAPTER
static const unsigned int kNumSecurityBits = 80;
#include <fstream>
#include <omp.h>
#include <math.h>
#include <string>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "HomomorphicCrypto.hpp"
#include "PaillierPublicParameters.hpp"
#include "PaillierPrivateParameters.hpp"

#include <boost/python.hpp>
#include <Python.h>
using namespace std;

class PaillierAdapter : public HomomorphicCrypto {

	private:
		/*Attributs*/
		gmp_randstate_t rand;
		int unsigned modulusbits;
		int security_bits;
		PaillierPrivateParameters privateParameters;
	
		/*Methods*/
		void keygen(unsigned int modulusbits,
											paillier_pubkey* pub,
											paillier_prvkey* prv,
											unsigned int s);
		void complete_prvkey( 	paillier_prvkey* prv, 
								paillier_pubkey* pub, 
								unsigned int s );
		void generatePrivateKey(void);
		void generatePublicKey(void);
		void enc(paillier_pubkey* pub,
							mpz_t m,
							unsigned int s,
							mpz_t c
							);
		
		void dec( paillier_pubkey* pub,
							paillier_prvkey* prv,
							mpz_t ct,  
							unsigned int,
							mpz_t i);

		void getRandFromfile( int len, mpz_t* val );
		void getRandInteger(mpz_t rop, unsigned int length, gmp_randstate_t prng);
    void initRandomGenerator();

	public:
		std::string e_add_wrap(std::string ct1, std::string ct2, unsigned int rec_lvl);
		void e_add(mpz_t res, mpz_t a, mpz_t b, int);
		void e_mul_const(mpz_t res, mpz_t a, mpz_t n, int);
		std::string e_mul_wrap(std::string ct1, std::string ct2, unsigned int rec_lvl);
		static unsigned int securityToModulus(int); 
		/*Attributs*/
		PaillierPublicParameters publicParameters;
		
		/*Methods*/
		std::string encrypt1(unsigned int a, unsigned int b);
		std::string encrypt2(char* data, size_t dataSize,  unsigned int exponent);
		char* encrypt(unsigned int ui, unsigned int);
		char* encrypt(char* data, size_t, unsigned int exponent);
	    char* encrypt_perftest();
		char* decrypt(char* cipheredData, unsigned int rec_lvl, size_t, size_t);
		std::string decrypt1(std::string cipheredData, unsigned int rec_lvl, size_t, size_t);
    unsigned int getCryptoParams(unsigned int k,set<std::string>& crypto_params);
    unsigned int getAllCryptoParams(set<std::string>& crypto_params);
    long setandgetAbsBitPerCiphertext(unsigned int elt_nbr);
    std::string getSerializedCryptoParams(bool shortversion);

    PaillierAdapter();
    PaillierAdapter(int security_bits, int recLvl);
		~PaillierAdapter(void);
		
    double estimateAbsTime(std::string crypto_param);
		AbstractPublicParameters& getPublicParameters(void);
		PaillierPublicParameters& getPublicParameters1(void);
		double getDecCost(unsigned int length, unsigned int s);
		void setNewParameters(const std::string& crypto_params);

		void get_prime_of_size(mpz_t rop, unsigned int size);
};
#endif
