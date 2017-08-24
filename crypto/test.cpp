#include "PaillierAdapter.hpp"
#include "base64.h"
#include <iostream>
#include <string>
#include <cstdio>

#include <typeinfo>

int main(void){
    PaillierAdapter cryptoMethod(128,1);
    std::string str = "hello";
    // char *ct = cryptoMethod.encrypt(&str[0u], str.length(), 1);
    char *ct = cryptoMethod.encrypt(3,2);
    char *ct2 = cryptoMethod.encrypt(5,2);
    char *ct4 = cryptoMethod.encrypt(3,2);
    cout<<base64_encode(reinterpret_cast<const unsigned char*>(ct), strlen(ct))<<endl;
    cout<<base64_encode(reinterpret_cast<const unsigned char*>(ct), strlen(ct4))<<endl;

    char *pt = cryptoMethod.decrypt(ct, 2, cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8, cryptoMethod.getPublicParameters().getAbsorptionBitsize(1)/8);
    std::cout<<cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8<<std::endl;
    std::cout<<cryptoMethod.getPublicParameters().getAbsorptionBitsize(1)/8<<std::endl;
    int i;
    for (i=0; i<cryptoMethod.getPublicParameters().getAbsorptionBitsize(1)/8; i++) {
        printf("%02x ", (unsigned char)pt[i]);
    }
    cout<<endl;

    // for (i=0; i<cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8; i++) {
    //     printf("%02x ", (unsigned char)ct[i]);
    // }

    mpz_t res, a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_init(res);
    // cout<<"strlen(ct) = "<<strlen(ct)<<endl;
    mpz_import(a, cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8, 1, sizeof(char), 0, 0, ct);
    // cout<<"convert ct to a, result : "<<a<<endl;
    mpz_import(b, cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8, 1, sizeof(char), 0, 0, ct2);
    // int init_s = ((PaillierPublicParameters*) &(cryptoMethod.getPublicParameters())).getPubKey()->getinit_s();
    // ((PaillierPublicParameters) cryptoMethod.getPublicParameters()).getPubKey();
    // cout<< typeid(cryptoMethod.getPublicParameters()).name()<<endl;
    int init_s = (*((PaillierPublicParameters*) &(cryptoMethod.getPublicParameters()))).getPubKey()->getinit_s();
 
    // cout<<"init_s = "<<init_s<<endl;

    int dim = 1;
    cryptoMethod.e_add(res, a, b, init_s+1+dim);
    char *ct3 = (char*)mpz_export(NULL, NULL, 1, sizeof(char) , 0, 0, res);
    char *pt2 = cryptoMethod.decrypt(ct3, 1, cryptoMethod.getPublicParameters().getCiphBitsizeFromRecLvl(2)/8, cryptoMethod.getPublicParameters().getAbsorptionBitsize(1)/8);

    for (i=0; i<cryptoMethod.getPublicParameters().getAbsorptionBitsize(1)/8; i++) {
        printf("%02x ", (unsigned char)pt2[i]);
    }
    cout<<endl;

    mpz_clears(a, b, res, NULL);
    
    return 0;
}