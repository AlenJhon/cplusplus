#include <limits.h>
#include <stdio.h>

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define MIN(a, b) (((a) <= (b)) ? (a) : (b))


double 
find_median_sorted_arrays(int *nums1, int nums1size, int *nums2, int nums2size) {
    
    int halfsize = 0;
    int headpos, tailpos, half1, half2;
    int nums1left, nums1right, nums2left, nums2right;
    
    if (nums1size > nums2size) {
        return find_median_sorted_arrays(nums2, nums2size, nums1, nums1size);
    }
    halfsize = nums1size + nums2size;

    headpos = 0;
    tailpos = 2 * nums1size;
    
    while (headpos <= tailpos) {
        half1 = headpos + (tailpos - headpos) / 2;
        half2 = halfsize - half1;
        
        nums1left = (half1 == 0) ? INT_MIN : nums1[ (half1-1) / 2];
        nums2left = (half2 == 0) ? INT_MIN : nums2[ (half2-1) / 2];
        
        nums1right = (half1 == 2*nums1size) ? INT_MAX : nums1[half1 / 2];
        nums2right = (half2 == 2*nums2size) ? INT_MAX : nums2[half2 / 2];
    
        if (nums1left > nums2right) {
            tailpos = half1 - 1;
        } else if ( nums2left > nums1right) {
            headpos = half1 + 1;
        } else {
            break;
        }
    }
    printf("nums1left:%d, nums1left:%d, nums1right:%d, nums2right:%d\n", nums1left, nums2left, nums1right, nums2right ); 
    double ret = (MAX(nums1left, nums2left) + MIN(nums1right, nums2right)) / 2.0;
    printf("ret:%f\n", ret);

    return (MAX(nums1left, nums2left) + MIN(nums1right, nums2right) ) / 2.0;
}



int main(void) {

    int nums1[5] = {1, 2, 3, 4, 5};
    int nums1size = 5;
    int nums2[5] = {2, 3, 4, 5, 6};
    int nums2size = 5;
    //int nums1[2] = {1, 2};
    //int nums1size = 2;
    //int nums2[4] = {3, 4, 5, 6};
    //int nums2size = 4;
    
    printf("result : %lf\n", find_median_sorted_arrays(nums1, nums1size, nums2, nums2size));

    return 0;
}
