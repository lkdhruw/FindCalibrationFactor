#include <stdio.h>

float known_w = 21.0f;

float get_value(int factor) {
  return 5.0f*(factor/8000.0);
}

int main(void) {
  int factor_x = 20000;
  int step = 1000;
  float val_x = get_value(factor_x);
  float val_x_m1 = get_value(factor_x-step);
  float val_x_p1 = get_value(factor_x+step);
  float diff = 0.0f;

  // Integrity check
  if(val_x_m1 < val_x && val_x_p1 < val_x) {
    printf("Data integrity error");
    return 0;
  } else if (val_x_m1 > val_x && val_x_p1 > val_x) {
    printf("Data integrity error");
    return 0;
  }

  if(val_x_m1 > val_x) {
    step = -step;
  }

  printf("x= %f, x-1=%f, x+1=%f\n",val_x, val_x_m1, val_x_p1);

  if(known_w < val_x) {
    diff = val_x - known_w;
    while(diff > 0.1) {
      if (known_w >  get_value(factor_x-step)) {
        step = step/10;
      }
      factor_x = factor_x - step;
      diff = get_value(factor_x) - known_w;
    }
    printf("Final calibration factor: %d", factor_x);
  } else if (known_w > val_x) {
    diff = known_w - val_x;
    while(diff > 0.1) {
      if (known_w <  get_value(factor_x+step)) {
        step = step/10;
      }
      factor_x = factor_x + step;
      diff = known_w - get_value(factor_x);
    }
    printf("Final calibration factor: %d", factor_x);
  } else {
    printf("Final calibration factor: %d", factor_x);
  }

  return 0;
}

