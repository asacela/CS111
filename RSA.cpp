#include<iostream>
#include<fstream>
#include<math.h>
#include <string>

using namespace std;

void partA(long int& e, long int& n);

void encrypt(string fileName, long int e, long int n);
void decrypt(long int e, long int n);

long int CalcD(long int e, long int n);
bool isPrime(long int);
long int randPrime();
int gcd(int,int);
int phi(int);

long int encodingSchema(char x);
char decodingSchema(int x);

int main(int argc, char *argv[]){

  int e = stoi(argv[1]);
  int n = stoi(argv[2]);

  string fileName = argv[4];


  cout << "Arguments Received -- \n";
  cout << "E: " << e << endl;
  cout << "N: " << n << endl;
  cout << "Encrypt/Decrypt: " << argv[3] << endl;
  cout << "File Name: " << fileName << endl;

  bool encryptFlag = false;
  bool decryptFlag = false;

  if(strcmp(argv[3], "e") == 0){

    encryptFlag = true;
  }
  else if(strcmp(argv[3], "d") == 0){

    decryptFlag = true;
  }
  else{

    //Error
  }

  cout << "Welcome to the RSA encryption & decryption system." << endl << endl;

  if(encryptFlag == true){

    encrypt(fileName, e, n);
  }
  else if(decryptFlag == true){

    //decrypt(e,n);
  }
  else{

    //Error
  }

  return 0;
}

void partA(long int& e, long int& n){
  bool cont = true;
  while(cont){
    cont = false;
    cout << "Enter a two integer PUBLIC key (e,n):" << endl;
    cin >> e >> n;
    cout << endl;
    if(gcd(e,phi(n)) != 1){
      cout << "Uh oh, it looks like your public key is invalid." << endl;
      cont = true;
    }
    else{
      cout << "Thank you!" << endl;
    }
    cout << endl;
  }
}

void encrypt(string InputFile, long int e, long int n){
  cout << "-- ENCRYPTION --" << endl;

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

  cout << "Writing to Output File...\n";
  while(ifs >> letter){

    encoded = encodingSchema(letter);
    int result = encoded;

    for(int i = 0; i < e-1 ; i++){

      result = (encoded * result) % n;

    }
    
    ofs << result << " "; 
  }

  ifs.close();
  ofs.close();
}

void decrypt(long int e, long int n){
  cout << "-- DECRYPTION --" << endl;
  cout << "Enter your file name." << endl;
  ifstream ifs;
  string InputFile;
  cin >> InputFile;
  ifs.open(InputFile);
  if(!ifs.is_open()){
    cout << "ERROR opening " << InputFile << endl;
    exit(1);
  }

  cout << "Breaking RSA..." << endl;
  cout << "Find d..." << endl;
  long int d = CalcD(e,n);
  cout << d;
  ofstream ofs;;
  ofs.open("decrypted.txt");


  int num;
  while(ifs >> num){


  }


  ifs.close();
  ofs.close();
}

// Helper functions
long int CalcD(long int e, long int n){
  // Find p and q
  int p,q;
  for(long int i = 2; i*i <= n; ++i){
    if(isPrime(i)){
      if(isPrime(n/i)){
        p = i;
        q = n/i;
        break;
      }
    }
  }
  long int phiN = (p-1)*(q-1);
  long int a,b = 1;
  while(a*e == b*phiN + 1){
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

long int randPrime(){
  long int n = rand();
  while(!isPrime(n)){
    n = rand();
  }
  return n;
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

  long int myInt = int(x) - 63;

  return myInt;
}

char decodingSchema(int x){

  char myChar = char(x + 63);

  return myChar;
}

