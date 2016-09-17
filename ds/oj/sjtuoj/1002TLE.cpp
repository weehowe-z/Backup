//二哥种花生 注意算法效率
#include <iostream>
using namespace std;

int main()
{
    unsigned int all_length, all_width;
    unsigned int avai_length, avai_width;
    unsigned int * max;
    unsigned int max_last=0, max_now, max_diff = 0, max_last_final = 0;
    unsigned int **avai_num = NULL;

    cin>>all_length>>all_width;

    avai_num = new unsigned int* [all_length];

    for(unsigned int i = 0; i < all_length; i++)
    {
        avai_num[i] = new unsigned int[all_width];
    }

    for(unsigned int i = 0; i < all_length; i++){
        for(unsigned int j = 0; j < all_width; j++){
            cin>>avai_num[i][j];
        }
    }

    cin>>avai_length>>avai_width;

    if(avai_width >= all_length){
        max = new unsigned  int [all_length - avai_length + 1];
        for(unsigned int i = 0; i < all_length - avai_length + 1; i++){
            max[i] = 0;
        }
        for(unsigned int i = 0; i < avai_length; i++){
            for(unsigned int j = 0; j < avai_width; j++)
                max[0] += avai_num[i][j];
        }
        for(unsigned int i = 1; i < all_length - avai_length + 1; i++){
                for(unsigned int j = 0; j < avai_width; j++){
                    max_diff += avai_num[i+avai_length-1][j] - avai_num[i-1][j];
                }
                max[i]= max[i-1]+max_diff;
                max_diff = 0;
        }

        max_diff=0;
        for(unsigned int i = 0; i < all_length -avai_length + 1; i++){
            max_last_final = max[i];
            for(unsigned int j = 1; j < all_width -avai_width + 1; j++){
                for(unsigned int k = 0; k < avai_length; k++){
                    max_diff += avai_num[i+k][j+avai_width-1] - avai_num[i+k][j-1];
                }
                max_now = max_last_final + max_diff;
                max_last_final = max_now;
                if(max_now > max[i]) max[i] = max_now;
                max_diff = 0;
            }
        }

        for(unsigned int i = 0; i < all_length - avai_length + 1; i++){
            if(max_last_final < max[i]) max_last_final = max[i];
        }
        cout<<max_last_final;
    }
    else{
        max = new unsigned  int [all_width - avai_width + 1];
        for(unsigned int i = 0; i < all_width - avai_width + 1; i++){
            max[i] = 0;
        }
        for(unsigned int i = 0; i < avai_length; i++){
            for(unsigned int j = 0; j < avai_width; j++)
                max[0] += avai_num[i][j];
        }
        for(unsigned int i = 1; i < all_width - avai_width + 1; i++){
                for(unsigned int j = 0; j < avai_length; j++){
                    max_diff += avai_num[j][i+avai_width-1] - avai_num[j][i-1];
                }
                max[i]= max[i-1]+max_diff;
                max_diff = 0;
        }
        max_diff=0;
        for(unsigned int i = 0; i < all_width -avai_width + 1; i++){
            max_last_final = max[i];
            for(unsigned int j = 1; j < all_length -avai_length + 1; j++){
                for(unsigned int k = 0; k < avai_width; k++){
                    max_diff += avai_num[j+avai_length-1][i+k] - avai_num[j-1][i+k];
                }
                max_now = max_last_final + max_diff;
                max_last_final = max_now;
                if(max_now > max[i]) max[i] = max_now;
                max_diff = 0;
            }
        }

        for(unsigned int i = 0; i < all_width - avai_width + 1; i++){
            if(max_last_final < max[i]) max_last_final = max[i];
        }
        cout<<max_last_final;
    }
    for(unsigned int i = 0; i < all_length; i++)
    {
        delete [] avai_num[i];
    }

    delete [] avai_num;
    delete [] max;
    return 0;
}
