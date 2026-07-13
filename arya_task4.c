
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int state=0;
char* statestr="LAUNCH_PAD";
float alts[3] ={0.0, 0.0, 0.0};
float max_alt=0.0;
float apogee_alt=0.0;
int count=0;
float P0=93913;

float convert(float currentp){
    return 44330.0 *(1.0-pow(currentp/ P0,0.190284));
}

void update_alts(float new_alt) {
    alts[0]=alts[1]; 
    alts[1]=alts[2]; 
    alts[2]=new_alt;
    
    if (new_alt>max_alt) {
        max_alt=new_alt;
    }
}

void update_state(){
    float oldest =alts[0];
    float middle =alts[1];
    float newest = alts[2];

switch(state) {
    case 0:
        if(oldest<middle && middle<newest && newest>0){
        state=1;
        statestr="ASCENT";
        }
        break;
    case 1:
        if(newest<max_alt-1.0) count++;
        else count=0;
        if(count==3) {state=2;
        statestr="APOGEE";
            apogee_alt=max_alt;
        }
        break;
    case 2:
        state=3;
        statestr="DESCENT";
        break;
    case 3:
        if(newest<=apogee_alt*0.8){
            state=4;
            statestr="PAYLOAD_RELEASE";
        }
        break;
    case 4:
        if(newest<=2.0){
            state=5;
            statestr="PROBE_RELEASE";
        }
        break;
    case 5:
        if(newest==0){
            state=6;
            statestr="LANDED";
        }
        break;
}  
}
int main() {
float data[]={93948, 93949, 93948, 93948, 93948, 93948, 93948, 93948, 93949, 93949,93949, 93949,   93948, 93948, 93948, 93948, 93947, 93947, 93947, 93947, 
   93946, 93829, 93085, 92016, 89603, 88575, 87836, 87232, 86794, 86251, 
        86205, 86166, 86216, 86374, 86533, 86691, 86850, 87010, 87169, 87329, 
        87488, 87649, 87809, 87970, 88130, 88291, 88507, 88722, 88938, 89154, 
        89371, 89589, 89806, 90024, 90243, 90462, 90681, 90901, 91121, 91342, 
        91563, 91709, 91765, 91821, 91878, 91934, 91990, 92046, 92102, 92158, 
        92214, 92271, 92327, 92383, 92439, 92496, 92552, 92608, 92665, 92721, 
        92778, 92834, 92891, 92947, 93004, 93061, 93117, 93174, 93231, 93287, 
        93344, 93401, 93458, 93514, 93571, 93628, 93685, 93742, 93799, 93856, 
        93913, 93913, 93913, 93913, 93913, 93912, 93913, 93913, 93913, 93913, 
        93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 
        93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 93913, 
        93913, 93913, 93913, 93912, 93912, 93912, 93913, 93912, 93913, 93912, 
        93913, 93912, 93914, 93914, 93914, 93914, 93914, 93914, 93914, 93914, 
        93914, 93914, 93914, 93914, 93914, 93914};
for(int i=0; i<(sizeof(data)/4); i++){
    float currentp=data[i];
    float currenta=convert(currentp);
    update_alts(currenta);
    update_state();
    printf("Current State is: %s \n", statestr);
}
    return 0;
}