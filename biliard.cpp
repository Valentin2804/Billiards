#include <iostream>
#include <cmath>
using namespace std;

class Point
{
    double x;
    double y;

public:

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    double getDistance(const Point& secondPoint) const
    {
        return sqrt(((this->x - secondPoint.x)*(this->x - secondPoint.x))
         + ((this->y - secondPoint.y)*(this->y - secondPoint.y)));
    }

    int getX() const
    {
        return this->x;
    }

    int getY() const
    {
        return this->y;
    }

    void setX(int x)
    {
        this->x = x;
    }

    void setY(int y)
    {
        this->y = y;
    }

    double getArea(const Point& a, const Point& b)
    {
        return abs((this->x*(a.getY() - b.getY())) + (a.getX()*(b.getY() - this->y)) + (b.getX()*(this->getY() - a.getY()))) / 2;
    }

    bool isEqual(Point point)
    {
        if(this->x == point.getX() && this->y == point.getY())
        {
            return true;
        }else
        {
            return false;
        }
    }
};

class Vector
{
    double x, y;

public:

    Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Vector(const Point p1, const Point p2)
    {
        this->x = p2.getX() - p1.getX();
        this->y = p2.getY() - p1.getY();
    }

    Vector timesNum(double num) const 
    {
        Vector vec((this->x) * num, (this->y) * num);

        return vec;
    }

    double dot_product(const Vector& other) const 
    {
        double product = this->x*other.x + this->y*other.y;
    
        return product;
    }

    bool isSameDirectionColinear(const Vector& other) const
    {
        if((this->x * other.y) == (this->y * other.x) && this->dot_product(other) > 0)
        {
            return true;
        }
    
        return false;
    }

    double getX() const
    {
        return this->x;
    }

    double getY() const
    {
        return this->y;
    }
};

class Line 
{
    double a;
    double b;
    double c;

    double lenght;

public:

    Line()
    {
        this->a = 0;
        this->b = 0;
        this->c = 0;

        this->lenght = 0;
    }

    Line(const Point &a, const Point &b)
    {
        this->a = b.getY() - a.getY();
        this->b = a.getX() - b.getX();
        this->c = (this->a * (a.getX())) + (this->b * (a.getY()));

        this->lenght = a.getDistance(b);
    }

    Line(const Point p, const Vector& v) 
    {
        this->a = v.getY();
        this->b = -v.getX();
        this->c = -((this->a*p.getX())+(this->b*p.getY()));
    }

    bool isOnLine(const Point& a) const
    {
        if (this->b < 0)
        {
            if((this->a * a.getX()) - (this->b * a.getY()) == this->c)
            {
                return true;
            }else
            {
                return false;
            }
        }else
        {
            if((this->a * a.getX()) + (this->b * a.getY()) == this->c)
            {
                return true;
            }else
            {
                return false;
            }
        }
    }

    bool isOrthogonal(const Line& other) const 
    {
	    if (((this->a*other.a) + (this->b*other.b)) == 0)
	    {
		    return true;
	    }
	
	    return false;
    }

    Vector orthogonal() const 
    {
        Vector new_vec(this->a, this->b);
        
        return new_vec;
    }

    double distanceToPoint(const Point& a) const 
    {
        return abs((this->a * a.getX()) + (this->b * a.getY()) + this->c) / sqrt((this->a * this->a) + (this->b * this->b));
    }

    double getLenght()
    {
        return this->lenght;
    }

    Point getIntersectPoint(Line line)
    {
        double x = (this->b * line.c - line.b * this->c) / (this->a * line.b - line.a * this->b);
        double y = (this->c * line.a - line.c * this->a) / (this->a * line.b - line.a * this->b);

        if(x == -0)
        {
            x = 0;
        }

        if(y == -0)
        {
            y = 0;
        }

        return Point(x, y);
    }

    bool isParalel(Line line)
    {
        if(this->a * line.b == this->b * line.a)
        {
            return true;
        }

        return false;
    }

    Line orthogonal(const Point p) const 
    {
        Line new_line(p, this->orthogonal());
        
        return new_line;
    }
};

class Ball
{
    int diameter;
    Point startPoint;
    Point currentPoint;

public:

    Ball()
    {
        diameter = 0;
    }

    Ball(int diameter, const Point &startPoint)
    {
        if(diameter < 0)
        {
            throw invalid_argument("Invalid diameter(should be non negative number)");
        }
        this->diameter  = diameter;
        this->startPoint = startPoint;
        this->currentPoint = startPoint;
    }

    Point getStartPoint() const
    {
        return this->startPoint;
    }

    Point getCurrentPoint() const
    {
        return this->currentPoint;
    }

    int getDiameter() const
    {
        return this->diameter;
    }

    void setCurrentPoint(Point a)
    {
        this->currentPoint = a;
    }
};

