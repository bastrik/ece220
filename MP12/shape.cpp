#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape(string name)
{
	name_ = name;
}
string Shape::getName()
{
	return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
Rectangle::Rectangle(double width, double length) : Shape("Rectangle")
{
	width_ = width;
	length_ = length;
}

double Rectangle::getWidth(){return width_;}
double Rectangle::getLength(){return length_;}
double Rectangle::getArea()
{
	return width_ * length_;
}
double Rectangle::getVolume()
{
	return 0;
}
Rectangle Rectangle::operator + (const Rectangle& rec)
{
	Rectangle rectangle;
	rectangle.length_ = this->length_ + rec.length_;
	rectangle.width_ = this->width_ + rec.width_;
	return rectangle;
}
Rectangle Rectangle::operator - (const Rectangle& rec)
{
	Rectangle rectangle;
	rectangle.length_ = max(0.0, this->length_ - rec.length_);
	rectangle.width_ = max(0.0, this->width_ + rec.width_);
	return rectangle;
}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
Circle::Circle(double radius) : Shape("Circle")
{
	radius_ = radius;
}

double Circle::getRadius(){return radius_;}
double Circle::getArea()
{
	return radius_ * radius_ * M_PI;
}
double Circle::getVolume()
{
	return 0;
}
Circle Circle::operator + (const Circle& cir)
{
	Circle circle(0.0);
	circle.radius_ = this->radius_ + cir.radius_;
	return circle;
}
Circle Circle::operator - (const Circle& cir)
{
	Circle circle(0.0);
	circle.radius_ = max(0.0, this->radius_ + cir.radius_);
	return circle;
}
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
Sphere::Sphere(double radius) : Shape("Sphere")
{
	radius_ = radius;
}

double Sphere::getRadius(){return radius_;}
double Sphere::getArea()
{
	return 4 * radius_ * radius_ * M_PI;
}
double Sphere::getVolume()
{
	return (4./3.) * radius_ * radius_ * radius_ * M_PI;
}
Sphere Sphere::operator + (const Sphere& sph)
{
	Sphere sphere(0.0);
	sphere.radius_ = this->radius_ + sph.radius_;
	return sphere;
}
Sphere Sphere::operator - (const Sphere& sph)
{
	Sphere sphere(0.0);
	sphere.radius_ = max(0.0, this->radius_ + sph.radius_);
	return sphere;
}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
RectPrism::RectPrism(double width, double length, double height) : Shape("RectPrism")
{
	length_ = length;
  	width_ = width;
  	height_ = height;
}

double RectPrism::getWidth(){return width_;}
double RectPrism::getHeight(){return height_;}
double RectPrism::getLength(){return length_;}
double RectPrism::getArea()
{
	return 2 * (length_*width_ + length_*height_ + width_*height_);
}
double RectPrism::getVolume()
{
	return length_ * width_ * height_;
}
RectPrism RectPrism::operator + (const RectPrism& rectp)
{
	RectPrism rectPrism(0.0, 0.0, 0.0);
	rectPrism.length_ = this->length_ + rectp.length_;
	rectPrism.width_ = this->width_ + rectp.width_;
	rectPrism.height_ = this->height_ + rectp.height_;
	return rectPrism;
}
RectPrism RectPrism::operator - (const RectPrism& rectp)
{
	RectPrism rectPrism(0.0, 0.0, 0.0);
	rectPrism.length_ = max(0.0, this->length_ + rectp.length_);
	rectPrism.width_ = max(0.0, this->width_ + rectp.width_);
	rectPrism.height_ = max(0.0, this->height_ + rectp.height_);
	return rectPrism;
}

 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	FILE * file;
	file = fopen(file_name, "r");
	int size = fscanf(file, "%d", &size);
	vector<Shape*> v(size);
	string shape;
	double r, l, w, h;

	while(feof(file) == 0)
    {    	
    	fscanf(file, "%s", &shape);
    	if (shape.compare("Circle"))
    	{
    		fscanf(file, "%lf", &r);
    		Shape * s = new Circle(r);
    		v.push_back(s);
    	}
    	if (shape.compare("Rectangle"))
    	{
    		fscanf(file, "%lf", &l);
    		fscanf(file, "%lf", &w);
    		Shape * s = new Rectangle(w, l);
    		v.push_back(s);
    	}
    	if (shape.compare("Sphere"))
    	{
    		fscanf(file, "%lf", &r);
    		Shape * s = new Sphere(r);
    		v.push_back(s);
    	}
    	if (shape.compare("RectPrism"))
    	{
    		fscanf(file, "%lf", &l);
    		fscanf(file, "%lf", &w);
    		fscanf(file, "%lf", &h);
    		Shape * s = new RectPrism(w, l, h);
    		v.push_back(s);
    	}
    }
    fclose(file);
	return v; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	for (vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		double temp = *it.getArea();
		if (temp > max_area)
			max_area = temp;
	}
	
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

	
	return max_volume;
}

