//虚拟继承
class Point1D
{
public:
    Point1D(int x = 1) : x_(x) {}

private:
    int x_;
};

class Point2D : public virtual Point1D
{
public:
    Point2D(int y = 2) : Point1D(), y_(y) {}

private:
    int y_;
};