class Table
{
    Point upLeftCorner;
    Point upRightCorner;
    Point downLeftCorner;
    Point downRightCorner;
    Ball ball;

public:

    Table(const Point& upLeftCorner, const Point &upRightCorner
    , const Point& downLeftCorner, const Point& downRightCorner)
    {
        Line left(upLeftCorner, downLeftCorner);
        Line right(upRightCorner, downRightCorner);
        Line up(upLeftCorner, upRightCorner);
        Line down(downLeftCorner, downRightCorner);

        if(!left.isOrthogonal(up) || !right.isOrthogonal(down))
        {
            throw invalid_argument("Invalid table provided (should be rectangle with perpendicular angles)");
        }

        if(!(abs((upLeftCorner.getDistance(upRightCorner)/2) - upLeftCorner.getDistance(downLeftCorner)) < numeric_limits<double>::epsilon()))
        {
            throw invalid_argument("Invalid table provided (should be in 1:2 proportion)");
        }

        this->downLeftCorner = downLeftCorner;
        this->downRightCorner = downRightCorner;
        this->upLeftCorner = upLeftCorner;
        this->upRightCorner = upRightCorner;
        this->ball = ball;       
    }

    bool IsOnTable(Point point)
    {
        if(((point.getArea(this->getUpLeftCorner(), this->getUpRightCorner()) 
        + point.getArea(this->getDownRightCorner(), this->getUpRightCorner())
        + point.getArea(this->getDownLeftCorner(), this->getDownRightCorner())
        + point.getArea(this->getUpLeftCorner(), this->getDownLeftCorner())) 
        - (this->getDownLeftCorner().getDistance(this->getUpLeftCorner()) * this->getUpLeftCorner().getDistance(this->getUpRightCorner()))
        < numeric_limits<double>::epsilon()))
        {
            return true;
        }

        return false;
    }

    void setStartPoint()
    {
        cout<< "now ball is out of the table, change the coordinates of the ball\n";
            int x;
            int y;
            cout<< "X: ";
            cin >> x;
            cout<< "\nY: ";
            cin >> y;

            Point newPoint(x, y);

            Ball newBall(this->ball.getDiameter(), newPoint);

            this->setBall(newBall);
    }

    void resize()
    {
        this->downLeftCorner.setX(0 + this->ball.getDiameter()/2);
        this->downLeftCorner.setY(0 + this->ball.getDiameter()/2);

        this->downRightCorner.setX(this->downRightCorner.getX() - this->ball.getDiameter()/2);
        this->downRightCorner.setY(0 + this->ball.getDiameter()/2);

        this->upLeftCorner.setX(0 + this->ball.getDiameter()/2);
        this->upLeftCorner.setY(this->getUpLeftCorner().getY() - this->ball.getDiameter()/2);

        this->upRightCorner.setX(this->getUpRightCorner().getX() - this->ball.getDiameter()/2);
        this->upRightCorner.setY(this->getUpRightCorner().getY() - this->ball.getDiameter()/2);
    }

    void setBall(Ball ball)
    {
        if(!this->IsOnTable(ball.getStartPoint()))
        {
            throw invalid_argument("Invalid ball provided(should be on the field)");
        }

        this->ball = ball;
    }

    Point getUpLeftCorner() const
    {
        return this->upLeftCorner;
    }

    Point getUpRightCorner() const
    {
        return this->upRightCorner;
    }

    Point getDownLeftCorner() const
    {
        return this->downLeftCorner;
    }

    Point getDownRightCorner() const
    {
        return this->downRightCorner;
    }

    Ball getBall() const
    {
        return this->ball;
    }

