
#ifndef Curves_h
#define Curves_h

#define slopeFromT(t,A,B,C)  (1.0f / (3.0f * A * t * t + 2.0f * B * t + C))
#define xFromT(t, A, B, C, D) (A * (t * t * t) + B * (t * t) + C * t + D)
#define yFromT(t, E, F, G, H) (E * (t * t * t) + F * (t * t) + G * t + H)

class Curves {
public:
    static inline float cubicBezier(float x, float a, float b, float c, float d){
        
        float y0a = 0.00f; // initial y
        float x0a = 0.00f; // initial x
        float y1a = b;    // 1st influence y
        float x1a = a;    // 1st influence x
        float y2a = d;    // 2nd influence y
        float x2a = c;    // 2nd influence x
        float y3a = 1.00f; // final y
        float x3a = 1.00f; // final x
        
        float A = x3a - 3.0f * x2a + 3.0f * x1a - x0a;
        float B = 3.0f * x2a - 6.0f * x1a + 3.0f * x0a;
        float C = 3.0f * x1a - 3.0f * x0a;
        float D = x0a;
        
        float E = y3a - 3.0f * y2a + 3.0f * y1a - y0a;
        float F = 3.0f * y2a - 6.0f * y1a + 3.0f * y0a;
        float G = 3.0f * y1a - 3.0f * y0a;
        float H = y0a;
        
        // Solve for t given x (using Newton-Raphelson), then solve for y given t.
        // Assume for the first guess that t = x.
        float currentt = x;
        int nRefinementIterations = 5;
        for (int i = 0; i < nRefinementIterations; i++){
            float currentx = xFromT (currentt,A,B,C,D);
            float currentslope = slopeFromT(currentt,A,B,C);
            currentt -= (currentx - x)*(currentslope);
            currentt = ofClamp(currentt, 0.0f, 1.0f);
        }
        
        return yFromT(currentt,E,F,G,H);
    }
    
    typedef std::function<double(double)> CurveFunction;
    
    CurveFunction easeInEaseOut = [&](double arg)->double {
        return pow(arg, 3) / (pow(arg, 3) + pow(1 - arg, 3));
    };

    CurveFunction easeOut = [&](double arg)->double {
        return 1 - pow(1 - arg, 3);
    };
    
    CurveFunction swiftOut = [&](double arg)->double {
        return cubicBezier(arg, 0.444f, 0.013f, 0.188f, 0.956f);
    };
};

#endif /* Curves_h */
