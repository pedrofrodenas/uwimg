#include <math.h>
#include "image.h"

float nn_interpolate(image im, int c, float h, float w)
{
    // TODO
    // Nearest Neightbour interpolation
    return get_pixel(im, c, roundf(h), roundf(w));
}

image nn_resize(image im, int h, int w)
{
    // TODO
    image imageResized = make_image(im.c, h, w);

    // Get resizing coeficients
    float Sx, Sy = 0.f;
    Sx = w/(float)im.w;
    Sy = h/(float)im.h;

    float Xorig, Yorig = 0.f;
    float pixel = 0.f;
    for (int c=0; c!=im.c; c++)
    {
        for (int y=0; y!=h; y++)
        {
        // Original coordinate system position calculation
        //   Reescale + Grid Shifting  
        Yorig = (y/Sy)+(0.5f/Sy)-0.5f;
            for (int x=0; x!=w; x++)
            {
                Xorig = (x/Sx)+(0.5f/Sx)-0.5f;
                pixel = nn_interpolate(im, c, Yorig, Xorig);
                set_pixel(imageResized, c, y, x, pixel);
            }
        }
    }
    return imageResized;
}

float bilinear_interpolate(image im, int c, float h, float w)
{

    int truncatedx = (int)w;
    int truncatedy = (int)h;

    // Coorners coordinates with int values
    int x1, x2, y1, y2;
    // Variables to place pixel values of coorners coordinates
    float v1, v2, v3, v4;
    // Variables to place calculated distances (d) and interpolated values (q)
    float d1,d2,d3,d4,q1,q2,q=0.f;

    // Arreglar esto para contemplar estos corner case 
    if ( (truncatedx == w) && (truncatedy == h))
    {
        return get_pixel(im,c, truncatedy, truncatedx);
    }
    else if (truncatedx == w)
    {
        y1 = floor(h);
        y2 = ceil(h);

        v1 = get_pixel(im, c, y1, truncatedx);
        v3 = get_pixel(im, c, y2, truncatedx);

        d3 = h-y1;
        d4 = y2-h;

        q = v1*d4+v3*d3;
        return q;
    }
    else if (truncatedy == h)
    {
        x1 = floor(w);
        x2 = ceil(w);

        v1 = get_pixel(im, c, truncatedy, x1);
        v2 = get_pixel(im, c, truncatedy, x2);

        d1 = w-x1;
        d2 = x2-w;

        q = v1*d2+v2*d1;
        return q;
    }

    // TODO
    x1 = floor(w);
    x2 = ceil(w);
    y1 = floor(h);
    y2 = ceil(h);

    // Get sorrounding pixels
    v1 = get_pixel(im, c, y1, x1);
    v2 = get_pixel(im, c, y1, x2);
    v3 = get_pixel(im, c, y2, x1);
    v4 = get_pixel(im, c, y2, x2);

    d1 = w-x1;
    d2 = x2-w;

    q1 = v1*d2+v2*d1;
    q2 = v3*d2+v4*d1;

    d3 = h-y1;
    d4 = y2-h;

    q = q1*d4+q2*d3;
    return q;
}

image bilinear_resize(image im, int h, int w)
{
	// TODO
	image imageResized = make_image(im.c, h, w);
    
	// Get resizing coeficients
	float Sx, Sy = 0;
	Sx = w/(float)im.w;
	Sy = h/(float)im.h;
    float Xorig, Yorig = 0;
    for (int c=0; c!=im.c; c++)
    {
        for (int y=0; y!=h; y++)
	    {
            Yorig = (y/Sy)+(0.5/Sy)-0.5;
            for (int x=0; x!=w; x++)
            {
                Xorig = (x/Sx)+(0.5/Sx)-0.5;
                set_pixel(imageResized, c, y, x, bilinear_interpolate(im, c, Yorig, Xorig));  
            } 
        }
    }
	return imageResized;
}

