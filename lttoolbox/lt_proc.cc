/*
 * Copyright (C) 2005 Universitat d'Alacant / Universidad de Alicante
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#include <lttoolbox/fst_processor.h>
#include <lttoolbox/lttoolbox_config.h>
#include <lttoolbox/my_stdio.h>
#include <lttoolbox/lt_locale.h>

#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <libgen.h>

#ifdef _MSC_VER
#include <io.h>
#include <fcntl.h>
#endif

using namespace std;

void endProgram(char *name)
{
  cout << basename(name) << ": process a stream with a letter transducer" << endl;
  cout << "USAGE: " << basename(name) << " [-c] [-a|-g|-n|-d|-p|-s|-t] fst_file [input_file [output_file]]" << endl;
  cout << "Options:" << endl;
#if HAVE_GETOPT_LONG
  cout << "  -a, --analysis:         morphological analysis (default behavior)" << endl;
  cout << "  -c, --case-sensitive:   use the literal case of the incoming characters" << endl;
  cout << "  -g, --generation:       morphological generation" << endl;
  cout << "  -n, --non-marked-gen    morph. generation without unknown word marks" << endl;
  cout << "  -d, --debugged-gen      morph. generation with all the stuff" <<endl;
  cout << "  -p, --post-generation:  post-generation" << endl;
  cout << "  -s, --sao:              SAO annotation system input processing" << endl;
  cout << "  -t, --transliteration:  apply transliteration dictionary" << endl;
  cout << "  -z, --null-flush:       flush output on the null character " << endl;
  cout << "  -w, --dictionary-case:  use dictionary case instead of surface case" << endl;
  cout << "  -v, --version:          version" << endl;
  cout << "  -h, --help:             show this help" << endl;
#else
  cout << "  -a:   morphological analysis (default behavior)" << endl;
  cout << "  -c:   use the literal case of the incoming characters" << endl;
  cout << "  -g:   morphological generation" << endl;
  cout << "  -n:   morph. generation without unknown word marks" << endl;
  cout << "  -p:   post-generation" << endl;
  cout << "  -s:   SAO annotation system input processing" << endl;
  cout << "  -t:   apply transliteration dictionary" << endl;
  cout << "  -z:   flush output on the null character " << endl;
  cout << "  -w:   use dictionary case instead of surface case" << endl;
  cout << "  -v:   version" << endl;
  cout << "  -h:   show this help" << endl;
#endif
  exit(EXIT_FAILURE);
}

void checkValidity(FSTProcessor const &fstp)
{
  if(!fstp.valid())
  {
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
  int cmd = 0;
  FSTProcessor fstp;

#if HAVE_GETOPT_LONG
  static struct option long_options[]=
    {
      {"analysis",        0, 0, 'a'},
      {"generation",      0, 0, 'g'},
      {"non-marked-gen",  0, 0, 'n'},
      {"debugged-gen",    0, 0, 'd'},
      {"post-generation", 0, 0, 'p'},
      {"sao",             0, 0, 's'},
      {"transliteration", 0, 0, 't'},
      {"null-flush",      0, 0, 'z'},
      {"dictionary-case", 0, 0, 'w'},
      {"version",	  0, 0, 'v'},
      {"case-sensitive",  0, 0, 'c'},
      {"help",            0, 0, 'h'}
    };
#endif    

  while(true)
  {
#if HAVE_GETOPT_LONG
    int option_index;
    int c = getopt_long(argc, argv, "acgndpstzwvh", long_options, &option_index);
#else
    int c = getopt(argc, argv, "acgndpstzwvh");
#endif    

    if(c == -1)
    {
      break;
    }
      
    switch(c)
    {
    case 'c':
      fstp.setCaseSensitiveMode(true);
      break;
      
    case 'a':
    case 'g':
    case 'n':
    case 'd':
    case 'p':
    case 't':
    case 's':
      if(cmd == 0)
      {
	cmd = c;
      }
      else
      {
	endProgram(argv[0]);
      }
      break;

    case 'z':
      fstp.setNullFlush(true);
      break;

    case 'w':
      fstp.setDictionaryCaseMode(true);
      break;

    case 'v':
      cout << basename(argv[0]) << " version " << PACKAGE_VERSION << endl;
      exit(EXIT_SUCCESS);
      break;
    case 'h':
    default:
      endProgram(argv[0]);
      break;
    }
  }

  FILE *input = stdin, *output = stdout;
  LtLocale::tryToSetLocale();
  
  if(optind == (argc - 3))
  {
    FILE *in = fopen(argv[optind], "rb");
    if(in == NULL || ferror(in))
    {
      endProgram(argv[0]);
    }
    
    input = fopen(argv[optind+1], "rb");
    if(input == NULL || ferror(input))
    {
      endProgram(argv[0]);
    }
    
    output= fopen(argv[optind+2], "wb");
    if(output == NULL || ferror(output))
    {
      endProgram(argv[0]);
    }
    
    fstp.load(in);
    fclose(in);
  }
  else if(optind == (argc -2))
  {
    FILE *in = fopen(argv[optind], "rb");
    if(in == NULL || ferror(in))
    {
      endProgram(argv[0]);
    }
    
    input = fopen(argv[optind+1], "rb");
    if(input == NULL || ferror(input))
    {
      endProgram(argv[0]);
    }
    
    fstp.load(in);
    fclose(in);
  }   
  else if(optind == (argc - 1))
  {
    FILE *in = fopen(argv[optind], "rb");
    if(in == NULL || ferror(in))
    {
      endProgram(argv[0]);
    }
    fstp.load(in);    
    fclose(in);
  }
  else
  {
    endProgram(argv[0]);
  }

#ifdef _MSC_VER
  	_setmode(_fileno(input), _O_U8TEXT);
	_setmode(_fileno(output), _O_U8TEXT);
#endif

  try
  {
    switch(cmd)
    {
      case 'n':
        fstp.initGeneration();
        checkValidity(fstp);
        fstp.generation(input, output, gm_clean);
        break;

      case 'g':
        fstp.initGeneration();
        checkValidity(fstp);
        fstp.generation(input, output);
        break;
      
      case 'd':
        fstp.initGeneration();
        checkValidity(fstp);
        fstp.generation(input, output, gm_all);
      
      case 'p':
        fstp.initPostgeneration();
        checkValidity(fstp);
        fstp.postgeneration(input, output);
        break;

      case 's':
        fstp.initAnalysis();
        checkValidity(fstp);
        fstp.SAO(input, output);
        break;

      case 't':
        fstp.initPostgeneration(); 
        checkValidity(fstp);
        fstp.transliteration(input, output);
        break;
      
      case 'a':
      default:
        fstp.initAnalysis(); 
        checkValidity(fstp);
        fstp.analysis(input, output);
        break;
    }
  }
  catch (exception& e)
  {
    cerr << e.what();
    if (fstp.getNullFlush()) {
      fputws_unlocked('\0', output);
    }

    exit(1);
  }

  fclose(input);
  fclose(output); 
  return EXIT_SUCCESS;
}
