#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

// Ерөнхий дүрсийн класс
class Shape{
  protected:
    char name[20];
  public:
    Shape(const char *n = "shape"){
      strcpy(name, n);
    }
    void set_name(const char *n){
      strcpy(name, n);
    }
    const char *get_name(){ return name; }
};

// 2D дүрсийн класс
class TwoDShape : public Shape{
  protected:
    float length, area, perimeter;
    int *x, *y;
  public:
    TwoDShape(float l = 0) : Shape(){
      length = l;
      area = 0;
      perimeter = 0;
      x = new int[1];  
      y = new int[1];  
    }
    virtual ~TwoDShape(){
      delete []x;
      delete []y;
    }

    void set_x(int _x){ this->x[0] = _x; }
    void set_y(int _y){ this->y[0] = _y; }
    int get_x(){ return x[0]; }
    int get_y(){ return y[0]; }
    float get_area(){ return area; }
    float get_perimeter(){ return perimeter; }
    void findArea(float _a){ area = _a; }
    void findPerimeter(float _p){ perimeter = _p; }
    virtual void setCoordinates(int _x, int _y){} 

    // Дүрсийн мэдээллийг санамсаргүй авах функц
    void getData() {
        // Санамсаргүй нэр, координат, хэмжээг үүсгэнэ
        const char *shapeNames[] = {"Тойрог", "Дөрвөлжин", "Гурвалжин"};
        strcpy(name, shapeNames[rand() % 3]);
        set_name(name);

        int randomX = rand() % 100;
        int randomY = rand() % 100;
        set_x(randomX);
        set_y(randomY);
    }

    // Дүрсийн нэр, талбай, периметрийг хэвлэх функц
    void displayData(int index){
      cout << endl << "Дүрс " << index << ": " << this->get_name() << endl;
      cout << "Талбай = " << area << endl;
      cout << "Периметр = " << perimeter << endl;
    }
};

// Тойрог класс
class Circle : public TwoDShape{
  public:
    Circle() : TwoDShape() {}   

    void setCoordinates(int _x, int _y){        
      this->x[0] = _x;        
      this->y[0] = _y;    
    }  

    // Тойргийн мэдээллийг санамсаргүй авах функц
    void getData() {
        TwoDShape::getData(); 
        length = rand() % 10 + 1; // Радиусыг санамсаргүйгээр 1-10 хооронд авах
        findArea(M_PI * length * length); 
        findPerimeter(2 * M_PI * length); 
    }

    void displayData(int index) {
        TwoDShape::displayData(index);
        setCoordinates(get_x(), get_y());
        cout << "Радиус = " << length << endl;
    }
};

// Квадрат класс
class Square : public TwoDShape{
  public:
    Square() : TwoDShape(){}

    // Квадратын оройн цэгүүдийг олох функц
    void setCoordinates(int _x, int _y){
      this->x[0] = _x;        
      this->y[0] = _y;        
      this->x[1] = _x;        
      this->y[1] = _y - length;       
      this->x[2] = _x + length;        
      this->y[2] = _y - length;       
      this->x[3] = _x + length;       
      this->y[3] = _y; 
    }

    // Квадратын мэдээллийг санамсаргүй авах функц
    void getData() {
        TwoDShape::getData();
        length = rand() % 10 + 1;  
        findArea(length * length); 
        findPerimeter(4 * length); 
    }

    void displayData(int index) {
        TwoDShape::displayData(index);
        setCoordinates(get_x(), get_y());
        cout << "Талын урт = " << length << endl;
    }
};

// Гурвалжин класс
class Triangle : public TwoDShape {
public:
    Triangle() : TwoDShape() {}

    void setCoordinates(int _x, int _y) {
        this->x[0] = _x;
        this->y[0] = _y;
        this->x[1] = _x - length / 2;
        this->y[1] = _y - (sqrt(3) / 2) * length;
        this->x[2] = _x + length / 2;
        this->y[2] = _y - (sqrt(3) / 2) * length;
    }

    // Гурвалжины мэдээллийг санамсаргүй авах функц
    void getData() {
        TwoDShape::getData(); 
        length = rand() % 10 + 1; 
        setCoordinates(get_x(), get_y());
        findArea((sqrt(3) / 4) * length * length); 
        findPerimeter(3 * length); 
    }

    void displayData(int index) {
        TwoDShape::displayData(index);
        setCoordinates(get_x(), get_y());
        cout << "Талын урт = " << length << endl;
    }
};

int main() {
    srand(time(0)); 

    vector<TwoDShape*> shapes;

    // 20-30 санамсаргүй тооны дүрс үүсгэнэ
    int numShapes = rand() % 11 + 20; 
    for (int i = 0; i < numShapes; i++) {
        int shapeType = rand() % 3; // Дүрсний төрлийг санамсаргүй сонгоно
        TwoDShape* shape = nullptr;

        if (shapeType == 0) { 
            Circle* circle = new Circle();
            circle->getData(); // Радиусыг санамсаргүйгээр оруулах
            shape = circle;
        } else if (shapeType == 1) { 
            Square* square = new Square();
            square->getData(); // Талын уртыг санамсаргүйгээр оруулах
            shape = square;
        } else { 
            Triangle* triangle = new Triangle();
            triangle->getData(); // Талын уртыг санамсаргүйгээр оруулах
            shape = triangle;
        }

        shapes.push_back(shape);
    }

    // Талбайн хэмжээгээр эрэмбэлнэ
    sort(shapes.begin(), shapes.end(), [](TwoDShape* a, TwoDShape* b) {
        return a->get_area() < b->get_area();
    });

    int index = 1;
    for (TwoDShape* shape : shapes) {
        shape->displayData(index++);
        delete shape; 
    }

    return 0;
}