    void hitR(Point direction, Vector visualVector)
    {
        if(direction.isEqual(this->downLeftCorner) || direction.isEqual(this->downRightCorner)
         || direction.isEqual(this->upLeftCorner) || direction.isEqual(this->upRightCorner))
        {
            this->ball.setCurrentPoint(this->ball.getStartPoint());
        }else
        {
            Line visualLine(this->ball.getCurrentPoint(), direction);

            Line left(this->upLeftCorner, this->downLeftCorner);
            Line up(this->upLeftCorner, this->upRightCorner);
            Line down(this->downLeftCorner, this->downRightCorner);
            Line right(this->upRightCorner, this->downRightCorner);

            if(this->IsOnTable(direction))
            {
                this->ball.setCurrentPoint(direction);
            }else
            {
                if(!visualLine.isParalel(up))
                {
                    Point pointUp(visualLine.getIntersectPoint(up));
                    Vector toUp(this->ball.getCurrentPoint(), pointUp);

                    if(visualVector.isSameDirectionColinear(toUp))
                    {  
                        this->ball.setCurrentPoint(pointUp);
                        direction.setY(direction.getY() - 2 * up.orthogonal(direction).getIntersectPoint(up).getDistance(direction));
                        Vector newVec(pointUp, direction);
                        visualVector = newVec;
                        hitR(direction, visualVector);
                    }
                }

                if(!visualLine.isParalel(left))
                {
                    Point pointLeft(visualLine.getIntersectPoint(left));
                    Vector toLeft(this->ball.getCurrentPoint(), pointLeft);

                    if(visualVector.isSameDirectionColinear(toLeft))
                    {  
                        this->ball.setCurrentPoint(pointLeft);
                        direction.setX(abs(left.distanceToPoint(direction)));
                        Vector newVec(pointLeft, direction);
                        visualVector = newVec;
                        hitR(direction, visualVector);
                    }
                }

                if(!visualLine.isParalel(right))
                {
                    Point pointRight(visualLine.getIntersectPoint(right));
                    Vector toRight(this->ball.getCurrentPoint(), pointRight);

                    if(visualVector.isSameDirectionColinear(toRight))
                    {  
                        this->ball.setCurrentPoint(pointRight);
                        direction.setX(direction.getX() - 2 * right.orthogonal(direction).getIntersectPoint(right).getDistance(direction));
                        Vector newVec(pointRight, direction);
                        visualVector = newVec;
                        hitR(direction, visualVector);
                    }
                }

                if(!visualLine.isParalel(down))
                {
                    Point pointDown(visualLine.getIntersectPoint(down));
                    Vector toDown(this->ball.getCurrentPoint(), pointDown);

                    if(visualVector.isSameDirectionColinear(toDown))
                    {  
                        this->ball.setCurrentPoint(pointDown);
                        direction.setY(abs(down.distanceToPoint(direction)));
                        Vector newVec(pointDown, direction);
                        visualVector = newVec;
                        hitR(direction, visualVector);
                    }
                }
            }
        }
    }

    void hit(Point direction, double power)
    {
        if(power < 1 || power > 10)
        {
            throw invalid_argument("Invalid power provided(should be between 1 and 10)");
        }

        Vector visualVector(this->ball.getCurrentPoint(), direction);
        visualVector = visualVector.timesNum(power);


        direction.setX(this->ball.getCurrentPoint().getX() + visualVector.getX());
        direction.setY(this->ball.getCurrentPoint().getY() + visualVector.getY());
        
        this->hitR(direction, visualVector);
    }
};

int main() {

    char SCCase;

    cout<< "Hello, what is your case, simple(S) or complex(C)\n";
    cin >> SCCase;

    if(SCCase == 'S')
    {
        int num;
        double x, y, longSide, shortSide, ballDiameter, power;

        cout<< "\nGive me start point coordinates, width and lenght of your table:\n";
        cout<< "Table start point X: ";
        cin >> x;
        cout<< "Table start point Y: ";
        cin >> y;
        cout<< "Width: ";
        cin >> longSide;
        cout<< "Lenght: ";
        cin >> shortSide;

        Point downLeftCorner(x, y);
        Point downRightCorner(x+longSide, y);
        Point upLeftCorner(x, y+shortSide);
        Point upRightCorner(x+longSide, y+shortSide);

        Table table(upLeftCorner, upRightCorner, downLeftCorner, downRightCorner);

        cout << "\nGive me the start point of the ball and it's diameter\n";
        cout<< "Ball start point X: ";
        cin >> x;
        cout<< "Ball start point Y: ";
        cin >> y;
        cout<< "Diameter: ";
        cin >> ballDiameter;

        Point ballStart(x, y);

        Ball ball(ballDiameter, ballStart);

        table.setBall(ball);

        table.resize();

        while(1){
            cout<< "\nWhat do you want?\n1. Hit\n2. New start point of the ball\n3. Get to the start point of the ball\n";
            cin >> num;
            if(num == 1)
            {
                cout<< "Give me the point where you want to moove and your power\nX: ";
                cin >> x;
                cout << "Y:";
                cin >> y;
                cout << "Power: ";
                cin >> power;

                Point direction(x, y);

                table.hit(direction, power);

                cout<< "\nNew position of the ball: "<< table.getBall().getCurrentPoint().getX() << " " << table.getBall().getCurrentPoint().getY() << "\n";
            }else if (num == 2)
            {
                cout<< "Give me the new start point of the ball\nX: ";
                cin >> x;
                cout << "Y:";
                cin >> y;

                Point newPoint(x, y);

                Ball newball(table.getBall().getDiameter(), newPoint);

                table.setBall(newball);
            }else if (num == 3)
            {
                table.getBall().setCurrentPoint(table.getBall().getStartPoint());
            }
            else
            {
                cout<< "game ended";
                return 0;
            }
        }
        
    }else if (SCCase == 'C')
    {
        cout<< "\nDon't have complex case";
    }

    return 0;
}