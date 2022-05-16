class Range
{
public:
    float min, mid, max;

    Range(float min, float mid, float max)
    {
        this->min = min;
        this->mid = mid;
        this->max = max;
    }

    Range(float min, float max)
    {
        this->min = min;
        this->mid = min + max / 2.f;
        this->max = max;
    }

    Range()
    {
        min = -1;
        mid = 0;
        max = 1;
    }

    //takes values from -1 to 1 and scales them to range
    float scale(float val)
    {
        if (val < -1)
            val = -1;
        else if (val > 1)
            val = 1;

        if (val < 0)
            return ((mid - min) * val) + mid;
        else
            return ((max - mid) * val) + mid;
    }

    //takes values from min to max and scales them to -1 to 1
    float inverceScale(float val)
    {
        if (val < min)
            val = min;
        else if (val > max)
            val = max;

        if (val < mid)
            return ((val - mid) / (mid - min));
        else
            return ((val - mid) / (max - mid));
    }
};

class Range2
{
public:
    Range r1, r2;

    Range2(Range r1, Range r2)
    {
        this->r1 = r1;
        this->r2 = r2;
    }

    Range2(float r1Min, float r1Mid, float r1Max , float r2Min, float r2Mid, float r2Max ){
        this -> r1 = Range(r1Min, r1Mid, r1Max);
        this -> r2 = Range(r2Min, r2Mid, r2Max);
    }

    Range2()
    {
        this->r1 = Range();
        this->r2 = Range();
    }

    //takes val from -1 to 1 and ranges it based on which range is selected
    float scale(float val, int range)
    {
        if (range == 1)
            return r1.scale(val);
        else if (range == 2)
            return r2.scale(val);
        else
            return 0;
    }

    //takes val from first range and scales it to the second range
    float scale1To2(float val)
    {
        return r2.scale(r1.inverceScale(val));
    }

    //takes val from second range and scales it to the first range
    float scale2To1(float val)
    {
        return r1.scale(r2.inverceScale(val));
    }
};