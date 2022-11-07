#if !defined(_MSC_VER)
#define CODING_VS_CODE
#endif
#include <iostream>
#include <math.h>
#if !defined(CODING_VS_CODE)
	#include <clocale>
#endif
using namespace std;

class Icosahedron {
	double a; // side of the icosahedron
	unsigned int color;
public:
	Icosahedron() : a(1.0), color(0) {}
	Icosahedron(double ai) : a(ai), color(0) {}
	Icosahedron(int ic) : a(1.0) { if (ic >= 0) color = ic; else color = 0; }
	Icosahedron(double a, int c) {
		this->a = a;
		if (c >= 0) color = c; else color = 0;
	}
	double getA() const
	{
		return a;
	}
	void setA(double a)
	{
		if (a < 0 || a > 1.e+100)
		{
			cout << " Error set  a \n";
			return;
		}
		this->a = a;
	}
	double getColor() const
	{
		return color;
	}
	void setColor(int c)
	{
		if (c < 0 || c > 10000)
		{
			cout << " Error set  color \n";
			return;
		}
		this->color = c;
	}
	double S() {
		return 5 * a * a * sqrt(3.0);
	}
	double V() {
		return 5 * a * a * a * (3 + sqrt(5.0)) / 12.0;
	}
	double r() {
		return a * (3 + sqrt(5.0)) / (4.0 * sqrt(3.0));
	}
	double R() {
		return sqrt(2 * (5 + sqrt(5.0) * a)) / 4.0;
	}
	void printInfo()
	{
		cout << "\n a= " << a << " color = " << color;
		cout << "  S= " << S() << " V = " << V() << "  r= " << r() << " V = " << R() << endl;
	}

};
int mainExample1()
{
	Icosahedron obj;
	obj.printInfo();
	double in_a; int in_color;
	cout << " Input side and color Icosahedron  "; cin >> in_a >> in_color;
	Icosahedron obj1(in_a), obj2(in_color), obj3(in_a, in_color);
	obj1.printInfo();
	obj2.printInfo();
	obj3.printInfo();
	obj.setA(-5);
	obj.printInfo();
	obj.setA(5);
	obj.printInfo();
	obj.setA(2.e100);
	obj.printInfo();
	obj.setColor(-10);
	obj.printInfo();
	obj.setColor(10);
	obj.printInfo();
	obj.setColor(10001);
	obj.printInfo();
	cout << " End testing \n";
	return 1;
}


// Ключове слово static 

class foo
{
private:
	static int count; // загальне поле всім об'єктів
	// (У сенсі "оголошення")
public:
	foo() { incObj(); } // інкрементування під час створення об'єкта
	static int incObj() { return ++count; }
	int getcount() { return count; }
};
int  foo::count = 0;
// Ключове слово static ставиться перед типом способу.В основному використовуються
//для роботи зі статичними полями класу.

