#include <math.h>
#include <stdint.h>

void edge_filter (const uint32_t image_in[128][128], uint32_t image_out[128][128])
{
  int y, x;

  static int cx[9]={-1,0,1,
                    -1,0,1,
                    -1,0,1};
  static int cy[9]={-1,-1,-1,
                    0, 0, 1,
                    1, 1, 1};

  int d[9];

  for (x = 0; x < 128; x++) {
    image_out[0][x] = 0;
  }
  for (y = 1; y < 128-1; y++) {
    image_out[y][0] = 0;
    for (x = 1; x < 128-1; x++) {
      d[0]=image_in[y-1][x-1];
      d[1]=image_in[y-1][x];
      d[2]=image_in[y-1][x+1];
      d[3]=image_in[y]  [x-1];
      d[4]=image_in[y]  [x];
      d[5]=image_in[y]  [x+1];
      d[6]=image_in[y+1][x-1];
      d[7]=image_in[y+1][x];
      d[8]=image_in[y+1][x+1];
      int x_edge=cx[0]*d[0]+cx[1]*d[1]+cx[2]*d[2]
	+cx[3]*d[3]+cx[4]*d[4]+cx[5]*d[5]
	+cx[6]*d[6]+cx[7]*d[7]+cx[8]*d[8];
      int y_edge=cy[0]*d[0]+cy[1]*d[1]+cy[2]*d[2]
	+cy[3]*d[3]+cy[4]*d[4]+cy[5]*d[5]
	+cy[6]*d[6]+cy[7]*d[7]+cy[8]*d[8];
      image_out[y][x]=sqrtf(x_edge * x_edge + y_edge * y_edge);
    }
    image_out[y][127] = 0;
  }
  for (x = 0; x < 128; x++) {
    image_out[127][x] = 0;
  }

  return;
}
