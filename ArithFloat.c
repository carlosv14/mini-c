float sum(float a, float b){
    return a + b;
}

float substr(float a, float b){
    return a - b;
}

float multi(float a, float b){
    return a * b;
}

float divi(float a, float b){
    return a / b;
}

void main() {
    float x, y;

    x = 150.56;
    y = 10.25;

    printf("X= ");
    printf(x);
    printf("\n");
    printf("Y= ");
    printf(y);
    printf("\n");

    printf("Add: ");
    printf(sum(x, y));
    printf("\n");
    printf("Sub: ");
    printf(substr(x,y));
    printf("\n");
    printf("Mul: ");
    printf(multi(x,y));
    printf("\n");
    printf("Div: ");
    printf(divi(x,y));
    printf("\n");
}