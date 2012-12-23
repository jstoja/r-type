//
//  main.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <cstdlib>
#include <cstdio>
#include "Debug.h"
#include "Client.h"

int	main(int argc, char *argv[]) {
  if (argc == 3) {
      Client client(argv[1], atoi(argv[2]));

      getchar();
    }
  return (0);
}
