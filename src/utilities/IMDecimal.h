#ifndef IM_DECIMAL_H
#define IM_DECIMAL_H

class IMDecimal {
  private:
    int whole;
    int fract;
    static const int precision = 100;
    static const int roundReserve = 10;
    void parse(float value);
    int getDecimalPlaces(const int value);

  public:
    IMDecimal(float value);
    IMDecimal();

    bool operator==(const IMDecimal& other) const;
    bool operator!=(const IMDecimal& other) const;
    bool operator>(const IMDecimal& other) const;
    bool operator<(const IMDecimal& other) const;
    bool operator>=(const IMDecimal& other) const;
    bool operator<=(const IMDecimal& other) const;
    float getFloat();
};

#endif