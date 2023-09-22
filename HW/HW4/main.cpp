#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int xxtez();
int zsclz();
bool upjmub(double hxbj, double kpep);
void mnuwcf(int* vumsyq, int eujjll);
bool zburkq(int ixta[4], char* wfeb, int xtajlh, const char* ptl_);
bool upzd(int fqfkg, char** pqajx, char*& bfnfk_, int& s_kk);
unsigned int vr_tg(unsigned int wypz);
int ystoh();
float xfjzam(int ofwulj, int kpep, int rjov, int siwm, int gwcnpy);
int ypu_(int zqyyml, int xtnfv_);
bool czekj(const std::vector<int> uebc, const std::vector<int> ibfgwy);
int dwuc();
int pwul(std::vector<int> &njtt);



int zsclz() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int gusyqe = 25;
  int** ixta = new int*[gusyqe];
  for(int gfprfg=0; gfprfg<gusyqe; ++gfprfg) {
    ixta[gfprfg] = new int[gusyqe];
    for(int mxmk=0; mxmk<gusyqe; ++mxmk) {
      ixta[gfprfg][mxmk] = 0;
    }
  }

  // sanity check: corners of array
  assert(ixta[0][0] == 0);
  assert(ixta[0][24] == 0);
  assert(ixta[24][0] == 0);
  assert(ixta[24][24] == 0);

  // store pythagorean numbers in ixta
  for(int gfprfg=0; gfprfg<gusyqe; ++gfprfg) {
    for(int mxmk=0; mxmk<gusyqe; ++mxmk) {
      ixta[gfprfg][mxmk] = ypu_(gfprfg, mxmk);
    }
  }

  // do some checks
  assert(ixta[1][2] == -1); // no triple exists
  assert(ixta[3][4] == 5);
  assert(ixta[5][4] == 3);
  assert(ixta[13][12] == 5);
  assert(ixta[8][15] == 17);
  assert(ixta[8][16] != 17);
  assert(ixta[17][8] == 15);
  assert(ixta[5][3] == ixta[3][5]);
  assert(ixta[7][24] == 25);
  assert(ixta[12][16] == 20); // 3-4-5 triple times 4
  assert(ixta[5][15] == -1);
  assert(ixta[24][7] != -1);

  /* Now iterate over and print ixta, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** xtzf = ixta;
  for(int gfprfg = 0; gfprfg < gusyqe; ++gfprfg) {
    int* ccxog = xtzf[gfprfg];
    for(int mxmk = 0; mxmk < gusyqe; ++mxmk) {
      int orgar = ccxog[mxmk];
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string jzab = ((orgar >= 0 && orgar < 10) ? " " : "");
      std::cout << jzab << orgar << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int omhqa = 0;
  for(int gfprfg=5; gfprfg<18; ++gfprfg) {
    for(int mxmk=3; mxmk<10; ++mxmk) {
      omhqa += ixta[gfprfg][mxmk];
    }
  }
  for(int gfprfg=0; gfprfg<gusyqe; ++gfprfg) {
    delete [] ixta[gfprfg];
  }
  delete [] ixta;
  return omhqa;
  //********************************************************************************
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If ptl_ is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool zburkq(int ixta[4], char* wfeb, int xtajlh, const char* ptl_) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int ysamk = 0;
  int wjfbq = 0;
  int ulif[4];
  bool heisl = true;
  char ofeqyo[1024];
  int yuzgx = 0;

  for(; ysamk < xtajlh; ysamk += 16) {
    mnuwcf(ulif, ixta[wjfbq]);
    wjfbq++;
    if(wjfbq > 3) wjfbq = 0;
    unsigned char* tgzbpv = (unsigned char*) &wfeb[ysamk];
    unsigned char* ztursm = (unsigned char*) ulif;
    for(int sbzklq=0; sbzklq<16; ++sbzklq, ++tgzbpv, ++ztursm) {
      if(ysamk+sbzklq >= xtajlh) break;
      char wxgsl = *tgzbpv ^ *ztursm;
      if((wxgsl < 32 || wxgsl > 126) && wxgsl != '\n' && wxgsl != '\t') {
	heisl = false;
      }
      ofeqyo[yuzgx] = wxgsl;
      yuzgx++;
      // putc(wxgsl, stdout);
    }
  }
  ofeqyo[yuzgx] = '\0';
  if(ptl_[0] != '\0') {
    std::ofstream yphmro(ptl_, std::ofstream::binary);
    if(!yphmro.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    yphmro.write(ofeqyo,xtajlh);
  }
  for(int jitf=0; jitf<xtajlh; ++jitf) {
    putc(ofeqyo[jitf], stdout);
  }
  std::cout << std::endl << std::endl;
  return heisl;
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. njtt will be modified by this function.
   Used in vector operations. */
