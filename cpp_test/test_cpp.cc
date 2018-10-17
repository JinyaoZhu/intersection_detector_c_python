// compile: g++ -o test_cpp intersection_detector.cxx test_cpp.cc 
// run: ./test_cpp

#include "intersection_detector.h"
#include <iostream>
#include <stdio.h>

int main()
{
    std::cout << "Test intersection_detector..." << std::endl;

    bool map[100];
    int height = 10;
    int width = 10;

    int N_ray = 7;

    // genrate a map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0) || (i == height - 1) || (j == 0) || (j == width - 1) || ((i > 3)&&(j>3)&&(i<height-3)))
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
    float startPoint[N_ray * 2] = {3,3,3,3,3,3,8,
                                   5,5,5,5,5,5,8};
    float endPoint[N_ray * 2] = {1,5,1,1,5,8,1,
                                 1,1,8,5,5,5,1};

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