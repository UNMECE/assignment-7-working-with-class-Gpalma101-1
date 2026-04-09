#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>

class Electric_Field
{
private:
    double *E; // E[0]=Ex, E[1]=Ey, E[2]=Ez

public:
    Electric_Field() : E(new double[3]{0.0, 0.0, 0.0}) {}

    Electric_Field(double Ex, double Ey, double Ez) : E(new double[3]{Ex, Ey, Ez}) {}

    Electric_Field(const Electric_Field& other) : E(new double[3]{other.E[0], other.E[1], other.E[2]}) {}

    Electric_Field& operator=(const Electric_Field& other)
    {
        if (this != &other)
        {
            E[0] = other.E[0];
            E[1] = other.E[1];
            E[2] = other.E[2];
        }
        return *this;
    }

    ~Electric_Field()
    {
        delete[] E;
    }

    double getEx() const { return E[0]; }
    double getEy() const { return E[1]; }
    double getEz() const { return E[2]; }

    void setEx(double Ex) { E[0] = Ex; }
    void setEy(double Ey) { E[1] = Ey; }
    void setEz(double Ez) { E[2] = Ez; }

    double calculateMagnitude() const
    {
        return std::sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
    }

    double innerProduct(const Electric_Field& other) const
    {
        return E[0] * other.E[0] + E[1] * other.E[1] + E[2] * other.E[2];
    }
};

class Magnetic_Field
{
private:
    double *B; // B[0]=Bx, B[1]=By, B[2]=Bz

public:
    Magnetic_Field() : B(new double[3]{0.0, 0.0, 0.0}) {}

    Magnetic_Field(double Bx, double By, double Bz) : B(new double[3]{Bx, By, Bz}) {}

    Magnetic_Field(const Magnetic_Field& other) : B(new double[3]{other.B[0], other.B[1], other.B[2]}) {}

    Magnetic_Field& operator=(const Magnetic_Field& other)
    {
        if (this != &other)
        {
            B[0] = other.B[0];
            B[1] = other.B[1];
            B[2] = other.B[2];
        }
        return *this;
    }

    ~Magnetic_Field()
    {
        delete[] B;
    }

    double getBx() const { return B[0]; }
    double getBy() const { return B[1]; }
    double getBz() const { return B[2]; }

    void setBx(double Bx) { B[0] = Bx; }
    void setBy(double By) { B[1] = By; }
    void setBz(double Bz) { B[2] = Bz; }

    double calculateMagnitude() const
    {
        return std::sqrt(B[0] * B[0] + B[1] * B[1] + B[2] * B[2]);
    }

    std::array<double, 3> calculateUnitVector() const
    {
        double mag = calculateMagnitude();
        if (mag == 0.0)
        {
            return {0.0, 0.0, 0.0}; // avoid divide-by-zero
        }
        return {B[0] / mag, B[1] / mag, B[2] / mag};
    }
};

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    Electric_Field E_default;                    // default constructor
    Electric_Field E_components(1e5, 10.9, 1.7e2); // 3-component constructor

    Electric_Field E_setter;
    E_setter.setEx(3200.0);
    E_setter.setEy(-120.5);
    E_setter.setEz(45.0);

    Magnetic_Field B_default;                    // default constructor
    Magnetic_Field B_components(0.02, -0.03, 0.04); // 3-component constructor

    Magnetic_Field B_setter;
    B_setter.setBx(0.5);
    B_setter.setBy(0.4);
    B_setter.setBz(0.1);

    
    std::cout << "E_default magnitude:    " << E_default.calculateMagnitude() << '\n';
    std::cout << "E_components magnitude: " << E_components.calculateMagnitude() << '\n';
    std::cout << "E_setter magnitude:     " << E_setter.calculateMagnitude() << "\n\n";

    std::cout << "B_default magnitude:    " << B_default.calculateMagnitude() << '\n';
    std::cout << "B_components magnitude: " << B_components.calculateMagnitude() << '\n';
    std::cout << "B_setter magnitude:     " << B_setter.calculateMagnitude() << "\n\n";

    double dotE = E_components.innerProduct(E_setter);
    std::cout << "Inner product (E_components · E_setter): " << dotE << "\n\n";

    auto uB = B_components.calculateUnitVector();
    std::cout << "Unit vector of B_components: ("
              << uB[0] << ", " << uB[1] << ", " << uB[2] << ")\n";

    return 0;
}
