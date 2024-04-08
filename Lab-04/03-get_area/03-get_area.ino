struct Trialgle
{
    float W;
    float H;
};


void get_area_triangle(float width,float height){
    float area;
    area = 0.5 * width * height;
    Serial.printf("Area = %.2f\n\n", area);
}

void setup()
{
    Serial.begin(115200);
    Trialgle Triangle_A = {3, 6};
    Trialgle Triangle_B = {12, 6};

    get_area_triangle(Triangle_A.W ,Triangle_A.H);
    get_area_triangle(Triangle_B.W ,Triangle_B.H);
}

void loop()
{
}


