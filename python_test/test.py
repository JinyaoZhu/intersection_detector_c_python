import sys
sys.path.append('./build/lib.linux-x86_64-3.5/')

import intersection_detector
import numpy as np
import matplotlib.pyplot as plt

#genrate a map
height = 10
width = 10
map = np.zeros(height*width,dtype=np.uint8)
for i in range(height):
    for j in range(width):
        if ((i == 0) or (i == height - 1) or (j == 0) or (j == width - 1) or ((i > 3)and(j>3)and(i<height-3))):
            map[i*width + j] = 255
        else:
            map[i*width + j] = 0

map_img = map.reshape((height,height))
plt.imshow(map_img)

# setting rays
N_rays = 7
ray_start = np.array([3,3,3,3,3,3,8,
                      5,5,5,5,5,5,8],dtype=np.float32)

ray_end   = np.array([1,5,1,1,5,8,1,
                      1,1,8,5,5,5,1],dtype=np.float32)

# outputs
isect = np.zeros(N_rays,dtype=np.uint8)
ray_range = np.zeros(N_rays,dtype=np.float32)

# compute intersection
intersection_detector.do_detect(map,height,width,ray_start,ray_end,isect,ray_range)

# show results
for i in range(N_rays):
    print('Ray:%d \t Start point: [%5.2f,%5.2f]\t End point: [%5.2f, %5.2f]'%(i,ray_start[i],ray_start[i+N_rays],ray_end[i],ray_end[i+N_rays]))
print('\n')
for i in range(N_rays):
    print('Ray:%d \t intersect:%s \t range:%5.3f' % (i,"ture" if isect[i]==1 else "false",ray_range[i]))

plt.show()



