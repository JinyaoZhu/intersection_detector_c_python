
class IntersectionDetector
{
  public:
    IntersectionDetector(const bool *p_map, const int map_hight, const int map_width);

    IntersectionDetector();
    
    void detect(const float *ray_start, const float *ray_end, const int num_of_rays, bool *p_isec, float *p_range);

  private:
    bool *pMap;
    int width, height;
    unsigned pitch, count;
    struct
    {
        float *pX;
        float *pY;
    } rayStart, rayEnd;
  
  private:
    float inv_sqrt( float number);

    bool *mxISect_;  // output intersection
    float *mxRange_; // output range
};