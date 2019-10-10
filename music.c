#include <stdio.h>

// From https://www.reddit.com/r/programming/comments/d2nudv/music_from_code/


unsigned sound(unsigned i, unsigned x, unsigned n, unsigned t, unsigned o)
{
    // beat repeats the same pattern 3 times. The 4th
    // time, there are just tiny differences...
    char beat[4][8] = {{117, 140, 176, 105, 140, 117, 105, 88},
                       {117, 140, 176, 105, 140, 117, 105, 88},
                       {117, 140, 176, 105, 140, 117, 105, 88},
                       {132, 157, 176, 105, 157, 132, 105, 88}};


    char s = beat[n][t];

    // apparently, the 'magic' stuff is here...
    unsigned e = i*s / o;

    // x goes from 0 to 3 at a very slow rate
    // so we are basically only interested in 0, 1 or 2 bits
    // so this return either 0, 8, 16 or 24
    return(( x & e ) <<4 );
}

int main()
{
    for(unsigned i=0; ; i++){
        // at 8kHz, wait (1<<10)/8192 = 1/8 second
        // before this value is incremented
        unsigned t0125s = i/(1<<10);

        // at 8kHz, wait (1<<11)/8192 = 1/4 second
        // before this value is incremented
        unsigned t025s = i/(1<<11);

        // at 8kHz, wait (1<<13)/8192 = 1 second
        // before this value is incremented
        unsigned t1s = i/(1<<13);

        // at 8kHz, wait (1<<14)/8192 = 2 second
        // before this value is incremented
        unsigned t2s=i/(1<<14);

        // at 8kHz, wait (1<<16)/8192 = 8 second before
        // this value is incremented
        unsigned t8s = i/(1<<16);

        // at 8kHz, wait (1<<17)/8192 = 16 second
        // before this value is incremented
        unsigned t16s=i/(1<<17);

        unsigned x0 = 1;
        unsigned x1 = t16s % 4;     // '-'=16s  0-1-2-3-..
        unsigned x2 = (t16s/3) % 4; // '-'=48s  0-1-2-3-..
        unsigned x3 = (t16s/5) % 4; // '-'=80s  0-1-2-3-..

        unsigned tempo0 = t2s % 8; // '-'=2s  0-1-2-3-4-5-6-7..
        unsigned tempo1 = (t1s ^ t2s) % 8;
        unsigned tempo2 = ((t025s % 3) + t2s) % 8;
        unsigned tempo3 = (8 + t2s -(t0125s % 3) ) % 8;

        unsigned beat0 = sound(i, x0, t8s % 4, tempo1, 1<<12);
        // unsigned beat1 = sound(i, x1, t8s % 4, tempo1, 1<<10);
        // unsigned beat2 = sound(i, x2, t8s % 4, tempo2, 1<<10);
        //unsigned beat4 = sound(i, x3, t8s % 4, tempo3, 1<<9);

        //putchar(beat0 + beat1 + beat2 + beat4);

        putchar(beat0);
    }
    return 0;
}