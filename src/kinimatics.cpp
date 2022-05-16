class KinimaticPart{
    public:
    float length;
    bool rotAxis[3];
    
    KinimaticPart(float length, bool rotAxis[3]){
        this -> length = length;    
    }

    KinimaticPart(){}
};

class Kinimatics{
    KinimaticPart p = KinimaticPart(); 
};