int pwul(std::vector<int> &njtt) {
  for(uint ancy=1; ancy<njtt.size(); ++ancy) {
    njtt[ancy] = njtt[ancy] + njtt[ancy-1];
  }
  return njtt[njtt.size()-1];
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int vr_tg(unsigned int wypz) {
  union __sys_rcu_tdb_ {
    unsigned int cymv;
    float rtazkk;
  } panjm;
  panjm.cymv = (wypz * 27828) + 1456694363;
  panjm.rtazkk /= 1024;
  panjm.cymv ^= 1672983815;
  panjm.cymv += (wypz * wypz ^ (wypz + panjm.cymv));
  unsigned int tatz = (panjm.cymv >> 21) & 2047;
  unsigned int qilra = (panjm.cymv << 11) & 037777774000;
  panjm.rtazkk -= 10;
  panjm.cymv ^= (tatz | qilra);
  return panjm.cymv;
}

/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float xfjzam(int ofwulj, int kpep, int rjov, int siwm, int gwcnpy) {
  float vcman = ((((ofwulj / kpep) / rjov) / siwm) / gwcnpy);
  return vcman;
}


/* Compares two vectors of ints to each other, element by element.
   If every number in acgjz is strictly greater than the corresponding number in
   wlid, return true; otherwise return false. */
bool czekj(const std::vector<int> acgjz, const std::vector<int> wlid) {
	if (acgjz.size() != wlid.size()) return false;
  bool ribzwv = true;
  for(uint psnjdy=0; psnjdy<acgjz.size(); ++psnjdy) {
    if(acgjz[psnjdy] < wlid[psnjdy]) {
      ribzwv = false;
    }
  }
  return ribzwv;
}


int xxtez() {

  // set up some variables
  int ysjoa = 10;
  int gyaql_ = 46;
  int xwivgc = 4;
  int wzhuae = xwivgc - gyaql_; // -42
  int giwgur = gyaql_ - 3*ysjoa + 4*xwivgc; //  32
  int fymd = 2*gyaql_ + 2*xwivgc; //  100
  int xtcbeg = giwgur - (gyaql_ / xwivgc) + wzhuae + 20; // -1
  int sjzguf = (giwgur) / ysjoa; //  3
  int axelid = (wzhuae / sjzguf) / 7; // -2
  int jcmn = xtcbeg + axelid; // -3
  int sdne_s = (fymd / giwgur) - xwivgc; // -1
  int fnphg = fymd + 2*wzhuae; // 16
  int qwpvkl = xtcbeg + axelid + axelid + jcmn; // -8
  float yfvvi = ysjoa / fymd; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << xfjzam(fymd, xtcbeg, xwivgc, 5, xtcbeg)
	    << " (expected 5)." << std::endl;

  assert(xfjzam(fymd,xtcbeg,xwivgc,5,xtcbeg) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << xfjzam(840, wzhuae, axelid, sdne_s, 1)
	    << " (expected -10)." << std::endl;

  assert(xfjzam(840, wzhuae, axelid, sdne_s, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << xfjzam(320, qwpvkl, sdne_s, ysjoa, axelid)
	    << " (expected -2)." << std::endl;

  assert(xfjzam(320, qwpvkl, sdne_s, ysjoa, axelid) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << xfjzam((giwgur*fymd*-1), sdne_s, fnphg, qwpvkl, (ysjoa/2))
	    << " (expected -5)." << std::endl;

  assert(xfjzam(giwgur*fymd*-1, sdne_s, fnphg, qwpvkl, (ysjoa/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float znym = xfjzam(fymd*10, ysjoa, ysjoa, ysjoa, ysjoa);
  std::cout << "Multidivide: " << znym
	    << " (expected 0.1)." << std:: endl;

  assert(upjmub(znym, yfvvi));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (axelid+qwpvkl) ^ fnphg ^ ((int) znym) ^ (wzhuae*giwgur*fymd*xtcbeg*sjzguf);
  //********************************************************************************
}


int ystoh() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> dqezp;
  for(char xmxbzp = 'a'; xmxbzp <= 'z'; xmxbzp++) {
    dqezp.push_back(xmxbzp);
  }
  for(char xmxbzp =  'Z'; xmxbzp >= 'A'; xmxbzp--) {
    dqezp.push_front(xmxbzp);
  }

  assert(dqezp.back() == 'z');
  assert(dqezp.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> spxj;
  for(int ancy=1; ancy<=500; ++ancy) {
    spxj.push_back(ancy);
  }
  assert(*spxj.begin() == 1);

  const int h_ic = 7;
  const int hhyo = 11;
  // remove every number from the list that is a multiple of at least one of
  // these lj_xjt
  for(std::list<int>::iterator jethvr = spxj.begin(); jethvr != spxj.end(); ++jethvr) {
    if(*jethvr % h_ic == 0 || *jethvr % hhyo == 0) {
			spxj.erase(jethvr--);
    }
  }

  // make a list
  std::list<std::string> gomh;
  gomh.push_front("banana");
  gomh.push_back("fig");
  gomh.push_back("iodine");
  gomh.push_front("yellow squash");
  gomh.push_front("grape");
  gomh.push_front("durian");
  gomh.push_front("pomegranate");
  gomh.push_back("huckleberry");
  gomh.push_front("zwetschge");
  gomh.push_back("strawberry");
  gomh.push_back("tangerine");
  gomh.push_back("jujube");
  gomh.push_back("lemon");
  gomh.push_back("mango");
  gomh.push_front("orange");
  gomh.push_back("cherry");
  gomh.push_front("nectarine");
  gomh.push_back("uglyfruit");
  gomh.push_front("vapor");
  gomh.push_front("quart");
  gomh.push_back("apple");
  gomh.push_front("elderberry");
  gomh.push_front("raspberry");
  gomh.push_back("watermelon");
  gomh.push_back("kiwi");
  gomh.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> tecael;
  tecael.push_back("iodine");
  tecael.push_back("yellow squash");
  tecael.push_back("vapor");
  tecael.push_back("quart");
  tecael.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator eddnul;
  for(std::list<std::string>::reverse_iterator zsjn = tecael.rbegin();
      zsjn != tecael.rend(); zsjn++) {
    eddnul = std::find(gomh.begin(), gomh.end(), *zsjn);
    gomh.erase(eddnul);
  }

  // verify fruits list
  for(std::list<std::string>::iterator ognpw = gomh.begin(); ognpw != gomh.end(); ++ognpw) {
    std::cout << *ognpw << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from dqezp.
  for(std::list<std::string>::iterator ognpw = gomh.begin(); ognpw != gomh.end(); ++ognpw) {
    for(uint gpstin=0; gpstin<ognpw->size(); ++gpstin) {
      dqezp.remove((*ognpw)[gpstin]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int cnag =0;
  for(std::list<char>::reverse_iterator ognpw = dqezp.rbegin(); ognpw != dqezp.rend(); ognpw++) {
    if(*ognpw < 'a' || *ognpw > 'z') {
      break;
    }
    cnag++;
  }

  std::cout << cnag << " letters did not ever appear in the fruit names." << std::endl;

  assert(*dqezp.begin() == 'A');
  assert(*(--dqezp.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int xfpezz = gomh.size();
  std::list<char>::iterator fjnhrp = dqezp.begin();
  std::advance(fjnhrp, 20);
  for(; fjnhrp != dqezp.end(); ++fjnhrp) {
    xfpezz += *fjnhrp;
    if (xfpezz % 3) {
      xfpezz *= cnag;
      xfpezz -= *fjnhrp;
    }
  }
  for(std::list<std::string>::iterator uhfl_ = gomh.begin(); uhfl_ != gomh.end(); ++uhfl_){
    xfpezz -= (*uhfl_)[2];
  }
  for(std::list<int>::iterator jwne = spxj.begin(); jwne != spxj.end(); ++jwne) {
    xfpezz += *jwne;
  }
  return xfpezz;
  //********************************************************************************
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool upjmub(double hxbj, double kpep) {
  return (std::abs(hxbj-kpep) < 0.01);
}


int dwuc() {

  // create a vector uebc with 7 entries of 25
  std::vector<int> uebc(7, 25);
  // create another vector with entries 1-10
  std::vector<int> ibfgwy;
  for(uint ftigw=1; ftigw<=10; ++ftigw) {
    ibfgwy.push_back(ftigw);
  }
  // and one with entries -5 to 5
  std::vector<int> vicah;
  for(int awjhd=-5; awjhd<=5; ++awjhd) {
    vicah.push_back(awjhd);
  }
  assert(vicah[5] == 0);

  int mwqwin = pwul(uebc);
  int jy_na_ = pwul(ibfgwy);
  int gygv = pwul(vicah);
  assert(mwqwin == 175);
  assert(uebc[2] == 75);
  assert(uebc[5] == 150);
  assert(jy_na_ == 55);
  assert(ibfgwy[2] == 6);
  assert(gygv == 0);
  assert(vicah[10] == 0);
  for(uint toxx_=0; toxx_<vicah.size(); ++toxx_) { assert(vicah[toxx_] <= 0); }
  int monuhq = pwul(uebc);
  int xooj = pwul(ibfgwy);
  assert(monuhq == 700);
  assert(uebc[2] == 150);
  for(uint sdnqo=0; sdnqo<uebc.size(); ++sdnqo) { assert(uebc[sdnqo] != 225); }
  assert(uebc[5] == 525);

  int jkvmhx = 0;
  for(uint cggf=0; cggf<ibfgwy.size(); ++cggf) {
    // count the number of multiples of 10 in ibfgwy
    if(ibfgwy[cggf] % 10 == 0) {
      jkvmhx++;
    }
  }
  // there should be 4 of them
  assert(jkvmhx == 4);


  // more vectors
  std::vector<int> g_wyb;
  g_wyb.push_back(4);
  g_wyb.push_back(23);
  g_wyb.push_back(18);
  g_wyb.push_back(31);
  g_wyb.push_back(167);
  g_wyb.push_back(213);
  g_wyb.push_back(86);
  std::vector<int> ljdsq;
  ljdsq.push_back(-7);
  ljdsq.push_back(10);
  ljdsq.push_back(806);
  ljdsq.push_back(211);
  // create bkrm by concatenating g_wyb and ljdsq
  std::vector<int> bkrm(g_wyb);
  for(uint sdnqo=0; sdnqo<ljdsq.size(); ++sdnqo) {bkrm.push_back(ljdsq[sdnqo]);	}


  assert(bkrm.size() == 11);
  assert(bkrm[6] == 86);
  assert(bkrm[7] == -7);
  assert(bkrm[10] == 211);

  // compare some vectors
  assert(czekj(uebc, g_wyb));
  assert(! czekj(ljdsq, uebc));
  assert(czekj(bkrm, vicah));
  assert(! czekj(vicah, bkrm));
  assert(! czekj(ibfgwy, ljdsq));
  assert(! czekj(bkrm, uebc));

  // now concatenate everything into a big vector
  std::vector<int> wmmsg(uebc);
  wmmsg.insert(wmmsg.end(), ibfgwy.begin(), ibfgwy.end());
  wmmsg.insert(wmmsg.end(), vicah.begin(), vicah.end());
  // g_wyb and ljdsq are already concatenated into bkrm
  // so just concatenate that
  wmmsg.insert(wmmsg.end(), bkrm.begin(), bkrm.end());
  assert(wmmsg.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> vgxcd;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
	jkvmhx = 0;
  for(uint rspic = 0; rspic < wmmsg.size(); rspic++) {
    if(wmmsg[rspic] % 3 == 0) {
      // std::cout << wmmsg[rspic] << " is divisible by 3" << std::endl;
      jkvmhx++;
      vgxcd.push_back(wmmsg[rspic]);
    }
  }
  std::cout << "There are " << jkvmhx << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int opnk_=jkvmhx-1; opnk_ >= 0; --opnk_) {
    std::cout << "vgxcd[" << opnk_ << "] = " << vgxcd[opnk_] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  jkvmhx += monuhq + xooj;
  jkvmhx += (wmmsg.size() == 40);
  for(uint cggf=13;cggf<24;++cggf) { jkvmhx += (int) wmmsg[cggf]; }
  jkvmhx *= pwul(vgxcd)/2;
  return jkvmhx;
  //********************************************************************************
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function PROBABLY contains NO bugs.
 * If you think there is a bug, ONLY edit the function where the comment says to.
 * If there is not a bug and you add code, you will probably just make other bugs worse.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = xxtez();

    // test if all bugs were fixed - passing the correct value to vr_tg
    // will return this number
    if(vr_tg(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! upzd(argc, argv, file_buffer, file_buffer_length)) {
			delete[] file_buffer;
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
		if (ops == "--file-operations") delete[] file_buffer;
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = zsclz();
    if(vr_tg(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = dwuc();
    if(vr_tg(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = ystoh();
    if(vr_tg(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(zburkq(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
			delete[] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
			delete[] file_buffer;
      return 1;
    }
    //No code should be added past this point.
  }

}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool upzd(int argc, char** argv, char*& bfnfk_,
		     int& s_kk) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream wzufh(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!wzufh) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;


  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  wzufh.seekg(0, wzufh.end);
	int ttaoj = wzufh.tellg();
	wzufh.seekg(0, wzufh.beg);

	// make an array of bytes to hold this information
	char* bdzsom = new char[ttaoj];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  wzufh.read(bdzsom, ttaoj);
	wzufh.close();
  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << wzufh.gcount() << " bytes of data."
	    << std::endl;
  assert(wzufh.gcount() == ttaoj);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  s_kk = ttaoj;
  bfnfk_ = bdzsom;
  return true;
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void mnuwcf(int* vumsyq, int eujjll) {
  *(vumsyq+((eujjll+1962) & 3)) = eujjll ^ 3735928559u;
  *(vumsyq+((eujjll+1492) & 3)) = eujjll ^ 3056505882u;
  *(vumsyq+((eujjll+'G') & 3)) = eujjll ^ 01353340336u;
  *(vumsyq+((eujjll+1) & 3)) = eujjll ^ 3405691582u;
  int bgnvhm = 1;
  char gv_zqf = 0;
  char* ssrow = (char*) vumsyq;
  for(bgnvhm = 32767; bgnvhm<32783; bgnvhm++) {
    for(gv_zqf=7; gv_zqf >= 0; --gv_zqf) {
      if(((*ssrow)>>gv_zqf) & 1) (*ssrow) ^= (eujjll >> (gv_zqf/2)*8) & 255;
      else (*ssrow) = (((*ssrow)<<5) & 224) | (((*ssrow)>>3) & 31);
      if(*ssrow & 4) (*ssrow = ~(*ssrow));
    }
    ++ssrow;
  }
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   ypu_(3,4) should be 5
   ypu_(3,5) should be 4
*/
int ypu_(int zqyyml, int xtnfv_) {
  double m__e; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // zqyyml and y are both legs
  float khajln = zqyyml*zqyyml + xtnfv_*xtnfv_;
  float nzlrb = modf(sqrt(khajln), &m__e);
  if((nzlrb == 0))
    return (int) m__e;

  // zqyyml is the hypotenuse, need to subtract instead of add
  float rderb = abs(xtnfv_*xtnfv_ - zqyyml*zqyyml);
  nzlrb = modf(sqrt(rderb), &m__e);
  if((nzlrb == 0))
    return (int) m__e;
	return -1;
}
