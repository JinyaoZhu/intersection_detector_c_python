// interdection_detector.cxx

/*******************************************************
 * test rays for intersection with an obstacle grid map and optionally 
 * return the distance from the start point to the first obstacle.
 * Outputs: 
 * - intersection = true for each ray that intersects an obstacle
 * - range = distance from start to first obstacle or (-1) when no intersection was found
 *Inputs:
 * - obstacles: matrix (uint8 or mxLogical), map of obstacles
 * - rayStart: Mx2 matrix of ray start coordinates (relative to map)
 * - rayEnd: Mx2 matrix of ray end coordinates (relative to map)
 */

// #include "stdio.h"
#define FAST_SQRT

#include "interdection_detector.h"

#ifndef FAST_SQRT
#include "math.h"
#endif

IntersectionDetector::IntersectionDetector(const bool *p_map, const int map_hight, const int map_width)
{
  pMap = (bool *)p_map;
  width = map_width;
  height = map_width;
  pitch = height;
  // printf("Created an IntersectionDetector...\n");
}

IntersectionDetector::IntersectionDetector()
{
  // printf("Created an empty IntersectionDetector...\n");
}

void IntersectionDetector::detect(const float *ray_start, const float *ray_end, const int num_of_rays, bool *p_isec, float *p_range)
{
  bool obstacleValue = false; //which value in the map should be treated as obstacle
  count = num_of_rays;        // number fo rays
  rayStart.pX = (float *)ray_start;
  rayStart.pY = rayStart.pX + count;
  rayEnd.pX = (float *)ray_end;
  rayEnd.pY = rayEnd.pX + count;

  mxISect_ = p_isec;
  bool *pISect = mxISect_;
  float *pRange = p_range;

  for (int i = 0; i < count; i++)
  {
    int xs = (int)((*rayStart.pX++) + 0.5); /* add rounding constant of 0.5 */
    int ys = (int)((*rayStart.pY++) + 0.5);
    if (xs >= 0 && ys >= 0 && xs < width && ys < height)
    {
      if (pMap[xs * pitch + ys] != obstacleValue)
      {
        int xe = (int)((*rayEnd.pX++) + 0.5);
        int ye = (int)((*rayEnd.pY++) + 0.5);

        int dx = xe - xs;
        int dy = ye - ys;
        int x, y, prevX, prevY;
        bool isect;

#define CHECK_CELL                          \
  if (pMap[x * pitch + y] != obstacleValue) \
  {                                         \
    prevX = x;                              \
    prevY = y;                              \
  }                                         \
  else                                      \
  {                                         \
    prevX = x;                              \
    prevY = y;                              \
    break;                                  \
  }

        if (dx >= 0)
        { /* octants 1, 2, 7, 8 */
          if (dy >= 0)
          {               /* octants 1, 2 */
            if (dx >= dy) //Bresenham algorithm
            {             /* octant 1 */
              int error = dx >> 1;
              int xe_ = xe < width ? xe : (width - 1);
              for (prevX = x = xs, prevY = y = ys; x <= xe_; x++)
              {
                CHECK_CELL
                error -= dy;
                if (error < 0)
                {
                  if (++y >= height)
                    break;
                  error += dx;
                }
              }
              isect = (x <= xe);
            }
            else
            { /* octant 2 */
              int error = dy >> 1;
              int ye_ = ye < height ? ye : (height - 1);
              for (prevX = x = xs, prevY = y = ys; y <= ye_; y++)
              {
                CHECK_CELL
                error -= dx;
                if (error < 0)
                {
                  if (++x >= width)
                    break;
                  error += dy;
                }
              }
              isect = (y <= ye);
            }
          }
          else
          { /* octants 7, 8 */
            dy = -dy;
            if (dx >= dy)
            { /* octant 8 */
              int error = dx >> 1;
              int xe_ = xe < width ? xe : (width - 1);
              for (prevX = x = xs, prevY = y = ys; x <= xe_; x++)
              {
                CHECK_CELL
                error -= dy;
                if (error < 0)
                {
                  if (--y < 0)
                    break;
                  error += dx;
                }
              }
              isect = (x <= xe);
            }
            else
            { /* octant 7 */
              int error = dy >> 1;
              int ye_ = ye < 0 ? 0 : ye;
              for (prevX = x = xs, prevY = y = ys; y >= ye_; y--)
              {
                CHECK_CELL
                error -= dx;
                if (error < 0)
                {
                  if (++x >= width)
                    break;
                  error += dy;
                }
              }
              isect = (y >= ye);
            }
          }
        }
        else
        { /* octants 3-6 */
          dx = -dx;
          if (dy >= 0)
          { /* octants 3, 4 */
            if (dx >= dy)
            { /* octant 4 */
              int error = dx >> 1;
              int xe_ = xe < 0 ? 0 : xe;
              for (prevX = x = xs, prevY = y = ys; x >= xe_; x--)
              {
                CHECK_CELL
                error -= dy;
                if (error < 0)
                {
                  if (++y >= height)
                    break;
                  error += dx;
                }
              }
              isect = (x >= xe);
            }
            else
            { /* octant 3 */
              int error = dy >> 1;
              int ye_ = ye < height ? ye : (height - 1);
              for (prevX = x = xs, prevY = y = ys; y <= ye_; y++)
              {
                CHECK_CELL
                error -= dx;
                if (error < 0)
                {
                  if (--x < 0)
                    break;
                  error += dy;
                }
              }
              isect = (y <= ye);
            }
          }
          else
          { /* octants 5, 6 */
            dy = -dy;
            if (dx >= dy)
            { /* octant 5 */
              int error = dx >> 1;
              int xe_ = xe < 0 ? 0 : xe;
              for (prevX = x = xs, prevY = y = ys; x >= xe_; x--)
              {
                CHECK_CELL
                error -= dy;
                if (error < 0)
                {
                  if (--y < 0)
                    break;
                  error += dx;
                }
              }
              isect = (x >= xe);
            }
            else
            { /* octant 6 */
              int error = dy >> 1;
              int ye_ = ye < 0 ? 0 : ye;
              for (prevX = x = xs, prevY = y = ys; y >= ye_; y--)
              {
                CHECK_CELL
                error -= dx;
                if (error < 0)
                {
                  if (--x < 0)
                    break;
                  error += dy;
                }
              }
              isect = (y >= ye);
            }
          }
        }
#undef CHECK_CELL

        *pISect++ = isect;

        #ifdef FAST_SQRT
        *pRange++ = isect ? (1.0 / inv_sqrt((prevX - xs) * (prevX - xs) + (prevY - ys) * (prevY - ys))) : -1.0;
        #else
         *pRange++ = isect ? sqrt((double)((prevX - xs) * (prevX - xs) + (prevY - ys) * (prevY - ys))) : -1.0;
        #endif
        
        continue;
      }
    }

    // ray starts off the map or the start position is an obstacle
    *pISect++ = true;
    if (pRange)
      *pRange++ = 0.0;
  }
}

float IntersectionDetector::inv_sqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y)); // 1st iteration
  y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

  return y;
}