/*  Example 3
Створити тип даних - клас вектор, який має поля x, y типу double і змінну стану. У класі визначити
o	конструктор без параметрів(інінціалізує поля в нуль);
o	конструктор з одним параметром типу double (інінціалізує поля);
o	конструктор з одним параметром вказівник на тип double (інінціалізує поля x, y значенням масиву за вказівником, якщо вказівник NULL (nulptr) то встановити код помилки);
o	деструктор із виведенням інформації про стан вектора;
o	визначити функції друку, додавання, віднімання, векторний добуток які здійснюють ці арифметичні операції з даними цього класу;
o	функцію ділення на ціле типу double(при діленні на 0 змінити стан, а ділення не виконувати);
o	визначити функцію порівняння менше які повертають true або false.
У змінну стани встановлювати код помилки, діленні на 0, при передачі NULL (nulptr) в конструкторі із вказівником. Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/
enum STATE {
	OK, BAD_INIT, BAD_DIV
};

class Vec2
{
	double  x, y;
	int state;
	static int count;
public:
	Vec2() : x(0), y(0) {
		state = OK; count++;
	}   // 	 конструктор без параметрів
	Vec2(double iv) : x(iv), y(iv) {
		state = OK; count++;
	}
	Vec2(double ix, double iy);
	Vec2(double* v);
	~Vec2() {
		count--;
		cout << " state Vec " << state;
		cout << " Vec delete \n";
	}
	Vec2(const Vec2&);
	Vec2 Add(Vec2& d);
	Vec2 Sub(Vec2& d);
	Vec2 Mul(double d);
	Vec2 Div(double d);
	void Input();   //  !!! Без первантаження операцій    
	void Output();  //  !!! Без первантаження операцій
	bool CompLessAll(Vec2& s);
	static int getCount() {
		if (count <= 0) cout << " Немає об'єктів Vec2 ";
		return count;
	}
	int getState() { return state; }
};
int Vec2::count = 0;
Vec2::Vec2(double ix, double iy) {
	x = ix; y = iy;
	state = OK;
	count++;
}
Vec2::Vec2(const Vec2& s) {
	//if (this == &s) return; //  // the expression is used in the old standard
	x = s.x; y = s.y; state = OK;
	count++;
};
Vec2::Vec2(double* v) {
	if (v == nullptr) {
		state = BAD_INIT; x = 0; y = 0;
	}
	else {
		x = v[0]; y = v[1];
		state = OK;
	}
	count++;
}
void Vec2::Input() {
	cout << " Input  x y ";
	cin >> x >> y;
}
void Vec2::Output() {
	cout << " x =" << x << " y = " << y << " state  " << state << endl;
}

Vec2 Vec2::Add(Vec2& s) {
	Vec2 tmp;
	tmp.x = x + s.x;
	tmp.y = y + s.y;
	return tmp;
}

Vec2 Vec2::Sub(Vec2& s) {
	Vec2 tmp;
	tmp.x = x - s.x;
	tmp.y = y - s.y;
	return tmp;
}
Vec2 Vec2::Div(double d) {
	Vec2 tmp;
	if (fabs(d) < 1.e-25) {
		tmp.state = BAD_DIV;
		cout << " Error div \n";
		return *this;
	}
	tmp.x = x / d;
	tmp.y = y / d;
	return tmp;
}
Vec2 Vec2::Mul(double d) {
	Vec2 tmp;
	tmp.x = x * d;
	tmp.y = y * d;
	return tmp;
}

bool Vec2::CompLessAll(Vec2& s) {

	if (x < s.x && y < s.y) return true;
	return false;
}

int mainExample3()
{
#if !defined(CODING_VS_CODE)
	setlocale(LC_CTYPE, "ukr");
	cout << "Тестування створенного класу \n";
	cout << "Тестування конструкторiв \n"; 
#else 
	cout << "Testing create class  \n";
	cout << "Testing crot's  \n";
#endif
	Vec2 ObjCDef;
	ObjCDef.Output();
	Vec2 ObjP1(10.0);
	ObjP1.Output();
	double  a = 1.0, b = 2.0;
	Vec2  ObjP2(a, b);
	ObjP2.Output();
	Vec2 ObjCopy(ObjP2);
	double* v = nullptr, v2[] = { 1.2, 3.3 };
	Vec2  ObjP3(v2);
	if (ObjP3.getState() != OK) cout << " ObjP3  x= 0  y= 0  \n";
	Vec2  ObjP4(v2);
	if (ObjP4.getState() != OK) cout << " ObjP4 x= 0  y= 0  \n";
#if !defined(CODING_VS_CODE)
	cout << " Кiлькiсть створених об'єктiв Vec2 " << Vec2::getCount() << endl;
	cout << "Тестування введення \n";
	ObjCDef.Input();
	cout << "Тестування функцiй \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n Кiлькiсть створених об'єктiв Vec2 до Sub " << Vec2::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n Кiлькiсть створених об'єктiв Vec2 пiсля Sub " << Vec2::getCount() << endl;
#else 
	cout << "Testing input \n";
	ObjCDef.Input();
	cout << "Testing gunction \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n Counts create objects Vec2 before  Sub " << Vec2::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n  Counts create objects Vec2 after Sub  " << Vec2::getCount() << endl;
#endif

	ObjCDef.Output();
	ObjCDef = ObjCDef.Mul(5);
	ObjCDef.Output();
	ObjCDef = ObjCDef.Div(1.3);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();

	ObjCDef = ObjCDef.Div(0.0);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();
	cout << "ObjCopy state " << ObjCopy.getState() << endl;
	if (ObjCopy.CompLessAll(ObjCDef))  cout << "ObjCopy less ObjDef  " << endl;

	
#if !defined(CODING_VS_CODE)
	cout << "Завершення  тестування  \n";
#else 
	cout << "Completion of testing  \n";
#endif
	return 1;

}
/*example  4
Створити тип даних - клас вектор, який має вказівник на ComplexDouble, число елементів і змінну стану. У класі визначити
o	 конструктор без параметрів( виділяє місце для одного елемента та інінціалізує його в нуль);
o	конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує масив значенням нуль);
o	конструктор із двома параметрами - розмір вектора та значення ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує значенням другого аргументу).
o	конструктор копій та операцію присвоєння; // !!!
o	деструктор звільняє пам'ять;
o	визначити функції друку, додавання;
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі масиву. Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/

#include<complex>
using namespace std;
typedef complex<double> ComplexDouble;
#define _RE 0
#define _IM 1

class ComplexVector
{
	ComplexDouble* v;
	int num;   // default num=2
	int state = 0;
public:
	ComplexVector() : ComplexVector(2) {}
	ComplexVector(int n);
	ComplexVector(int n, ComplexDouble&);
	ComplexVector(int n, ComplexDouble*);
	ComplexVector(const ComplexVector& s);
	ComplexVector& operator=(const ComplexVector& s);
	~ComplexVector() {
		std::cout << " del vec";
		if (v) delete[] v;
	}
	void Output();
	void Input();
	ComplexVector Add(ComplexVector& b);

};

ComplexVector::ComplexVector(int n) {
	if (n <= 0)    n = 2;  // default num =2;
	num = n;
	v = new ComplexDouble[n];
	for (int i = 0; i < n; i++) {
			v[i] = 0.0;
			//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
		}

}
ComplexVector::ComplexVector(int n, ComplexDouble& b) : ComplexVector(n) {
	for (int i = 0; i < num; i++) {
		v[i] = b;
		//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
	}
}

ComplexVector::ComplexVector(int n, ComplexDouble* p) : ComplexVector(n) {
	if (p != nullptr) 
	for (int i = 0; i < num; i++) 
		v[i] = p[i];
	
}

ComplexVector::ComplexVector(const ComplexVector& s) {
	// if (this == &s) return;  // the expression is used in the old standard
	num = s.num;
	v = new ComplexDouble[num];
	state = 0;
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
}

ComplexVector& ComplexVector::operator=(const ComplexVector& s) {

	if (num != s.num)
	{
		if (v) delete[] v;
		num = s.num;
		v = new ComplexDouble[num];
		state = 0;
	}
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
	return *this;
}
void ComplexVector::Input() {
	int in_num=0;
		do {
			cout << "Input size Vec\n";
			cin >> in_num;
		} while (in_num <= 0);
		if (num != in_num ) {
			num = in_num;
			if (v) delete[] v;
		v = new ComplexDouble[num];
	}
	for (int i = 0; i < num; i++) {

#if defined(_MSC_VER)
cout << " v [ " << i << " ] real img  "; cin >> v[i] >> v[i]._Val[_IM];
#else 
double re,im;
cout << " v [ " << i << " ] real img  "; cin >> re>>im;
v[i].real(re); 
v[i].imag(im);
#endif		
		
		
	}
}

void ComplexVector::Output() {
	if (num != 0) {
		for (int i = 0; i < num; i++) {
			cout << " v [ " << i << " ]   " << v[i] << '\t';
			cout << endl;
		}
	}
}

ComplexVector ComplexVector::Add(ComplexVector& b) {
	int tnum;
	tnum = num < b.num ? num : b.num;
	if (tnum >= 0) {
		ComplexVector tmp(tnum);
		for (int i = 0; i < tnum; i++) tmp.v[i] = v[i] + b.v[i];
		return tmp;
	}
	return ComplexVector(1);
}


int mainExample4()
{
	ComplexDouble a(1.0, 2), b, c;
	cout << a << endl;
#if defined(_MSC_VER)
    b._Val[_RE] = 21.3;
	b._Val[_IM] = 22.3;
#else 
    b.real( 21.3);
	b.imag (22.3);
#endif	
	
	cout << b << endl;
	c = a + b;
	cout << c << endl;
	cout << " Test  " << endl;
	ComplexVector VecObj, VecObj1(10);
	cout << "VecObj \n";
	VecObj.Output();
	cout << "VecObj1 \n";
	VecObj1.Output();
	cout << " Input a " << endl;

#if defined(_MSC_VER)
 cin >> a >> a._Val[_IM];
#else 
double re,im;
cin >> re>>im;
a.real(re); 
a.imag(im);
#endif		
	cout << a << endl;
	ComplexVector VecObj2(10, a);
	VecObj2.Output();

	VecObj.Input();
	cout << endl;
	VecObj.Output();
	VecObj1 = VecObj.Add(VecObj2);
	VecObj1.Output();

	return 1;
}

/// 

