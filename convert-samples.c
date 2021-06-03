/*
This file is part of convert-samples, a program to convert samples
received from software defined radios from one format to another.

Copyright 2021 Guillaume LE VAILLANT

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <complex.h>
#include <getopt.h>
#include <stdio.h>
#include <strings.h>


typedef enum
  {
    UNKNOWN,
    S8,
    U8,
    S16,
    U16,
    S32,
    U32,
    F32,
    CS8,
    CU8,
    CS16,
    CU16,
    CS32,
    CU32,
    CF32
  } format_t;

typedef union
{
  char s8;
  unsigned char u8;
  short int s16;
  unsigned short int u16;
  int s32;
  unsigned int u32;
  float f32;
  char cs8[2];
  unsigned char cu8[2];
  short int cs16[2];
  unsigned short int cu16[2];
  int cs32[2];
  unsigned int cu32[2];
  float complex cf32;
} sample_t;


format_t get_format(char *name)
{
  format_t format;

  if(strcasecmp(name, "s8") == 0)
  {
    format = S8;
  }
  else if(strcasecmp(name, "u8") == 0)
  {
    format = U8;
  }
  else if(strcasecmp(name, "s16") == 0)
  {
    format = S16;
  }
  else if(strcasecmp(name, "u16") == 0)
  {
    format = U16;
  }
  else if(strcasecmp(name, "s32") == 0)
  {
    format = S32;
  }
  else if(strcasecmp(name, "u32") == 0)
  {
    format = U32;
  }
  else if(strcasecmp(name, "f32") == 0)
  {
    format = F32;
  }
  if(strcasecmp(name, "cs8") == 0)
  {
    format = CS8;
  }
  else if(strcasecmp(name, "cu8") == 0)
  {
    format = CU8;
  }
  else if(strcasecmp(name, "cs16") == 0)
  {
    format = CS16;
  }
  else if(strcasecmp(name, "cu16") == 0)
  {
    format = CU16;
  }
  else if(strcasecmp(name, "cs32") == 0)
  {
    format = CS32;
  }
  else if(strcasecmp(name, "cu32") == 0)
  {
    format = CU32;
  }
  else if(strcasecmp(name, "cf32") == 0)
  {
    format = CF32;
  }
  else
  {
    format = UNKNOWN;
  }

  return(format);
}

int read_input_sample(FILE *input, format_t input_format, sample_t *sample)
{
  sample_t x;

  switch(input_format)
  {
  case S8:
    if(fread(&x.s8, 1, 1, input) == 1)
    {
      sample->cf32 = x.s8 / 128.0;
    }
    else
    {
      return(0);
    }
    break;

  case U8:
    if(fread(&x.u8, 1, 1, input) == 1)
    {
      sample->cf32 = (x.u8 - 127) / 128.0;
    }
    else
    {
      return(0);
    }
    break;

  case S16:
    if(fread(&x.s16, 2, 1, input) == 1)
    {
      sample->cf32 = x.s16 / 32768.0;
    }
    else
    {
      return(0);
    }
    break;

  case U16:
    if(fread(&x.u16, 2, 1, input) == 1)
    {
      sample->cf32 = (x.u16 - 32767) / 32768.0;
    }
    else
    {
      return(0);
    }
    break;

  case S32:
    if(fread(&x.s32, 4, 1, input) == 1)
    {
      sample->cf32 = x.s32 / 2147483648.0;
    }
    else
    {
      return(0);
    }
    break;

  case U32:
    if(fread(&x.u32, 4, 1, input) == 1)
    {
      sample->cf32 = (x.u32 - 2147483647) / 2147483648.0;
    }
    else
    {
      return(0);
    }
    break;

  case F32:
    if(fread(&x.f32, 4, 1, input) == 1)
    {
      sample->cf32 = x.f32;
    }
    else
    {
      return(0);
    }
    break;

  case CS8:
    if(fread(&x.cs8, 2, 1, input) == 1)
    {
      sample->cf32 = (x.cs8[0] + I * x.cs8[1]) / 128.0;
    }
    else
    {
      return(0);
    }
    break;

  case CU8:
    if(fread(&x.cu8, 2, 1, input) == 1)
    {
      sample->cf32 = ((x.cu8[0] - 127) + I * (x.cu8[1] - 127)) / 128.0;
    }
    else
    {
      return(0);
    }
    break;

  case CS16:
    if(fread(&x.cs16, 4, 1, input) == 1)
    {
      sample->cf32 = (x.cs16[0] + I * x.cs16[1]) / 32768.0;
    }
    else
    {
      return(0);
    }
    break;

  case CU16:
    if(fread(&x.cu16, 2, 1, input) == 1)
    {
      sample->cf32 = ((x.cu16[0] - 32767) + I * (x.cu16[1] - 32767)) / 32768.0;
    }
    else
    {
      return(0);
    }
    break;

  case CS32:
    if(fread(&x.cs32, 8, 1, input) == 1)
    {
      sample->cf32 = (x.cs32[0] + I * x.cs32[1]) / 2147483648.0;
    }
    else
    {
      return(0);
    }
    break;

  case CU32:
    if(fread(&x.cu32, 8, 1, input) == 1)
    {
      sample->cf32 = ((x.cu32[0] - 2147483647) + I * (x.cu32[1] - 2147483647)) / 2147483648.0;
    }
    else
    {
      return(0);
    }
    break;

  case CF32:
    if(fread(&x.cf32, 8, 1, input) == 1)
    {
      sample->cf32 = x.cf32;
    }
    else
    {
      return(0);
    }
    break;

  default:
    return(0);
  }

  return(1);
}

void write_output_sample(FILE *output, format_t output_format, sample_t sample)
{
  sample_t x;

  switch(output_format)
  {
  case S8:
    x.s8 = crealf(sample.cf32 * 128.0);
    fwrite(&x.s8, 1, 1, output);
    break;

  case U8:
    x.u8 = crealf(sample.cf32 * 128.0) + 127;
    fwrite(&x.u8, 1, 1, output);
    break;

  case S16:
    x.s16 = crealf(sample.cf32 * 32768.0);
    fwrite(&x.s16, 2, 1, output);
    break;

  case U16:
    x.u16 = crealf(sample.cf32 * 32768.0) + 32767;
    fwrite(&x.u16, 2, 1, output);
    break;

  case S32:
    x.s32 = crealf(sample.cf32 * 2147483648.0);
    fwrite(&x.s32, 4, 1, output);
    break;

  case U32:
    x.s32 = crealf(sample.cf32 * 2147483648.0) + 2147483647;
    fwrite(&x.u32, 4, 1, output);
    break;

  case F32:
    x.f32 = crealf(sample.cf32);
    fwrite(&x.f32, 4, 1, output);
    break;

  case CS8:
    x.cs8[0] = crealf(sample.cf32 * 128.0);
    x.cs8[1] = cimagf(sample.cf32 * 128.0);
    fwrite(&x.cs8, 2, 1, output);
    break;

  case CU8:
    x.cu8[0] = crealf(sample.cf32 * 128.0) + 127;
    x.cu8[1] = cimagf(sample.cf32 * 128.0) + 127;
    fwrite(&x.cu8, 2, 1, output);
    break;

  case CS16:
    x.cs16[0] = crealf(sample.cf32 * 32768.0);
    x.cs16[1] = cimagf(sample.cf32 * 32768.0);
    fwrite(&x.cs16, 4, 1, output);
    break;

  case CU16:
    x.cu16[0] = crealf(sample.cf32 * 32768.0) + 32767;
    x.cu16[1] = cimagf(sample.cf32 * 32768.0) + 32767;
    fwrite(&x.cu16, 4, 1, output);
    break;

  case CS32:
    x.cs32[0] = crealf(sample.cf32 * 2147483648.0);
    x.cs32[1] = cimagf(sample.cf32 * 2147483648.0);
    fwrite(&x.cs32, 8, 1, output);
    break;

  case CU32:
    x.cu32[0] = crealf(sample.cf32 * 2147483648.0) + 2147483647;
    x.cu32[1] = cimagf(sample.cf32 * 2147483648.0) + 2147483647;
    fwrite(&x.cu32, 8, 1, output);
    break;

  case CF32:
    fwrite(&sample.cf32, 8, 1, output);
    break;

  default:
    break;
  }
}

void convert(FILE *input, format_t input_format, FILE *output, format_t output_format)
{
  sample_t sample;

  while(read_input_sample(input, input_format, &sample))
  {
    write_output_sample(output, output_format, sample);
  }
}

void usage()
{
  printf("convert-samples version 1.0.0\n");
  printf("\n");
  printf("Usage: convert-samples -f <fmt> -t <fmt> [-i <file>] [-o <file>]\n");
  printf("\n");
  printf("Options:\n");
  printf("  -f <fmt>\n");
  printf("    Format of input samples.\n");
  printf("  -t <fmt>\n");
  printf("    Format of output samples.\n");
  printf("  -i <file>  [default: stdin]\n");
  printf("    Read input samples from 'file'.\n");
  printf("  -o <file>  [default: stdout]\n");
  printf("    Write output samples to 'file'.\n");
  printf("\n");
  printf("Supported formats:\n");
  printf("  - s8: signed 8 bit integer\n");
  printf("  - u8: unsigned 8 bit integer\n");
  printf("  - s16: signed 16 bit integer\n");
  printf("  - u16: unsigned 16 bit integer\n");
  printf("  - s32: signed 32 bit integer\n");
  printf("  - u32: unsigned 32 bit integer\n");
  printf("  - f32: 32 bit float\n");
  printf("  - cs8: complex made of signed 8 bit integers\n");
  printf("  - cu8: complex made of unsigned 8 bit integers\n");
  printf("  - cs16: complex made of signed 16 bit integers\n");
  printf("  - cu16: complex made of unsigned 16 bit integers\n");
  printf("  - cs32: complex made of signed 32 bit integers\n");
  printf("  - cu32: complex made of unsigned 32 bit integers\n");
  printf("  - cf32: complex made of 32 bit floats\n");
}

int main(int argc, char **argv)
{
  int opt;
  FILE *input = stdin;
  FILE *output = stdout;
  format_t input_format = UNKNOWN;
  format_t output_format = UNKNOWN;

  while((opt = getopt(argc, argv, "f:hi:o:t:")) != -1)
  {
    switch(opt)
    {
    case 'f':
      input_format = get_format(optarg);
      break;

    case 'h':
      usage();
      return(0);

    case 'i':
      input = fopen(optarg, "rb");
      if(input == NULL)
      {
        fprintf(stderr, "Error: Failed to open '%s'\n", optarg);
        return(-1);
      }
      break;

    case 'o':
      output = fopen(optarg, "wb");
      if(output == NULL)
      {
        fprintf(stderr, "Error: Failed to open '%s'\n", optarg);
        return(-1);
      }
      break;

    case 't':
      output_format = get_format(optarg);
      break;

    default:
      fprintf(stderr, "Error: Unknown parameter: '-%c %s'\n", opt, optarg);
      return(-1);
    }
  }
  if(optind < argc)
  {
    fprintf(stderr, "Error: Unknown parameter: '%s'\n", argv[optind]);
    return(-1);
  }

  if(input_format == UNKNOWN)
  {
    fprintf(stderr, "Error: Unknown input format\n");
    return(-1);
  }
  if(output_format == UNKNOWN)
  {
    fprintf(stderr, "Error: Unknown output format\n");
    return(-1);
  }

  convert(input, input_format, output, output_format);

  fclose(input);
  fclose(output);

  return(0);
}
