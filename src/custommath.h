#ifndef __AIDENMATH__
#define __AIDENMATH__
//dont question why i made this

//sign values 
#define sign(val) \
  (val) < 0 ? -1 : 1

float MAX(float INPUT, float INPUT2, float INPUT3, float INPUT4) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2; 
  auto _temp2 = INPUT3 > INPUT4 ? INPUT3 : INPUT4;
  return _temp > _temp2 ? _temp : _temp2;
}
float MAX(float INPUT, float INPUT2, float INPUT3) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2;
  return _temp > INPUT3 ? _temp : INPUT3;
}
float MAX(float INPUT, float INPUT2) {
  return INPUT > INPUT2 ? INPUT : INPUT2;
}

int MAX(int INPUT, int INPUT2, int INPUT3, int INPUT4) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2; 
  auto _temp2 = INPUT3 > INPUT4 ? INPUT3 : INPUT4;
  return _temp > _temp2 ? _temp : _temp2;
}
int MAX(int INPUT, int INPUT2, int INPUT3) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2;
  return _temp > INPUT3 ? _temp : INPUT3;  
}
int MAX(int INPUT, int INPUT2) {
  return INPUT > INPUT2 ? INPUT : INPUT2;  
}

double MAX(double INPUT, double INPUT2, double INPUT3, double INPUT4) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2; 
  auto _temp2 = INPUT3 > INPUT4 ? INPUT3 : INPUT4;
  return _temp > _temp2 ? _temp : _temp2;
}
double MAX(double INPUT, double INPUT2, double INPUT3) {
  auto _temp = INPUT > INPUT2 ? INPUT : INPUT2;
  return _temp > INPUT3 ? _temp : INPUT3; 
}
double MAX(double INPUT, double INPUT2) {
  return INPUT > INPUT2 ? INPUT : INPUT2;
}

#endif //__AIDENMATH__