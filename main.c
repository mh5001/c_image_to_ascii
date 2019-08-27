#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

#define ASCII_LIST "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

typedef struct {
  int w;
  int h;
  unsigned int** data;
} Image;

void freeImage(Image img);
Image openImage(const char* path);
double luminance(int r, int g, int b);
int getRatio(double lum, int len);

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    puts("No path!");
    return 1;
  }
  int asciiLen = sizeof(ASCII_LIST) / sizeof(char);
  Image img = openImage(argv[1]);
  puts("Converting image to ascii...");
  FILE* output = fopen("result.txt", "w");
  for (size_t i = 0; i < img.h; i++) {
    for (size_t j = 0; j < img.w * 3; j += 3) {
      int r = img.data[i][j];
      int g = img.data[i][j + 1];
      int b = img.data[i][j + 2];
      double l = luminance(r, g, b);
      fprintf(output, "%c", ASCII_LIST[getRatio(l, asciiLen) - 1]);
    }
    fprintf(output, "\r\n");
  }
  fclose(output);
  freeImage(img);
  return 0;
}

Image openImage(const char* path) {
  int x, y, n;
  unsigned char* data = stbi_load(path, &x, &y, &n, 0);
  Image result = {x, y};
  result.data = malloc(y * sizeof(int*));
  puts("Reading image...");
  for (size_t i = 0; i < y; i++) {
    result.data[i] = malloc((x * 3) * sizeof(int));
  }

  for (size_t j = 0; j < y; j++) {
    for (size_t i = 0; i < x * 3; i++) {
      result.data[j][i] = data[i + (j * x * 3)];
    }
  }
  free(data);
  return result;
}

void freeImage(Image img) {
  for (size_t i = 0; i < img.h; i++) {
    free(img.data[i]);
  }
  free(img.data);
}

double luminance(int r, int g, int b) {
  return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

int getRatio(double lum, int len) {
  int ratio = (int)round((len - 1)/ 255.0 * lum);
  return ratio;
}
