/*

Justin Gomez      SID: 862035390

Alec Asatoorian   SID: 862026505

*/
#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<stdio.h>
#include<string.h>
#include<cstring>

using namespace std;

void encrypt(string fileName, long int e, long int n);
void decrypt(string fileName, long int e, long int n);
long int CalcD(long int e, long int n, int& p,int& q);
bool isPrime(long int);
int gcd(int,int);
int phi(int);

long int encodingSchema(char x);
char decodingSchema(int x);

int main(int argc, char *argv[]){

  int e = stoi(argv[1]);
  int n = stoi(argv[2]);

  string fileName = argv[4];

  //Switch e and n if e is greater than n
  if(e > n){

    int temp = e;
    e = n;
    n = temp;
  }


  cout << "Arguments Received -- \n";
  cout << "E: " << e << endl;
  cout << "N: " << n << endl;
  cout << "Encrypt/Decrypt: " << argv[3] << endl;
  cout << "File Name: " << fileName << endl << endl;

  if((e >= n) || (gcd(e,phi(n)) != 1)){
    cout << "Uh oh, it looks like your public key is invalid." << endl;
    exit(1);
  }



  if(strcmp(argv[3], "e") == 0){
    encrypt(fileName, e, n);

  }
  else if(strcmp(argv[3], "d") == 0){
    decrypt(fileName, e, n);

  }
  else{
    cout << "Invalid option." << endl;
    //Error
  }

  return 0;
}

void encrypt(string InputFile, long int e, long int n){
  cout << "-- ENCRYPTING --" << endl;

  ifstream ifs;
  ifs.open(InputFile);
  if(!ifs.is_open()){
    cout << "ERROR opening " << InputFile << endl;
    exit(1);
  }

  ofstream ofs;
  ofs.open("incrypted.txt");

  int encoded;
  char letter;

  cout << "Writing to Output File (incrypted.txt)...\n";
  ifs >> std::noskipws;
  while(ifs  >> letter){

    encoded = encodingSchema(letter);
    int result = 1;
    // cout << result <<",";

    for(int i = 0; i < e; i++){

      result = (encoded * result) % n;
      // cout << result <<",";
    }
    cout << letter << ": " << encoded <<" -> "<< result << endl; //---------------------------------------

    ofs << result << " ";
  }

  ifs.close();
  ofs.close();
}


void decrypt(string InputFile, long int e, long int n){


  cout << "-- DECRYPTION --" << endl;

  ifstream ifs;
  ifs.open(InputFile);
  if(!ifs.is_open()){
    cout << "ERROR opening " << InputFile << endl;
    exit(1);
  }
  ofstream ofs;
  ofs.open("decrypted.txt");

  cout << "BREAKING RSA..." << endl;



  long int d;
  int p=0;
  int q=0;
  d = CalcD(e, n, p ,q);

  cout << "Secret key (d,e): ("  << d << "," << e << ")" << endl;
  cout << "p: " << p << endl << "q: " << q << endl;



  int num;
  cout << "Decrypting to Output File (decrypted.txt)...\n";


  while(ifs >> num){
    int C = 1;
    for(int i = 0; i < d; ++i){

      C = (C * num) % n;
    }
    cout << num <<" -> "<< C << ": " << char(C) <<endl;   //-----------------------------
    ofs << decodingSchema(C);
  }

  ifs.close();
  ofs.close();
}

// Helper functions
long int CalcD(long int e, long int n, int& p, int& q){
  // Find p and q
  bool done = false;
  for(long int i = 2; (i <= n) && (!done); ++i){
    if(isPrime(i)){
      double ntemp= n;
      double itemp = i;
      double temp = ntemp/itemp;

      if(fmod(temp,1) == 0){

        if(isPrime(int(temp))){

          p = int(i);
          q = int(n/i);
          done = true;

        }

      }
    }
  }
  
  long int phiN = (p-1)*(q-1);
  long int a = 1;
  long int b = 1;

  while(a*e != b*phiN + 1){
    if(a*e > b*phiN + 1){
      ++b;
    }
    else if(a*e < b*phiN + 1){
      ++a;
    }
  }
  return a;
}

bool isPrime(long int n){
  if(n <= 1){ return false; }
  for(long int i = 2; i*i <= n; ++i){
    if(n%i == 0){
      return false;
    }
  }
  return true;
}

int gcd(int a,int b){
  if(a >= 0){
    if(a == 0){ return b; }
    else if(b == 0){ return a; }
    if(a == b){
      return a;
    }
    if(a < b){
      std::swap(a,b);
    }
    return gcd(a-b,b);
  }
  return gcd(b,-a);
}

int phi(int n){
  int total = 1;
  for(int i = 2; i < n; ++i){
    if(gcd(i,n) == 1){
      ++total;
    }
  }
  return total;
}

long int encodingSchema(char x){

  long int myInt = int(x);

  return myInt;
}

char decodingSchema(int x){

  char myChar = char(x);

  return myChar;
}
