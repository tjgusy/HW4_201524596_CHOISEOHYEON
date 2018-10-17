

int bitAnd(int x, int y) {
  x = ~x;
  y= ~y;
  
  return ~(x | y);

}

int getByte(int x, int n) {
  x= x >> (n << 3);
  return x & 0xff;
}

int logicalShift(int x, int n) {

  int temp;
  temp = ~(((1 << 31) >> n) << 1);
  x = (x >> n) & temp;



  return x;

}

int bitCount(int x) {

  int tmp, val1, val2, val3, val4, val5, v;

  

  tmp = 0x55 | (0x55 << 8);

  val1 = tmp | (tmp << 16); // 0x55555555

    

  tmp = 0x33 | (0x33 << 8);

  val2 = tmp | (tmp << 16); // 0x33333333



  tmp = 0x0F | (0x0F << 8);

  val3 = tmp | (tmp << 16); // 0x0F0F0F0F



  val4 = 0xFF | (0xFF << 16); // 0x00FF00FF

  

  tmp = 0xFF | (0xFF << 8);

  val5 = tmp | (0 << 16); // 0x0000FFFF



  v = (x & val1) + ((x >> 1) & val1);

  v = (v & val2) + ((v >> 2) & val2);

  v = (v & val3) + ((v >> 4) & val3);

  v = (v & val4) + ((v >> 8) & val4);

  v = (v & val5) + ((v >> 16) & val5);



  return v;

}


int bang(int x) {
  int temp ;
  temp = ~x+1;
  temp = x | temp;
  temp = temp>>31;
  temp = temp +1;
  return temp;

}

int tmin(void) {

  return 0x80 << 24;

}


int fitsBits(int x, int n) {



  int c;



  c = 33 + ~n;



  return !(((x << c) >> c) ^ x); 

}


int divpwr2(int x, int n) {

  int bias;
  int temp;


  bias = (1 << n) + ~0;
  
  temp =((x >> 31) & bias);

  return (x + temp) >> n;
}



int negate(int x) {

  return ~x + 1;

}



int isPositive(int x) {

  int temp = x >> 31;

  

  return !(temp | (!x));

}


int isLessOrEqual(int x, int y) {


  int sign_x, sign_y, temp;



  sign_x = (x >> 31) & 1;

  sign_y = (y >> 31) & 1;

  




  temp = (!(sign_x ^ sign_y)) & (((x + ~y) >> 31) & 1);

  return temp | ((!sign_y) & sign_x);

  

}


int ilog2(int x) {

  

  int tmp, val1, val2, val3, val4, val5, v;





  x = x | (x >> 1);

  x = x | (x >> 2);

  x = x | (x >> 4);
	
  x = x | (x >> 8);

  x = x | (x >> 16);  




  // bitCount  

  

  

  tmp = 0x55 | (0x55 << 8);

  val1 = tmp | (tmp << 16); // 0x55555555

    

  tmp = 0x33 | (0x33 << 8);

  val2 = tmp | (tmp << 16); // 0x33333333



  tmp = 0x0F | (0x0F << 8);

  val3 = tmp | (tmp << 16); // 0x0F0F0F0F



  val4 = 0xFF | (0xFF << 16); // 0x00FF00FF

  

  tmp = 0xFF | (0xFF << 8);

  val5 = tmp | (0 << 16); // 0x0000FFFF



  v = (x & val1) + ((x >> 1) & val1);

  v = (v & val2) + ((v >> 2) & val2);

  v = (v & val3) + ((v >> 4) & val3);

  v = (v & val4) + ((v >> 8) & val4);

  v = (v & val5) + ((v >> 16) & val5);




  return v + ~0; // x - 1

}


unsigned float_neg(unsigned uf) {



  if (((uf << 1) >> 24) == 0xFF && ((uf << 9) != 0))

    return uf;

  return (1 << 31) ^ uf;

}



unsigned float_i2f(int x) {

  int sign, exp, frac, bitc, tailb;



  if (x == 0) return 0;

  else if (x == 0x80000000) return 0xCF000000;

   

  sign = (x >> 31) & 1;

  if (sign) x = -x;

  

  bitc = 1;

  while ((x >> bitc) != 0)

    bitc++;

  bitc--;



  exp = bitc + 127;

  

  x = x << (31 - bitc); // clear all those zeros to the left of MSB

  frac = (x >> 8) & 0x7FFFFF;



  // round to even (nearest) 

  if (bitc > 23) {

    tailb = x & 0xFF; // byte to round

    

    if ((tailb > 128) || ((tailb == 128) && (frac & 1))) {

      frac += 1;

      if (frac >> 23) {

        exp += 1;

        frac = 0;

      } 

    }

  }



  return (sign << 31) | (exp << 23) | frac;

}



unsigned float_twice(unsigned uf) {

  if ((uf & 0x7F800000) == 0) { // denormalized

    uf = ((uf & 0x007FFFFF) << 1) | (0x80000000 & uf);

  } else if ((uf & 0x7F800000) != 0x7F800000) { // normalized

    uf = uf + 0x00800000;

  } // NAN



  return uf;

}
