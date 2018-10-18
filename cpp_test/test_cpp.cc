// compile: g++ -o test_cpp intersection_detector.cxx test_cpp.cc 
// run: ./test_cpp

#include "intersection_detector.h"
#include <iostream>
#include <stdio.h>

int main()
{
    std::cout << "Test intersection_detector..." << std::endl;

    const int height = 7;
    const int width = 9;

    bool map[height*width];

    int N_ray = 8;

    // genrate a map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i <= 1) || (i >= height - 2)||(j <= 1) || (j >= width - 2))
                map[i*width + j] = false; // obstacle
            else
                map[i*width + j] = true;  // free
        }
    }

    // display the map
    printf("Map:\n");
    printf("            ");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i*width + j] == true)
                printf("  "); // free
            else
                printf("* "); // obstacle
        }
        printf("\n");
        printf("            ");
    }
    printf("\n");

    // give start and end points
    float startPoint[N_ray * 2] = {4,4,4,4,4,4,4,4,
                                   3,3,3,3,3,3,3,3};
    float endPoint[N_ray * 2] = {7,7,4,1,1,1,4,7,
                                 3,1,1,1,3,5,5,5};

    printf("Inputs:\n");
    for (int i = 0; i < N_ray; i++)
    {
        printf("Ray:%d \t Start point: [%5.2f,%5.2f]\t End point: [%5.2f, %5.2f]\n",
               i, startPoint[i], startPoint[N_ray + i], endPoint[i], endPoint[N_ray + i]);
    }

    bool intsec[N_ray];
    float range[N_ray];

    IntersectionDetector ISD(map, height, width);

    ISD.detect(startPoint, endPoint, N_ray, intsec, range);


    printf("\nResults:\n");
    for (int i = 0; i < N_ray; i++)
    {
        printf("Ray:%d \t intersect:%s \t range:%5.3f\n",i,(intsec[i]?"true":"false"),range[i]);
    }

    return 0;
}