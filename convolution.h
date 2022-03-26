#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#define KERNEL_SIZE 25
#define MAX(a, b) (a > b ? a : b)

/*
 * src: memory location for previously computed images
 * dst: memory location for newly processed images
 * bias: Location for bias, value added to each pixel of an image
 * weights: memory location for filters
 * num_src: the number of images from the previous layer
 * num_dst: the number of images that will be produced from this layer
 * src_size: the size of each image from the previous layer C1 = 28 
 *
 */
void conv_layer(float *src, float *dst, float *bias, float *weights, int num_src, int num_dst, int src_size)
{
    int dst_size =  src_size - 4;
    int dst_index, src_index;
 
    for(int in = 0; in < num_src; in++)
    {
        // The image that will be convolved
        const float *image = &src[in * src_size];

        for(int out = 0; out < num_dst; out++)
        {
            // Pointer to where to store the output image
            float *output = &dst[out * dst_size * dst_size];

            // Bias value for this image
            float bi = bias[out];

            // Weight filter for this image
            // This calculation assumes that the weight vector only contains weights for
            // this specific layer.
            float *weight = &weights[out *KERNEL_SIZE];

            // Matrix dotsum
            for(int i = 2; i < src_size - 2; i++)
            {
                for(int j = 2; j < src_size - 2; j++)
                {
                    // Index for output value
                    dst_index = ((i - 2)*dst_size) + j - 2;

                    // starting index for source value
                    src_index = ((i - 2)*src_size) + j - 2;
                    output[dst_index] += 
                        //Row 1
                        image[src_index] * weight[0] + image[src_index + 1] * weight[1] + image[src_index + 2] * weight[2] + image[src_index + 3] * weight[3] + image[src_index + 4] * weight[4] + 
                        
                        //Row 2
                        image[src_index + src_size] * weight[5] + image[src_index + src_size + 1] * weight[6] + image[src_index + src_size + 2] * weight[7] + 
                        image[src_index + src_size + 3] * weight[8] + image[src_index + src_size + 4] * weight[9] +
                        
                        //Row 3
                        image[src_index + 2 * src_size] * weight[10] + image[src_index + 2 * src_size + 1] * weight[11] + image[src_index + 2 * src_size + 2] * weight[12] + 
                        image[src_index + 2 * src_size + 3] * weight[13] + image[src_index + 2 * src_size + 4] * weight[14] + 
                        
                        //Row 4
                        image[src_index + 3 * src_size] * weight[15] + image[src_index + 3 * src_size + 1] * weight[16] + image[src_index + 3 * src_size + 2] * weight[17] + 
                        image[src_index + 3 * src_size + 3] * weight[18] + image[src_index + 3 * src_size + 4] * weight[19] +
                        
                        //Row 5
                        image[src_index + 4 * src_size] * weight[20] + image[src_index + 4 * src_size + 1] * weight[21] + image[src_index + 4 * src_size + 2] * weight[22] + 
                        image[src_index + 4 * src_size + 3] * weight[23] + image[src_index + 4 * src_size + 4] * weight[24];

                        // Activation (ReLU function)
                        // Could also try sigmoid function
                        output[dst_index] = MAX(0, output[dst_index] + bi);


                }
            }
        }
    }
}

#endif // _CONVOLUTION_H_