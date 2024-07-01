#include <stdio.h>
#include <math.h>
// зеленая прямая
float f1(float x){
return 0.6 * x + 3;
}

// синяя изогнутая линия
float f2(float x){
return (x-2)*(x-2)*(x-2)- 1;
}
// красная из двух частей
float f3(float x){
return 3.0/x;
}

float dif(float x,
float (*func1)(float),
float (*func2)(float))
{
return func1(x) - func2(x);
}
// для пересечения красной и зеленой
float F1(float x){
//return f1(x) - f3(x);
return dif(x, f1, f3);
}
// для пересенечи красной и синей
float F2(float x){
return f3(x) - f2(x);
}

float F3(float x){
return f1(x) - f2(x);
}

float findXForF1(float x1, float x2, float step){
float x = x1;
float bestValue = fabs(F1(x));
float bestX = x;
while (x < x2){
x += step;
if (fabs(F1(x)) < bestValue){
bestValue = fabs(F1(x));
bestX = x;
}
}
return bestX;
}

float findXForF2(float x1, float x2, float step){
float x = x1;
float bestValue = fabs(F2(x));
float bestX = x;
while (x < x2){
x += step;
if (fabs(F2(x)) < bestValue){
bestValue = fabs(F2(x));
bestX = x;
}
}
return bestX;
}
//площадь x1 - x2
float squareX1X2(float x1, float x2, float step){
float square = 0.0;
float x = x1;
while (x < x2){
square += 2 * step * F1(x + step);
x += 2 * step;
}
return square;
}

//площадь x2 - x3
float squareX2X3(float x1, float x2, float step){
float square = 0.0;
float x = x1;
while (x < x2){
square += 2 * step * F3(x + step);
x += 2 * step;
}
return square;
}

float squareX3X4(float x1, float x2, float step){
float square = 0.0;
float x = x1;
while (x < x2){
square += 2 * step * F2(x + step);
x += 2 * step;
}
return square;
}

int main(){
float epsilon = 0.05;

float x1 = findXForF1(-6, -5, epsilon );
float x3 = findXForF1(0, 1, epsilon );
float x2 = findXForF2(-1, 0, epsilon );
float x4 = findXForF2(3, 4, epsilon );

float square =
squareX1X2(x1, x2, epsilon / 2.0) +
squareX2X3(x2, x3, epsilon / 2.0) +
squareX3X4(x3, x4, epsilon / 2.0);

printf("%f\n", square);
return 0;

}